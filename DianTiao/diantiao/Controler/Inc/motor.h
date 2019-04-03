#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f1xx_hal.h"

#define DRIVING_MOTOR 0
#define STEERING_MOTOR 1
#define LIFTING_MOTOR 2


typedef struct MOTOR MOTOR;

float motor_read_speed(MOTOR * motor);
float motor_get_speed(MOTOR * motor);
float motor_read_current(MOTOR * motor);
float motor_get_current(MOTOR * motor);
float motor_read_position(MOTOR * motor);
float motor_get_position(MOTOR * motor);
float motor_get_zero_position(MOTOR * motor);
float motor_set_zero_position(MOTOR * motor, float zero_position);
void motor_check_blocking(MOTOR * motor);
uint8_t motor_is_blocked(MOTOR * motor);

void motor_output(MOTOR *motor, float speed);

#endif

