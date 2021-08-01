/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */
#include "stm32f1xx.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "setups.h"
#include "ultrasounds.h"
#include "board.c"

#define LSM_TEMP_OUT			0x05
#define LSM_STATUS_M			0x07
#define LSM_OUT_X_M				0x08
#define LSM_OUT_Y_M				0x0a
#define LSM_OUT_Z_M				0x0c
#define LSM_WHO_AM_I			0x0f
#define LSM_CTRL0				0x1f
#define LSM_CTRL1				0x20
#define LSM_CTRL2				0x21
#define LSM_CTRL3				0x22
#define LSM_CTRL4				0x23
#define LSM_CTRL5				0x24
#define LSM_CTRL6				0x25
#define LSM_CTRL7				0x26
#define LSM_STATUS				0x27
#define LSM_OUT_X_A				0x28
#define LSM_OUT_Y_A				0x2a
#define LSM_OUT_Z_A				0x2c
#define LSM_ADDR			0x3a
#define CZAS_JAZDY_DO_PRZODU 400
#define CZAS_JAZDY_DO_TYLU	500
#define WSPOLCZYNNIK_KORYGUJACY 0.1
#define CZAS_OBROTU_W_LEWO 600
#define CZAS_OBROTU_W_PRAWO 900
#define JAZDA_DO_PRZODU GPIO_PIN_RESET
#define JAZDA_DO_TYLU GPIO_PIN_SET
#define KANAL_SILNIKA_LEWEGO TIM_CHANNEL_4
#define KANAL_SILNIKA_PRAWEGO TIM_CHANNEL_3
#define PIN_LEWY GPIO_PIN_1
#define PIN_PRAWY GPIO_PIN_0
#define WARTOSC_WYPELNIENIA_LEWA 500//589
#define WARTOSC_WYPELNIENIA_PRAWA 500//600

TIM_HandleTypeDef tim4;
TIM_HandleTypeDef tim3_servo;
UART_HandleTypeDef uart1; //DRUKOWANIE PO BLUETOOTH
UART_HandleTypeDef uart2; //DRUKOWANIE PRZEZ COM VIA USB-LINK
I2C_HandleTypeDef i2c;
float kierunek_pierwotny;
#define ROZMIAR_PLANSZY 40
char plansza[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY];
int pozycja_x = 20;
int pozycja_y = 20;
char tryb = '2';

enum Stany {
	stan_cofam = 0,
	stan_jade = 1,
	stan_obracam_w_lewo = 3,
	stan_obracam_w_prawo = 4,
	stan_przed_sciana = 5,
	stan_startowy = 8,
	stan_skonczylem = 9
};
enum Kierunki {
	polnoc = 0, zachod = 1, poludnie = 2, wschod = 3
};
int kolejnosc_kierunkow[4] = { polnoc, wschod, poludnie, zachod };
char kierunki_slownie[4] = { 'N', 'E', 'S', 'W' };

int suma_przejechanych_odleglosci[4] = { 0, 0, 0, 0 };
int wykryto_wyrwe_w_prawo = 0;

void zmien_kolejnosc_kierunkow_w_prawo() {
	for (int i = 0; i < 4; i++)
		kolejnosc_kierunkow[i] = (kolejnosc_kierunkow[i] + 1) %4;
}

void zmien_kolejnosc_kierunkow_w_lewo() {
	int temp = kolejnosc_kierunkow[0];
	for (int i = 0; i < 3; i++)
		kolejnosc_kierunkow[i] = kolejnosc_kierunkow[i + 1];
	kolejnosc_kierunkow[3] = temp;
}

void send_char(char c) {
	HAL_UART_Transmit(&uart1, (uint8_t*) &c, 1, 999);
	HAL_UART_Transmit(&uart2, (uint8_t*) &c, 1, 999);
	HAL_Delay(13);
}

int __io_putchar(int ch) {

	if (ch == '\n')
		send_char('\r');
	send_char(ch);
	return ch;
}

//i2c module ----------------------------------------
void lsm_write_reg(uint8_t reg, uint8_t value) {
	HAL_I2C_Mem_Write(&i2c, LSM_ADDR, reg, 1, &value, sizeof(value),
			HAL_MAX_DELAY);
}

