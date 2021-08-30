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
#define LSM_ADDRES			0x3a
#define TIME_OF_FORWARD_MOVING 400
#define TIME_OF_REVERSE_MOVING	500
#define ADDITIONAL_COURSE_ADJUSTEMENTS 0.1
#define TIME_OF_LEFT_TURN 600
#define TIME_OF_RIGHT_TURN 900
#define MOVING_FORWARD GPIO_PIN_RESET
#define MOVING_REVERSE GPIO_PIN_SET
#define LEFT_ENGINE_CANAL TIM_CHANNEL_4
#define RIGHT_ENGINE_CANAL TIM_CHANNEL_3
#define LEFT_PIN GPIO_PIN_1
#define RIGHT_PIN GPIO_PIN_0
#define LEFT_ENGINE_VALUE 500//589
#define WARTOSC_WYPELNIENIA_PRAWA 500//600

TIM_HandleTypeDef tim4;
TIM_HandleTypeDef tim3_servo;
UART_HandleTypeDef uart1; //PRINTING VIA BLUETOOTH
UART_HandleTypeDef uart2; //PRINTING VIA COM USING USB-LINK
I2C_HandleTypeDef i2c;
float initialHeading;
#define BOARD_SIZE 40
char board[BOARD_SIZE][BOARD_SIZE];
int position_x = 20;
int position_y = 20;
char mode = '2';

enum States {
	stateReversing = 0,
	stateDriving = 1,
	stateLeftTurning = 3,
	stateRightTurning = 4,
	stateInFrontOfWall = 5,
	stateStart = 8,
	stateEnd = 9
};

enum Headings {
	north = 0, west = 1, south = 2, east = 3
};

int headingSequence[4] = { north, east, south, west };
char charHeadings[4] = { 'N', 'E', 'S', 'W' };

int sumOfDistances[4] = { 0, 0, 0, 0 };
int breachDetected = 0;

void changeHeadingSequencesRight() {
	for (int i = 0; i < 4; i++)
		headingSequence[i] = (headingSequence[i] + 1) %4;
}

void changeHeadingSequencesLeft() {
	int temp = headingSequence[0];
	for (int i = 0; i < 3; i++)
		headingSequence[i] = headingSequence[i + 1];
	headingSequence[3] = temp;
}

void send_single_character(char c) {
	HAL_UART_Transmit(&uart1, (uint8_t*) &c, 1, 999);
	HAL_UART_Transmit(&uart2, (uint8_t*) &c, 1, 999);
	HAL_Delay(13);
}

int __io_putchar(int ch) { //function replacement

	if (ch == '\n')
		send_single_character('\r');
	send_single_character(ch);
	return ch;
}

//i2c module ----------------------------------------
void lsmWriteRegister(uint8_t reg, uint8_t value) {
	HAL_I2C_Mem_Write(&i2c, LSM_ADDRES, reg, 1, &value, sizeof(value),
			HAL_MAX_DELAY);
}

uint8_t lsmReadRegister(uint8_t reg) {
	uint8_t value = 0;
	HAL_I2C_Mem_Read(&i2c, LSM_ADDRES, reg, 1, &value, sizeof(value), HAL_MAX_DELAY);
	return value;
}

int16_t lsm_read_value(uint8_t reg) {
	int16_t value = 0;
	HAL_I2C_Mem_Read(&i2c, LSM_ADDRES, reg | 0x80, 1, (uint8_t*) &value, sizeof(value), HAL_MAX_DELAY);
	return value;
}

float get_heading_degrees() {
	int16_t m_x = (int16_t) lsmReadRegister(0x09) << 8 | lsmReadRegister(0x08);
	int16_t m_y = (int16_t) lsmReadRegister(0x0B) << 8 | lsmReadRegister(0x0A);

	float heading = atan2(m_y, m_x);
	if (heading < 0)
		heading += 2 * M_PI;
	return heading * 180 / M_PI;
}

void setI2c(void) {
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

	//mag config
	lsmWriteRegister(LSM_CTRL5, 0x64);
	lsmWriteRegister(LSM_CTRL6, 0x20);
	lsmWriteRegister(LSM_CTRL7, 0x0);
	HAL_Delay(100);
}

void waiting(int value) {
	while (--value / 2)
		continue;
}

void stopAllEngines() {
	HAL_TIM_PWM_Stop(&tim4, LEFT_ENGINE_CANAL);
	HAL_TIM_PWM_Stop(&tim4, RIGHT_ENGINE_CANAL);
}

