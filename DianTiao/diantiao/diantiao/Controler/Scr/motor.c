#include "motor.h"

struct MOTOR
{
    float current;  //电流读数
    float speed;    //转速读数
    float position; //位置读数
    float zero_position;//位置零位
    uint16_t counter;   //辅助计数器
    uint8_t is_blocked; //堵转检测
    uint8_t id;
}

float motor_read_speed(MOTOR * motor)
{
    return motor->speed;
}

float motor_get_speed(MOTOR * motor)
{
    return motor->speed;
}

float motor_read_current(MOTOR * motor)
{
    return motor->current;
}

float motor_get_current(MOTOR * motor)
{
    return motor->current;
}

float motor_read_position(MOTOR * motor)
{
    return motor->position;
}

float motor_get_position(MOTOR * motor)
{
    return motor->position;
}

float motor_get_zero_position(MOTOR * motor)
{
    return motor->zero_position;
}

float motor_set_zero_position(MOTOR * motor, float zero_position)
{
    return motor->zero_position;
}

void motor_check_blocking(MOTOR * motor)
{
    return;
}

uint8_t motor_is_blocked(MOTOR * motor)
{
    return motor->is_blocked;
}


void motor_output(MOTOR * motor)
{
    return;
}