uint8_t lsm_read_reg(uint8_t reg) {
	uint8_t value = 0;
	HAL_I2C_Mem_Read(&i2c, LSM_ADDR, reg, 1, &value, sizeof(value),
			HAL_MAX_DELAY);
	return value;
}

int16_t lsm_read_value(uint8_t reg) {
	int16_t value = 0;
	HAL_I2C_Mem_Read(&i2c, LSM_ADDR, reg | 0x80, 1, (uint8_t*) &value,
			sizeof(value), HAL_MAX_DELAY);
	return value;
}

float get_heading_degrees() {
	int16_t m_x = (int16_t) lsm_read_reg(0x09) << 8 | lsm_read_reg(0x08);
	int16_t m_y = (int16_t) lsm_read_reg(0x0B) << 8 | lsm_read_reg(0x0A);

	float heading = atan2(m_y, m_x);
	if (heading < 0)
		heading += 2 * M_PI;
	return heading * 180 / M_PI;
}

void set_i2c(void) {
	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_OD;
	gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;		// SCL, SDA
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &gpio);

	i2c.Instance = I2C1;
	i2c.Init.ClockSpeed = 100000;
	i2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	i2c.Init.OwnAddress1 = 0xff;
	i2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	i2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	i2c.Init.OwnAddress2 = 0xff;
	i2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	i2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	HAL_I2C_Init(&i2c);

	//konfiguracja modulu
	lsm_write_reg(LSM_CTRL5, 0x64); // z ustawien drugiego projektu na gicie -magnetometr + acc
	lsm_write_reg(LSM_CTRL6, 0x20); // z ustawien drugiego projektu na gicie -magnetometr + acc
	lsm_write_reg(LSM_CTRL7, 0x0); // z ustawien drugiego projektu na gicie -magnetometr + acc
	HAL_Delay(100);
}

void waiting(int value) {
	while (--value / 2)
		continue;
}

void zatrzymaj_silniki() {
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_LEWEGO);
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_PRAWEGO);
}

void jedz_do_przodu() {
	//__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400//doklejone
	//		__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 310); // 200//doklejone
	static int licznik = 0;
	if (licznik == 0) {
		HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
		HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
		licznik = 1;
	} else {
		HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);
		HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
		licznik = 0;
	}
	HAL_Delay(1700);
	zatrzymaj_silniki();
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400//doklejone
		__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 350); // 200//doklejone
}



//(if przedostatni == skrec w prawo && ostatnia_odlegloc - teraz odleglosc < 50)
//skrec w lewo)

int skrec_w_prawo() {
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 350);
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 350);

	float dist_array[4];
	update_ultrasound_distances(dist_array);
	float odleglosc_przod = dist_array[0];

	HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_TYLU);
	HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);

	HAL_Delay(440);
	update_ultrasound_distances(dist_array);
	float distance = dist_array[3];
	float previous_distance;
	while (1) {
		previous_distance = distance;
		update_ultrasound_distances(dist_array);
		distance = dist_array[3];
		if (abs(previous_distance - distance) < 8
				&& previous_distance < distance)
			break;
	}


	//dopisane 11 05 2021 o 15 -- BEGINING
	float distances[4];//dopisane 11 05 2021
		while (1)//dopisane 	11 05 2021
		{

			float a = distances[0] + 2;
			float b = distances[2];
			float c = b - a;
			int zwrot = 1;
			if (c < 0) {
				c = -c;
				zwrot = -1;
			}
			float kat = atan(c / 17);
			if (abs(kat*180/M_PI) < 4){
				//printf("Skrecilismy w lewo i mamy ponizej 10 stopni wychodzimy z petli skrecajace w lewo\n");
				break;

			}
			HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
			HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
			HAL_Delay(50);
			zatrzymaj_silniki();
			update_ultrasound_distances(distances);
		}
	//dopisane 11 05 2021 o 15 -- END

	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_PRAWEGO);
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_LEWEGO);
	//zatrzymaj_silniki();
	zmien_kolejnosc_kierunkow_w_lewo();
	return stan_jade;
}