void goForward() {
	static int counter = 0;
	if (counter == 0) {
		HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
		HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);
		HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
		HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
		counter = 1;
	} else {
		HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);
		HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
		HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
		HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
		counter = 0;
	}
	HAL_Delay(1700);
	stopAllEngines();
	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 250); //alternative: 400
	__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 350); //alternative: 200
}


int turnRight() {
	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 350);
	__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 350);

	float dist_array[4];
	update_ultrasound_distances(dist_array);

	HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_REVERSE);
	HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);
	HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
	HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);

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

	float distances[4];
		while (1)
		{
			float a = distances[0] + 2;
			float b = distances[2];
			float c = b - a;
			int shift = 1;
			if (c < 0) {
				c = -c;
				shift = -1;
			}
			float angle = atan(c / 17);
			if (abs(angle*180/M_PI) < 4){
				break;
			}
			HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
			HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
			HAL_Delay(50);
			stopAllEngines();
			update_ultrasound_distances(distances);
		}

	HAL_TIM_PWM_Stop(&tim4, RIGHT_ENGINE_CANAL);
	HAL_TIM_PWM_Stop(&tim4, LEFT_ENGINE_CANAL);
	changeHeadingSequencesLeft();
	return stateDriving;
}

void showData() {
}

int moveForward() {
	//showData();
	float distances[4];
	update_ultrasound_distances(distances);	// 1-right 2-left 3-back 4-front
	int startDistance = distances[3];//after right turn need to check: if after wall breach detection -
	  //- minimum distance traveled is: 30-50 cm

	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 250); //alternative 400
	__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 310); // alternative 200

	HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
	HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);
	HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
	HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);

	while (distances[3] > 25.0) {

		if (distances[2] > 50 && breachDetected == 0) {
			breachDetected = 1;
			HAL_Delay(500); //savety reasons
			stopAllEngines();
			update_ultrasound_distances(distances);	// 1-right 2-left 3-back 4-front
			int endDistance = abs(startDistance - distances[3]); //abs for safety reasons
			int currentHeading = headingSequence[0];
			sumOfDistances[currentHeading] += endDistance;
			return stateRightTurning;
		}

		if (distances[2] > 50 && breachDetected == 1) {
			update_ultrasound_distances(distances);
			if ((startDistance - distances[3]) > 30) {
				stopAllEngines();

				update_ultrasound_distances(distances);	// 1-right 2-left 3-back 4-fron
				int endDistance = abs(startDistance - distances[3]); //abs-safety reasons
				int currentHeading = headingSequence[0];
				sumOfDistances[currentHeading] +=
						endDistance;

				return stateDriving;
			}
		}

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int shift = 1;
		if (c < 0) {
			c = -c;
			shift = -1;
		}
		float angle = atan(c / 17);
		float trueDistance = ((a + b) / 2) * cos(angle);

		if (a < 20 && angle * 180 / M_PI > -45) {
			__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 400); // 400
			__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 0); //alternative: 200
			while (angle * 180 / M_PI> 0) {
				update_ultrasound_distances(distances);
				float a = distances[0] + 2;
				float b = distances[2];
				float c = b - a;
				int shift = 1;
				if (c < 0) {
					c = -c;
					shift = -1;
				}
				angle = atan(c / 17);
				angle = angle * shift;
				float trueDistance = ((a + b) / 2) * cos(angle);
			}
			__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 250); //alternative: 400
			__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 310); //alternative:  200
		}
		update_ultrasound_distances(distances);

	}
	stopAllEngines();

	update_ultrasound_distances(distances);	// 1-right 2-left 3-back 4-front
	float endDistance = abs(startDistance - distances[3]); //abs-negative numbers protection
	int currentHeading = headingSequence[0];
	sumOfDistances[currentHeading] += endDistance;

	printf("Przebyte odleglosci: N:%d  E:%d  S:%d  W:%d  \n\n",
			sumOfDistances[0], sumOfDistances[1],
			sumOfDistances[2], sumOfDistances[3]);
	HAL_Delay(2000);

	return stateInFrontOfWall;
}

void newMoveForward() {
	showData();
	float distances[4];
	update_ultrasound_distances(distances);	// 1-prawo 2-lewo 3-tyl 4-przod
	int startDistance = distances[3];//after right turn need to check: if after wall breach detection -
										  //- minimum distance traveled is: 30-50 cm
	while (1) {
		update_ultrasound_distances(distances);
		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int shift = 1;
		if (c < 0) {
			c = -c;
			shift = -1;
		}
		float angle = atan(c / 17);
		float trueDistance = ((a + b) / 2) * cos(angle);
		printf("a:%f    b:%f   angle:%f  trueDistance:%.f\n", a, b,shift * angle * 180 / M_PI, trueDistance);
	}

}

