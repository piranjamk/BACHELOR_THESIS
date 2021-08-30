#include "stm32f1xx.h"
#include "ultrasounds.h"

void update_ultrasound_distances(float *distances_array) {			//ultrasounds - block prototype - fully tested
	int reflection_time;											//block prototype - easy replacements
	int pins[4] = { GPIO_PIN_7 };
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
		}
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		distances_array[0] = distance;
	}
	HAL_Delay(100);

	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9))
		{
			reflection_time++;
		}
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		distances_array[1] = distance;

	}
	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);

		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
			reflection_time++;
		}
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		distances_array[2] = distance;
	}
	HAL_Delay(1);
	{
		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_Delay(2);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		waiting(800);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))
		{
			reflection_time++;
		}
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		distances_array[3] = distance;
	}
}

void update_ultrasound_right_distance(float *distances_array) {
	int reflection_time;

	reflection_time = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	waiting(800);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);

	while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)))
		continue;
	while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)) {
		reflection_time++;
	}
	float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
	distances_array[0] = distance;
}

void update_ultrasound_front_distance(float *distances_array)
{
	int reflection_time;

	reflection_time = 0;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	waiting(800);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)))
		continue;
	while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12)) {
		reflection_time++;
	}
	float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
	distances_array[3] = distance;
}

void update_ultrasound_back_distance(float *distances_array) {
	int reflection_time;

		reflection_time = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_Delay(2);

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
		waiting(800);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);

		while (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)))
			continue;
		while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
			reflection_time++;
		}
		float distance = reflection_time * .034 / 2 * 10 * 2 / 3;
		distances_array[2] = distance;
}