void wyswietl_dane() {
	//printf("Jade na: %c\n", kierunki_slownie[kolejnosc_kierunkow[0]]);
	/*
	printf("Przebyte odleglosci: N:%d  E:%d  S:%d  W:%d  \n\n",
			suma_przejechanych_odleglosci[0], suma_przejechanych_odleglosci[1],
			suma_przejechanych_odleglosci[2], suma_przejechanych_odleglosci[3]);
	HAL_Delay(2000);
	*/
}

int podazaj_przod() {
	wyswietl_dane();
	float distances[4];
	update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
	int odleglosc_startowa = distances[3];//trzeba zmierzyc, czy po skrecie w prawo po wykryciu wyrwy
										  //przejechalismy przynajmniej 30-50 cm

	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400//doklejone
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 310); // 200//doklejone


	HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
	HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);

	int skrecam_w_prawo = 0;
	int skrecam_w_lewo = 0;
	int skrecam = 0;
	while (distances[3] > 25.0) {

		//printf("%.3f\n", distances[0]);

		if (distances[2] > 50 && wykryto_wyrwe_w_prawo == 0) {
			wykryto_wyrwe_w_prawo = 1;
			HAL_Delay(500); //Poczekaj do pelnego przejechania.
			zatrzymaj_silniki();
			update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
			int odleglosc_koncowa = abs(odleglosc_startowa - distances[3]); //abs dla bezpieczenstwa
			int obecny_kierunek = kolejnosc_kierunkow[0];
			suma_przejechanych_odleglosci[obecny_kierunek] += odleglosc_koncowa;
			return stan_obracam_w_prawo;
		}

		if (distances[2] > 50 && wykryto_wyrwe_w_prawo == 1) {
			update_ultrasound_distances(distances);
			if ((odleglosc_startowa - distances[3]) > 30) {
				zatrzymaj_silniki();

				update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
				int odleglosc_koncowa = abs(odleglosc_startowa - distances[3]); //abs dla bezpieczenstwa
				int obecny_kierunek = kolejnosc_kierunkow[0];
				suma_przejechanych_odleglosci[obecny_kierunek] +=
						odleglosc_koncowa;

				return stan_jade;
			}
		}

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int zwrot = 1;
		if (c < 0) {
			c = -c;
			zwrot = -1;
		}
		float kat = atan(c / 17);
		float prawdziwa_odleglosc = ((a + b) / 2) * cos(kat);
		//printf("a:%f    b:%f   kat:%f  prawdziwa_odleglosc:%.f\n", a, b, zwrot * kat * 180 / M_PI, prawdziwa_odleglosc);

		if (a < 20 && kat * 180 / M_PI > -45) {
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 400); //400
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 0); // 200
			while (kat * 180 / M_PI> 0) {
				update_ultrasound_distances(distances);
				float a = distances[0] + 2;
				float b = distances[2];
				float c = b - a;
				int zwrot = 1;
				if (c < 0) {
					c = -c;
					zwrot = -1;
				}
				kat = atan(c / 17);
				kat = kat * zwrot;
				//printf("%f  -kat\n", kat *  180 / M_PI);
				float prawdziwa_odleglosc = ((a + b) / 2) * cos(kat);
			}
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 310); // 200
		}



		update_ultrasound_distances(distances);

	}
	zatrzymaj_silniki();

	update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
	float odleglosc_koncowa = abs(odleglosc_startowa - distances[3]); //abs dla bezpieczenstwa
	int obecny_kierunek = kolejnosc_kierunkow[0];
	suma_przejechanych_odleglosci[obecny_kierunek] += odleglosc_koncowa;

	printf("Przebyte odleglosci: N:%d  E:%d  S:%d  W:%d  \n\n",
			suma_przejechanych_odleglosci[0], suma_przejechanych_odleglosci[1],
			suma_przejechanych_odleglosci[2], suma_przejechanych_odleglosci[3]);
	HAL_Delay(2000);

	return stan_przed_sciana;
}