int turnLeft() {
	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 450);
	__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 450);

	float dist_array[4];
	update_ultrasound_distances(dist_array);
	float distanceFront = dist_array[3];

	HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
	HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_REVERSE);
	HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
	HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);

	HAL_Delay(600);
	stopAllEngines();

	float distances[4];
	while (1)
	{

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int shift = 1;
		if (c < 0) {
			c = -c;
			shift = -1;
		}
		float angle = atan(c / 17);
		if (abs(angle*180/M_PI) < 4){
			break;

		}
		HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
		HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
		HAL_Delay(50);
		stopAllEngines();
		update_ultrasound_distances(distances);

	}
	HAL_TIM_PWM_Stop(&tim4, RIGHT_ENGINE_CANAL);
	HAL_TIM_PWM_Stop(&tim4, LEFT_ENGINE_CANAL);
	changeHeadingSequencesRight();
	return stateDriving;
}

void goReverse() {
	HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_REVERSE);
	HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_REVERSE);
	HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
	HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
	HAL_Delay(TIME_OF_REVERSE_MOVING);
	HAL_TIM_PWM_Stop(&tim4, RIGHT_ENGINE_CANAL);
	HAL_TIM_PWM_Stop(&tim4, LEFT_ENGINE_CANAL);
}

void adjustCurrentCourse() {
	float distances[4];
	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 250); //alternative 400
	__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 310); //alternative 200
	update_ultrasound_distances(distances);	// 1-right 2-left 3-back 4-forward
	HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
	HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);

		float a = distances[0] + 2;
		float b = distances[2];
		float c = b - a;
		int shift = 1;
		if (c < 0) {
			c = -c;
			shift = -1;
		}
		float angle = atan(c / 17);
		float trueDistance = ((a + b) / 2) * cos(angle);

		if (a < 20 && angle * 180 / M_PI > -45) {
			__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 400); //400
			__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 0); //alternative 200
			HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
			HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
			while (angle * 180 / M_PI> 0) {
				if (a > 30 || b > 30)
					break;
				update_ultrasound_distances(distances);
				a = distances[0] + 2;
				b = distances[2];
				c = b - a;
				shift = 1;
				if (c < 0) {
					c = -c;
					shift = -1;
				}
				angle = atan(c / 17);
				angle = angle * shift;
				trueDistance = ((a + b) / 2) * cos(angle);
			}
			__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 250); //alternative 400
			__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 310); //alternative  200
		}
		stopAllEngines();
}


void turnLeftWithTime()
{

	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 650);
		__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 650);
		HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_FORWARD);
		HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_REVERSE);
		HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
		HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
		HAL_Delay(400);
		stopAllEngines();
}

void turnRightWithTime()
{
	__HAL_TIM_SET_COMPARE(&tim4, LEFT_ENGINE_CANAL, 650);
		__HAL_TIM_SET_COMPARE(&tim4, RIGHT_ENGINE_CANAL, 650);
		HAL_GPIO_WritePin(GPIOC, RIGHT_PIN, MOVING_REVERSE);
		HAL_GPIO_WritePin(GPIOC, LEFT_PIN, MOVING_FORWARD);
		HAL_TIM_PWM_Start(&tim4, LEFT_ENGINE_CANAL);
		HAL_TIM_PWM_Start(&tim4, RIGHT_ENGINE_CANAL);
		HAL_Delay(400);
		stopAllEngines();
}



void updateData() {
	int currentHeading = headingSequence[0];
	if (currentHeading == north) {
		position_y -= 1;
	} else if (currentHeading == south) {
		position_y += 1;
	} else if (currentHeading == east) {
		position_x += 1;
	} else if (currentHeading == west) {
		position_x -= 1;
	}
}




