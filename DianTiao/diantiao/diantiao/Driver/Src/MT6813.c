#include "mt6813.h"
#include "myi2c.h"
#include "delay.h"

u8 MT6813_init()
{
	u8 res;
	MT6813_IIC_Init();
	res = MT6813_Read_Byte(MT6813_ADDR,MT6813_REG1);
	if(res == MT6813_ID)
		return 0;
	return 1;
}

u8 MT6813_Write_Byte(u8 addr, u8 reg, u8 data)
{
	MT6813_IIC_Start();
	MT6813_IIC_Send_Byte((addr<<1)|0);
	if(MT6813_IIC_Wait_Ack())
	{
		MT6813_IIC_Stop();
		return 1;
	}
	MT6813_IIC_Send_Byte(reg);
	MT6813_IIC_Wait_Ack();
	MT6813_IIC_Send_Byte(data);
	if(MT6813_IIC_Wait_Ack())
	{
		MT6813_IIC_Stop();
		return 1;
	}
	MT6813_IIC_Stop();
	return 0;
}

u8 MT6813_Read_Byte(u8 addr, u8 reg)
{
	u8 res;
	MT6813_IIC_Start();
	MT6813_IIC_Send_Byte((addr<<1)|0);
	MT6813_IIC_Wait_Ack();
	MT6813_IIC_Send_Byte(reg);
	MT6813_IIC_Wait_Ack();
	MT6813_IIC_Start();
	MT6813_IIC_Send_Byte((addr<<1)|1);
	MT6813_IIC_Wait_Ack();
	res = MT6813_IIC_Read_Byte(0);
	MT6813_IIC_Stop();
	return res;
}

float MT6813_Get_Angle()
{
	u16 tmp = 0;
	float res;
	tmp  = (MT6813_Read_Byte(MT6813_ADDR, MT6813_REG1)|tmp)<<8;
	tmp |= MT6813_Read_Byte(MT6813_ADDR, MT6813_REG2);
	if(tmp & 0x02 || tmp>>1 == 0) return -1;
	res = (tmp>>2)*1.0*360/16384;
	return res;
}
