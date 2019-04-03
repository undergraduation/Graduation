#include "motor.h"
#include "mt6813.h"
#include "mcp4725.h"
#include "adc.h"
struct MOTOR
{
    float current;       //电流读数
    float speed;         //转速读数
    float position;      //位置读数
    float zero_position; //位置零位
    uint16_t counter;    //辅助计数器
    uint8_t is_blocked;  //堵转检测
    uint8_t id;
    uint8_t dir;
};

float motor_read_speed(MOTOR *motor)
{
    switch (motor->id)
    {
    case DRIVING_MOTOR:
        motor->speed = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_4);
        if(motor->dir == 1) motor->speed = -motor->speed;
        break;
    case LIFTING_MOTOR:
        break;
    case STEERING_MOTOR:
        break;
        default：break;
    }
    return motor->speed;
}

float motor_get_speed(MOTOR *motor)
{
    return motor->speed;
}

float motor_read_current(MOTOR *motor)
{
    switch (motor->id)
    {
    case DRIVING_MOTOR:
        motor->current = ADC_RX[0] * 3.3 / 4096;
        break;
    case LIFTING_MOTOR:
        break;
    case STEERING_MOTOR:
        motor->current = ADC_RX[1] * 3.3 / 4096;
        break;
        default：break;
    }
    return motor->current;
}

float motor_get_current(MOTOR *motor)
{
    return motor->current;
}

float motor_read_position(MOTOR *motor)
{
    switch (motor->id)
    {
    case STEERING_MOTOR:
        motor->position = MT6813_Get_Angle();
        break;
        default：break;
    case LIFTING_MOTOR:
        break;
    case DRIVING_MOTOR:
        break;
        default：break;
    }
    return motor->position;
}

float motor_get_position(MOTOR *motor)
{
    return motor->position;
}

float motor_get_zero_position(MOTOR *motor)
{
    return motor->zero_position;
}

float motor_set_zero_position(MOTOR *motor, float zero_position)
{
    return motor->zero_position;
}

void motor_check_blocking(MOTOR *motor)
{
    return;
}

uint8_t motor_is_blocked(MOTOR *motor)
{
    return motor->is_blocked;
}

void motor_output(MOTOR *motor, float speed)
{
    ass
    switch (motor->id)
    {
    case DRIVING_MOTOR:
        if (speed >= 0)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
            motor->dir = 0;
        }
        else
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
            speed = -speed;
            motor->dir = 1;
        }
        MCP4725_WriteVelData_Voltage(speed);
        break;
    case STEERING_MOTOR:
        /*DC_AL     ------> TIM2_CH3
         *DC_AH     ------> TIM2_CH4
         *DC_BL     ------> TIM3_CH1
         *DC_BH     ------> TIM3_CH2
         */
        if (speed > 0)
        {
            TIM2->CCR2 = 0;
            TIM3->CCR3 = 0;
            TIM2->CCR4 = speed;
            TIM3->CCR1 = 2000;   
        }
        else
        {
            TIM2->CCR1 = 0;
            TIM3->CCR4 = 0;
            TIM2->CCR2 = -speed;
            TIM3->CCR3 = 2000;     
        }
        break;
    case LIFTING_MOTOR:
        break;
    }
    return;
}
