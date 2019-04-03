#include "control_can.h"
extern CAN_HandleTypeDef hcan;
CanTxMsgTypeDef				CANTxMsg;
CanRxMsgTypeDef				CANRxMsg;
uint8_t CAN_RX[8];
uint8_t CAN_TX[2]={1,5};
uint8_t CAN_RX_Flag = 0;
void CAN_Config_Filter()
{
	hcan.pRx1Msg = &CANRxMsg;
	hcan.pTxMsg = &CANTxMsg;
	CAN_FilterConfTypeDef  sFilterConfig;
	sFilterConfig.FilterNumber = 0;		//��CAN�˲���ʹ�ñ��
//	sFilterConfig.BankNumber = 14;		//˫CAN ���õĹ�������ʼ��� F1û��
	
	sFilterConfig.FilterFIFOAssignment = CAN_FIFO1;	//ʹ������1
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //����λģʽ
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //32λ
	
	//�κ�ID������ͨ��
	sFilterConfig.FilterIdHigh = 0;
	sFilterConfig.FilterIdLow = 0;				//ID
	sFilterConfig.FilterMaskIdHigh = 0;
	sFilterConfig.FilterMaskIdLow = 0;		//����
	
	sFilterConfig.FilterActivation = ENABLE; //ʹ�ܹ�����
	
	HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);	// ��ʼ��������
}

uint8_t CAN_SendMessage(uint16_t id, uint8_t *pData,uint8_t length)
{
	assert_param(length<=8);
	
	hcan.pTxMsg->StdId = id;					//��׼��ʶ��
	hcan.pTxMsg->ExtId = 0;				//��չ��ʶ��
	hcan.pTxMsg->IDE = CAN_ID_STD; 		//��׼֡
	hcan.pTxMsg->RTR = CAN_RTR_DATA; //����֡
	hcan.pTxMsg->DLC = length;			//���ݳ���
	for(int i=0; i<length; i++)
		hcan.pTxMsg->Data[i] = pData[i];	//��������
	
	if(HAL_CAN_Transmit(&hcan, 10) != HAL_OK) return 0;
	return 1;	
}

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV1 | CAN_IT_FMP1);
	if(hcan->Instance == CAN1)
	{
		switch(hcan->pRx1Msg->StdId)
		{
			case 0: break;
			default: break;
		}

		for(int i=0; i< hcan->pRx1Msg->DLC; i++)
		{
			CAN_RX[i] = hcan->pRx1Msg->Data[i];
		}
		CAN_RX_Flag = 1;
	}	
}
