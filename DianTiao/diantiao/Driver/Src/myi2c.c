#include "myi2c.h"
#include "delay.h"
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

//MT6813_IIC��ʼ��
void MT6813_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //ʹ��GPIOBʱ��
    
    //PH11,12��ʼ������
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_10;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//GPIO_SPEED_FAST;     //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    
    MT6813_IIC_SDA=1;
    MT6813_IIC_SCL=1;  
}

//����MT6813_IIC��ʼ�ź�
void MT6813_IIC_Start(void)
{
	SDA_OUT();     //sda�����
	MT6813_IIC_SDA=1;	  	  
	MT6813_IIC_SCL=1;
	delay_us(4);
 	MT6813_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	MT6813_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����MT6813_IICֹͣ�ź�
void MT6813_IIC_Stop(void)
{
	SDA_OUT();//sda�����
	MT6813_IIC_SCL=0;
	MT6813_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	MT6813_IIC_SCL=1; 
	delay_us(4);			
	MT6813_IIC_SDA=1;//����I2C���߽����ź�				   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 MT6813_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	MT6813_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//MT6813_IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void MT6813_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    MT6813_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        MT6813_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		MT6813_IIC_SCL=1;
		delay_us(2); 
		MT6813_IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 MT6813_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        MT6813_IIC_NAck();//����nACK
    else
        MT6813_IIC_Ack(); //����ACK   
    return receive;
}


