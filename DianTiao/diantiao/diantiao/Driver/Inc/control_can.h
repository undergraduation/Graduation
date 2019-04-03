#ifndef __CONTROL_CAN_H__
#define __CONTROL_CAN_H__
#include "stm32f1xx_hal.h"
extern uint8_t CAN_RX[8];
extern uint8_t CAN_TX[2];
void CAN_Config_Filter(void);
uint8_t CAN_SendMessage(uint16_t id, uint8_t *pData,uint8_t length);
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan);
#endif
