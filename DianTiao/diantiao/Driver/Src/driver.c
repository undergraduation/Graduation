#include "driver.h"
#include "gpio.h"
#include "mcp4725.h"

#define ABS(x) (((x) > 0) ? (x) : (-x))
#define MAXSPEED 1000
#define MINSPEED 100
void driver_control(int speed)
{
	if(speed > 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	}
	speed = ABS(speed);
//	if(speed < MINSPEED)
//	{
//		MCP4725_WriteBreakData_Voltage(1000);
//	}
//	else
//	{
//		MCP4725_WriteBreakData_Voltage(4000);
//	}
	MCP4725_WriteVelData_Voltage(5000*speed/MAXSPEED);
}