void nowy_podazaj_przod() {
	wyswietl_dane();
	float distances[4];
	update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
	int odleglosc_startowa = distances[3];//trzeba zmierzyc, czy po skrecie w prawo po wykryciu wyrwy
										  //przejechalismy przynajmniej 30-50 cm
	while (1) {
		update_ultrasound_distances(distances);
		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int zwrot = 1;
		if (c < 0) {
			c = -c;
			zwrot = -1;
		}
		float kat = atan(c / 17);
		float prawdziwa_odleglosc = ((a + b) / 2) * cos(kat);
		printf("a:%f    b:%f   kat:%f  prawdziwa_odleglosc:%.f\n", a, b,zwrot * kat * 180 / M_PI, prawdziwa_odleglosc);

	}

}

int skrec_w_lewo() {
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 450);
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 450);

	float dist_array[4];
	update_ultrasound_distances(dist_array);
	float odleglosc_przod = dist_array[3];

	HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
	HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_TYLU);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);

	HAL_Delay(600);
	zatrzymaj_silniki();		//dopisane 	11 05 2021

	float distances[4];//dopisane 11 05 2021
	while (1)//dopisane 	11 05 2021
	{

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int zwrot = 1;
		if (c < 0) {
			c = -c;
			zwrot = -1;
		}
		float kat = atan(c / 17);
		if (abs(kat*180/M_PI) < 4){
			//printf("Skrecilismy w lewo i mamy ponizej 10 stopni wychodzimy z petli skrecajace w lewo\n");
			break;

		}
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
		HAL_Delay(50);
		zatrzymaj_silniki();
		update_ultrasound_distances(distances);

	}
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_PRAWEGO);
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_LEWEGO);
	zmien_kolejnosc_kierunkow_w_prawo();
	return stan_jade;
}


void jedz_do_tylu() {
	HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_TYLU);
	HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_TYLU);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
	HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
	HAL_Delay(CZAS_JAZDY_DO_TYLU);
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_PRAWEGO);
	HAL_TIM_PWM_Stop(&tim4, KANAL_SILNIKA_LEWEGO);
}

void skoryguj_kurs() {
	float distances[4];
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400//doklejone
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 310); // 200//doklejone
	update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
	HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
	HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int zwrot = 1;
		if (c < 0) {
			c = -c;
			zwrot = -1;
		}
		float kat = atan(c / 17);
		float prawdziwa_odleglosc = ((a + b) / 2) * cos(kat);
		//printf("a:%f    b:%f   kat:%f  prawdziwa_odleglosc:%.f\n", a, b, zwrot * kat * 180 / M_PI, prawdziwa_odleglosc);

		if (a < 20 && kat * 180 / M_PI > -45) {
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 400); //400
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 0); // 200
			HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
			HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
			while (kat * 180 / M_PI> 0) {
				if (a > 30 || b > 30)
					break;
				update_ultrasound_distances(distances);
				a = distances[0] + 2;
				b = distances[2];
				c = b - a;
				zwrot = 1;
				if (c < 0) {
					c = -c;
					zwrot = -1;
				}
				kat = atan(c / 17);
				kat = kat * zwrot;
				//printf("%f  -kat\n", kat *  180 / M_PI);
				prawdziwa_odleglosc = ((a + b) / 2) * cos(kat);
			}
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 250); //400
			__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 310); // 200
		}
		zatrzymaj_silniki();
}


void skrec_w_lewo_czasowo()
{

	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 650);
		__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 650);
		HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_PRZODU);
		HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_TYLU);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);
		HAL_Delay(400);
		zatrzymaj_silniki();		//dopisane 	11 05 2021

}

void skrec_w_prawo_czasowo()
{
	__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_LEWEGO, 650);
		__HAL_TIM_SET_COMPARE(&tim4, KANAL_SILNIKA_PRAWEGO, 650);

		HAL_GPIO_WritePin(GPIOC, PIN_PRAWY, JAZDA_DO_TYLU);
		HAL_GPIO_WritePin(GPIOC, PIN_LEWY, JAZDA_DO_PRZODU);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_LEWEGO);
		HAL_TIM_PWM_Start(&tim4, KANAL_SILNIKA_PRAWEGO);

		HAL_Delay(400);
		zatrzymaj_silniki();
}



