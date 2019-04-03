#ifndef _MYI2C_H
#define _MYI2C_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//MT6813_IIC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO��������
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//IO����
#define MT6813_IIC_SCL   PBout(10) //SCL
#define MT6813_IIC_SDA   PBout(11) //SDA
#define MT6813_READ_SDA  PBin(11)  //����SDA
//MT6813_IIC���в�������
void MT6813_IIC_Init(void);                //��ʼ��MT6813_IIC��IO��				 
void MT6813_IIC_Start(void);				//����MT6813_IIC��ʼ�ź�
void MT6813_IIC_Stop(void);	  			//����MT6813_IICֹͣ�ź�
void MT6813_IIC_Send_Byte(uint8_t txd);			//MT6813_IIC����һ���ֽ�
uint8_t MT6813_IIC_Read_Byte(unsigned char ack);//MT6813_IIC��ȡһ���ֽ�
uint8_t MT6813_IIC_Wait_Ack(void); 				//MT6813_IIC�ȴ�ACK�ź�
void MT6813_IIC_Ack(void);					//MT6813_IIC����ACK�ź�
void MT6813_IIC_NAck(void);				//MT6813_IIC������ACK�ź�

void MT6813_IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MT6813_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

