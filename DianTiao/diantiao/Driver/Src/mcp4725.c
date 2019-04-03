#include "mcp4725.h" 
#include "delay.h"
#include "myiic.h"	

//��ʼ��IIC�ӿ�
void MCP4725_Init(void)
{
	IIC_Init();
}

//ʹ�ÿ���ģʽд����дDAC�Ĵ���
void MCP4725_WriteBreakData_Voltage(u16 Vout)   //��ѹ��λmV
{
  u8 temp;
	u16 Dn;
	Dn = ( 4096 * Vout) / 5000;
	temp = (0x0F00 & Dn) >> 8;  //12λ����
	
	IIC_Start();
	
	IIC_Send_Byte(0xC2);      //����Ѱַ����������1100�� ��ַλA2��A1��A0Ϊ 0 �� 0 �� 1��-> 1100 0010
  IIC_Wait_Ack();	 

	IIC_Send_Byte(temp);
	IIC_Wait_Ack();	 
	
  IIC_Send_Byte(Dn);        //����8λ�͵�DAC�Ĵ���
	IIC_Wait_Ack();	
	
  IIC_Stop();//����һ��ֹͣ����  	

}

void MCP4725_WriteVelData_Voltage(u16 Vout)   //��ѹ��λmV
{
  u8 temp;
	u16 Dn;
	Dn = ( 4096 * Vout) / 5000;
	temp = (0x0F00 & Dn) >> 8;  //12λ����
	
	IIC_Start();
	
	IIC_Send_Byte(0xC0);      //����Ѱַ����������1100�� ��ַλA2��A1��A0Ϊ 0 �� 0 �� 1��-> 1100 0001
  IIC_Wait_Ack();	 
	
  IIC_Send_Byte(temp); 	
  IIC_Wait_Ack();	
	
  IIC_Send_Byte(Dn);        //����8λ�͵�DAC�Ĵ���
	IIC_Wait_Ack();	
	
  IIC_Stop();//����һ��ֹͣ����  	
//	delay_ms(10);	
}


