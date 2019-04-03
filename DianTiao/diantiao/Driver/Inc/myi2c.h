#ifndef _MYI2C_H
#define _MYI2C_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//MT6813_IIC驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}
//IO操作
#define MT6813_IIC_SCL   PBout(10) //SCL
#define MT6813_IIC_SDA   PBout(11) //SDA
#define MT6813_READ_SDA  PBin(11)  //输入SDA
//MT6813_IIC所有操作函数
void MT6813_IIC_Init(void);                //初始化MT6813_IIC的IO口				 
void MT6813_IIC_Start(void);				//发送MT6813_IIC开始信号
void MT6813_IIC_Stop(void);	  			//发送MT6813_IIC停止信号
void MT6813_IIC_Send_Byte(uint8_t txd);			//MT6813_IIC发送一个字节
uint8_t MT6813_IIC_Read_Byte(unsigned char ack);//MT6813_IIC读取一个字节
uint8_t MT6813_IIC_Wait_Ack(void); 				//MT6813_IIC等待ACK信号
void MT6813_IIC_Ack(void);					//MT6813_IIC发送ACK信号
void MT6813_IIC_NAck(void);				//MT6813_IIC不发送ACK信号

void MT6813_IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t MT6813_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	 
#endif

