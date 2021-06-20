#pragma once
#include "stm32f1xx.h"

void update_ultrasound_distances(float *distances_array);
void update_ultrasound_front_distance(float *distances_array);
void update_ultrasound_right_distance(float *distances_array);