void updatuj_dane() {
	int obecny_kierunek = kolejnosc_kierunkow[0];
	if (obecny_kierunek == polnoc) {
		pozycja_y -= 1;
	} else if (obecny_kierunek == poludnie) {
		pozycja_y += 1;
	} else if (obecny_kierunek == wschod) {
		pozycja_x += 1;
	} else if (obecny_kierunek == zachod) {
		pozycja_x -= 1;
	}
}




void zdalnie_steruj(){
	uint8_t received_char;
	if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {

				HAL_UART_Receive(&uart1, &received_char, 1, 100);
				switch (received_char) {
				case 'w':
					jedz_do_przodu();
					break;
				case 's':
					jedz_do_tylu();
					break;
				case 'a':
					skrec_w_lewo_czasowo();
					break;
				case 'd':
					skrec_w_prawo_czasowo();
					break;
				case '2':
					tryb = '2';
					break;
				}

			}
			if (__HAL_UART_GET_FLAG(&uart2, UART_FLAG_RXNE) == SET) {
				HAL_UART_Receive(&uart2, &received_char, 1, 100);
				switch (received_char) {
				case 'w':
					jedz_do_przodu();
					break;
				case 's':
					jedz_do_tylu();
					break;
				case 'a':
					skrec_w_lewo_czasowo();
					break;
				case 'd':
					skrec_w_prawo_czasowo();
					break;
				case '2':
					tryb = '2';
					break;
				}
			}

			float distances[4];
			update_ultrasound_distances(distances);


			//get angels - begin

			int16_t a_x = lsm_read_value(LSM_OUT_X_A);
			int16_t a_y = lsm_read_value(LSM_OUT_Y_A);
			int16_t a_z = lsm_read_value(LSM_OUT_Z_A);

			float x = a_x * 2.0f / 32678.0f;
			float y = a_y * 2.0f / 32678.0f;
			float z = a_z * 2.0f / 32678.0f;

			double roll, pitch, yaw;
			double accl_y = a_y;
			double accl_x = a_x;
			double accl_z = a_z;

			roll = atan2(accl_y, accl_z);
			pitch = atan(-accl_x / (accl_y * sin(roll) + accl_z * cos(roll)));
			//get angles - end


			printf("%.0f %.0f %.0f %.0f %.0f %.0f\n", distances[0], distances[1], distances[2], distances[3], roll*180/M_PI, pitch*180/M_PI);
}

