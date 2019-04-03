#include "myi2c.h"
#include "delay.h"
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

//MT6813_IIC初始化
void MT6813_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOB时钟
    
    //PH11,12初始化设置
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_10;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//GPIO_SPEED_FAST;     //快速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    MT6813_IIC_SDA=1;
    MT6813_IIC_SCL=1;  
}

//产生MT6813_IIC起始信号
void MT6813_IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	MT6813_IIC_SDA=1;	  	  
	MT6813_IIC_SCL=1;
	delay_us(4);
 	MT6813_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	MT6813_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生MT6813_IIC停止信号
void MT6813_IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	MT6813_IIC_SCL=0;
	MT6813_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	MT6813_IIC_SCL=1; 
	delay_us(4);			
	MT6813_IIC_SDA=1;//发送I2C总线结束信号				   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 MT6813_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	MT6813_IIC_SDA=1;delay_us(1);	   
	MT6813_IIC_SCL=1;delay_us(1);	 
	while(MT6813_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MT6813_IIC_Stop();
			return 1;
		}
	}
	MT6813_IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void MT6813_IIC_Ack(void)
{
	MT6813_IIC_SCL=0;
	SDA_OUT();
	MT6813_IIC_SDA=0;
	delay_us(2);
	MT6813_IIC_SCL=1;
	delay_us(2);
	MT6813_IIC_SCL=0;
}
//不产生ACK应答		    
void MT6813_IIC_NAck(void)
{
	MT6813_IIC_SCL=0;
	SDA_OUT();
	MT6813_IIC_SDA=1;
	delay_us(2);
	MT6813_IIC_SCL=1;
	delay_us(2);
	MT6813_IIC_SCL=0;
}					 				     
//MT6813_IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MT6813_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    MT6813_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        MT6813_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		MT6813_IIC_SCL=1;
		delay_us(2); 
		MT6813_IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 MT6813_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        MT6813_IIC_SCL=0; 
        delay_us(2);
		MT6813_IIC_SCL=1;
        receive<<=1;
        if(MT6813_READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        MT6813_IIC_NAck();//发送nACK
    else
        MT6813_IIC_Ack(); //发送ACK   
    return receive;
}


