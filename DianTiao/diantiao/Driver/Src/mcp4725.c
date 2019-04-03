#include "mcp4725.h" 
#include "delay.h"
#include "myiic.h"	

//初始化IIC接口
void MCP4725_Init(void)
{
	IIC_Init();
}

//使用快速模式写命令写DAC寄存器
void MCP4725_WriteBreakData_Voltage(u16 Vout)   //电压单位mV
{
  u8 temp;
	u16 Dn;
	Dn = ( 4096 * Vout) / 5000;
	temp = (0x0F00 & Dn) >> 8;  //12位数据
	
	IIC_Start();
	
	IIC_Send_Byte(0xC2);      //器件寻址，器件代吗：1100； 地址位A2，A1，A0为 0 ， 0 ， 1；-> 1100 0010
  IIC_Wait_Ack();	 

	IIC_Send_Byte(temp);
	IIC_Wait_Ack();	 
	
  IIC_Send_Byte(Dn);        //将低8位送到DAC寄存器
	IIC_Wait_Ack();	
	
  IIC_Stop();//产生一个停止条件  	

}

void MCP4725_WriteVelData_Voltage(u16 Vout)   //电压单位mV
{
  u8 temp;
	u16 Dn;
	Dn = ( 4096 * Vout) / 5000;
	temp = (0x0F00 & Dn) >> 8;  //12位数据
	
	IIC_Start();
	
	IIC_Send_Byte(0xC0);      //器件寻址，器件代吗：1100； 地址位A2，A1，A0为 0 ， 0 ， 1；-> 1100 0001
  IIC_Wait_Ack();	 
	
  IIC_Send_Byte(temp); 	
  IIC_Wait_Ack();	
	
  IIC_Send_Byte(Dn);        //将低8位送到DAC寄存器
	IIC_Wait_Ack();	
	
  IIC_Stop();//产生一个停止条件  	
//	delay_ms(10);	
}