void automatycznie_steruj()
{

	int pozycja_x = 20;
	int pozycja_y = 20;
	{
			for (int i = 0; i < ROZMIAR_PLANSZY; i++)
				for (int j = 0; j < ROZMIAR_PLANSZY; j++)
					plansza[i][j] = '_';
		}


	int przejechana_ilosc_prosto_po_skrecie_w_prawo = 0; //trzeba przejechac minimum dwie dlugosci po luce skrecie

	float distances[4];

	while (1) {
		if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {
			uint8_t value;
			HAL_UART_Receive(&uart1, &value, 1, 100);
			if (value == '1') {tryb = '1'; break;}
			if (value == '>') { break; } //jesli uzytkownik przeslal '>' to rozpocznij pomiar

		}
	}
	int operational_counter = 0;
	int poczatkowa_pozycja_x = pozycja_x;
	int poczatkowa_popzycja_y = pozycja_y;
	while (1 && tryb == '2') {


		if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {
			uint8_t value;
			HAL_UART_Receive(&uart1, &value, 1, 100);
			if (value == '1') {tryb = '1'; break;}
			if (value == '<') { break;} //jesli uzytkownik przeslal '<' to zakoncz
		}


		operational_counter++;

		update_ultrasound_distances(distances);
		//printf("Jade \n");

		if (distances[2] < 50) { //rezerwa 10 cm dla bezpieczenstwa
			int kierunek_obecny = kolejnosc_kierunkow[0];
			if (kierunek_obecny == polnoc)
				plansza[pozycja_y][pozycja_x + 1] = 'X';
			if (kierunek_obecny == poludnie)
				plansza[pozycja_y][pozycja_x - 1] = 'X';
			if (kierunek_obecny == wschod)
				plansza[pozycja_y+1][pozycja_x] = 'X';
			if (kierunek_obecny == zachod)
				plansza[pozycja_y-1][pozycja_x] = 'X';

			if (distances[3] < 25) {
				if (kierunek_obecny == polnoc)
					plansza[pozycja_y - 1][pozycja_x] = 'X';
				if (kierunek_obecny == poludnie)
					plansza[pozycja_y + 1][pozycja_x] = 'X';
				if (kierunek_obecny == wschod)
					plansza[pozycja_y][pozycja_x + 1] = 'X';
				if (kierunek_obecny == zachod)
					plansza[pozycja_y][pozycja_x - 1] = 'X';
			}
		}

		if ((operational_counter > 4) && (kolejnosc_kierunkow[0] == polnoc)) {
					if ( abs(poczatkowa_pozycja_x - pozycja_x) < 1  && abs(poczatkowa_popzycja_y - pozycja_y) < 1) {
						HAL_Delay(10);
								{
										for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
											for (int j = 0; j < ROZMIAR_PLANSZY; j++){
												printf("%c", plansza[i][j]);;
											}
											printf("\n");

										}
								}
								HAL_Delay(10); send_char('.'); HAL_Delay(10); send_char('\n');
																			send_char('*');
										 //wyslanie * oznacza zakonczenie mapowania w trybie autonomicznym
						//while (1) continue; //tylko do testow - - -
						break;
					}
				}

		printf("\n");
		HAL_Delay(10); send_char('.'); HAL_Delay(10); send_char('\n');



		if (distances[2] > 40 && wykryto_wyrwe_w_prawo == 1) //ochrona tuz po skrecie
			wykryto_wyrwe_w_prawo++;
		else if (distances[2] > 40 && wykryto_wyrwe_w_prawo == 2)
			wykryto_wyrwe_w_prawo = 0;
		wykryto_wyrwe_w_prawo %= 3;
		if (distances[2] > 40 && wykryto_wyrwe_w_prawo == 0)
		{
			wykryto_wyrwe_w_prawo = 1;
			HAL_Delay(700); //Poczekaj do pelnego przejechania.
			zatrzymaj_silniki();
			skrec_w_prawo();

		} else if(distances[2] < 40){	//ochrona skretu
			wykryto_wyrwe_w_prawo = 1;
		}


		if (distances[3] > 25)
			skoryguj_kurs();
		if (distances[3] > 25)
		{
			jedz_do_przodu();
			updatuj_dane();
		}
		else {
			if (distances[3] < 10)
				jedz_do_tylu();
			skrec_w_lewo();
		}
	}
}
int main(void) {
	{
		for (int i = 0; i < ROZMIAR_PLANSZY; i++)
			for (int j = 0; j < ROZMIAR_PLANSZY; j++)
				plansza[i][j] = '_';
	}
	//SystemClock_Config();
	SystemCoreClock = 8000000; // sys tick, hal_delay w ms
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();

	set_piny_kontrolne_mostka();
	set_piny_pwm_mostka();
	set_przycisk();
	set_pwm();
	set_usart_printowanie();
	set_i2c();
	init_servo();
	set_ultrasound_pins();
	HAL_Delay(300);
	int i = 0;
	uint8_t received_char;

// 1-prawo 2-lewo 3-tyl 4-przod





	int macierz_z_kierunkami[4] = { polnoc, wschod, poludnie, zachod };
	int macierz_z_odleglosciami[4] = { 0, 0, 0, 0 };
	enum Stany stan = stan_startowy;

	while (1) {
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			break;
	}


	lsm_write_reg(LSM_CTRL1, 0x40 | 0x07); // nadpis i poprawa
	lsm_write_reg(LSM_CTRL5, 0x80 | 0x10); //nadpis i poprawa




	while(1){
		if (tryb == '1') zdalnie_steruj();
		if (tryb == '2') automatycznie_steruj();
		if (tryb == '3') continue;
		HAL_Delay(3);
	}


}