void remoteWorking(){
	uint8_t received_char;
	if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {

				HAL_UART_Receive(&uart1, &received_char, 1, 100);
				switch (received_char) {
				case 'w':
					goForward();
					break;
				case 's':
					goReverse();
					break;
				case 'a':
					turnLeftWithTime();
					break;
				case 'd':
					turnRightWithTime();
					break;
				case '2':
					mode = '2';
					break;
				}

			}
			if (__HAL_UART_GET_FLAG(&uart2, UART_FLAG_RXNE) == SET) {
				HAL_UART_Receive(&uart2, &received_char, 1, 100);
				switch (received_char) {
				case 'w':
					goForward();
					break;
				case 's':
					goReverse();
					break;
				case 'a':
					turnLeftWithTime();
					break;
				case 'd':
					turnRightWithTime();
					break;
				case '2':
					mode = '2';
					break;
				}
			}
			float distances[4];
			update_ultrasound_distances(distances);

			//angels
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

void automaticWorking()
{
	int position_x = 20;
	int position_y = 20;
	{
			for (int i = 0; i < BOARD_SIZE; i++)
				for (int j = 0; j < BOARD_SIZE; j++)
					board[i][j] = '_';
		}


	int przejechana_ilosc_prosto_po_skrecie_w_prawo = 0; //need to ravel at least two length after turn

	float distances[4];

	while (1) {
		if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {
			uint8_t value;
			HAL_UART_Receive(&uart1, &value, 1, 100);
			if (value == '1') {mode = '1'; break;}
			if (value == '>') { break; } //if user sent '>' - start measurements

		}
	}
	int operational_counter = 0;
	int initial_position_x = position_x;
	int initial_position_y = position_y;
	while (1 && mode == '2') {

		if (__HAL_UART_GET_FLAG(&uart1, UART_FLAG_RXNE) == SET) {
			uint8_t value;
			HAL_UART_Receive(&uart1, &value, 1, 100);
			if (value == '1') {mode = '1'; break;}
			if (value == '<') { break;} //if user sent '<' - stop measurements
		}
		operational_counter++;
		update_ultrasound_distances(distances);

		if (distances[2] < 50) { //10 cm for safety reasons
			int currentHeading = headingSequence[0];
			if (currentHeading == north)
				board[position_y][position_x + 1] = 'X';
			if (currentHeading == south)
				board[position_y][position_x - 1] = 'X';
			if (currentHeading == east)
				board[position_y+1][position_x] = 'X';
			if (currentHeading == west)
				board[position_y-1][position_x] = 'X';

			if (distances[3] < 25) {
				if (currentHeading == north)
					board[position_y - 1][position_x] = 'X';
				if (currentHeading == south)
					board[position_y + 1][position_x] = 'X';
				if (currentHeading == east)
					board[position_y][position_x + 1] = 'X';
				if (currentHeading == west)
					board[position_y][position_x - 1] = 'X';
			}
		}
		if ((operational_counter > 4) && (headingSequence[0] == north)) {
					if ( abs(initial_position_x - position_x) < 1  && abs(initial_position_y - position_y) < 1) {
						HAL_Delay(10);
								{
										for (int i = 0; i < BOARD_SIZE; i++) {
											for (int j = 0; j < BOARD_SIZE; j++){
												printf("%c", board[i][j]);;
											}
											printf("\n");
										}
								}
								HAL_Delay(10); send_single_character('.'); HAL_Delay(10); send_single_character('\n');
																			send_single_character('*');
										 //sending * meaning: stop mapping in autonomic mode
						break;
					}
				}
		printf("\n");
		HAL_Delay(10); send_single_character('.'); HAL_Delay(10); send_single_character('\n');

		if (distances[2] > 40 && breachDetected == 1) //check just after turn
			breachDetected++;
		else if (distances[2] > 40 && breachDetected == 2)
			breachDetected = 0;
		breachDetected %= 3;
		if (distances[2] > 40 && breachDetected == 0)
		{
			breachDetected = 1;
			HAL_Delay(700); //a few additional miliseconds - savety reasons
			stopAllEngines();
			turnRight();

		} else if(distances[2] < 40){	//turn protection
			breachDetected = 1;
		}


		if (distances[3] > 25)
			adjustCurrentCourse();
		if (distances[3] > 25)
		{
			goForward();
			updateData();
		}
		else {
			if (distances[3] < 10)
				goReverse();
			turnLeft();
		}
	}
}

int main(void) {
	{
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
				board[i][j] = '_';
	}
	SystemCoreClock = 8000000; // sys tick, hal_delay in ms
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();

	setControlPinsBridge();
	setPwmPinsBridge();
	setButton();
	setPwm();
	setUsartPrinting();
	setI2c();
	initServo();
	setUltrasoundPins();
	HAL_Delay(300);
	int i = 0;
	uint8_t received_char;

	int headingMatrix[4] = { north, east, south, west };
	int distanceMatrix[4] = { 0, 0, 0, 0 };
	enum States state = stateStart;

	while (1) {
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
			break;
	}

	lsmWriteRegister(LSM_CTRL1, 0x40 | 0x07);
	lsmWriteRegister(LSM_CTRL5, 0x80 | 0x10);

	while(1){
		if (mode == '1') remoteWorking();
		if (mode == '2') automaticWorking();
		if (mode == '3') continue;
		HAL_Delay(3);
	}


}
