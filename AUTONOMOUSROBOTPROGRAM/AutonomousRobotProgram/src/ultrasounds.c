#include "stm32f1xx.h"
#include "ultrasounds.h"

void update_ultrasound_distances(float *distances_array) {			//ultrasounds - prototyp blokowy - przetestowany
	//static float distances[1];
	int reflection_time;
	int pins[4] = { GPIO_PIN_7 };

	//printf("Wchodze\n");
	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);


		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7))
		{
			reflection_time++;
			//if(reflection_time > 20000)
			//break;
			//waiting(1);
			//HAL_Delay(1);
		}
		//printf("Time: %d |||", reflection_time);
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		//printf("Distance: %.3f   ", distance);
		distances_array[0] = distance;
	}
	HAL_Delay(100);

	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		//waiting(2);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		//waiting(800);
		//HAL_Delay(10);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);


		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9))
		{
			reflection_time++;
			//if(reflection_time > 20000)
			//break;
			//waiting(1);
			//HAL_Delay(1);
		}
		//printf("Time: %d |||", reflection_time);
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		//printf("Distance: %.3f   ", distance);
		distances_array[1] = distance;

	}
	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		//waiting(2);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
		//waiting(800);
		//HAL_Delay(10);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);


		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
			reflection_time++;
			//if(reflection_time > 20000)
			//break;
			//waiting(1);
			//HAL_Delay(1);
		}
		//printf("Time: %d |||", reflection_time);
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		//printf("Distance: %.3f   ", distance);
		distances_array[2] = distance;
	}
	HAL_Delay(1);
	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		//waiting(2);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		//waiting(800);  // wait for 10 us
		//HAL_Delay(10);
		waiting(800);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);


		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))
		{
			reflection_time++;
			//if(reflection_time > 20000)
			//break;
			//waiting(1);
			//HAL_Delay(1);
		}
		//printf("Time: %d |||", reflection_time);
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		//printf("Distance: %.3f   ", distance);
		distances_array[3] = distance;
		//printf("\n");
	}
}

// 1-prawo 2-lewo 3-tyl 4-przod
void update_ultrasound_right_distance(float *distances_array) {
	int reflection_time;

	//printf("Wchodze\n");

	reflection_time = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	//waiting(2);
	HAL_Delay(2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	//waiting(800);
	//HAL_Delay(10);
	//waiting(640);
	//HAL_Delay(800);
	waiting(800);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);


	while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)))
		continue;
	while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)) {
		reflection_time++;
		//if(reflection_time > 20000)
		//break;
		//waiting(1);
		//HAL_Delay(1);
	}
	//printf("Time: %d |||", reflection_time);
	float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
	//printf("Distance: %.3f   ", distance);
	distances_array[0] = distance;
}





void update_ultrasound_front_distance(float *distances_array)
{
	int reflection_time;

	reflection_time = 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	//waiting(2);
	HAL_Delay(2);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	//waiting(800);
	//HAL_Delay(10);
	waiting(800);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);



	while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)))
		continue;
	while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)) {
		reflection_time++;
		//if(reflection_time > 20000)
		//break;
		//waiting(1);
		//HAL_Delay(1);
	}
	//printf("Time: %d |||", reflection_time);
	float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
	//printf("Distance: %.3f   ", distance);
	distances_array[3] = distance;
	//printf("\n");

}







void update_ultrasound_back_distance(float *distances_array) {
	int reflection_time;

		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
		//waiting(800);
		//HAL_Delay(10);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);


		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
			reflection_time++;
			//if(reflection_time > 20000)
			//break;
			//waiting(1);
			//HAL_Delay(1);
		}
		//printf("Time: %d |||", reflection_time);
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		//printf("Distance: %.3f   ", distance);
		distances_array[2] = distance;

}

// 1-prawo 2-lewo 3-tyl 4-przod
