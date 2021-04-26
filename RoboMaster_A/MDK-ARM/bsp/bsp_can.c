#include "bsp_can.h"

CAN_RxHeaderTypeDef moto_rx_head_can1;
CAN_RxHeaderTypeDef moto_rx_head_can2;
uint8_t moto_rx_data_can1[8] = {0};
uint8_t moto_rx_data_can2[8] = {0};

Moto3508_measure_s  chassis_moto[4] = {0};
Moto6020_measure_s  yaw_moto = {0};
Moto6020_measure_s  pit_moto = {0};

uint32_t tx_mailbox = CAN_TX_MAILBOX0;

void send_iq_by_can1(int16_t iq[4])
{
	CAN_TxHeaderTypeDef tx_head = {0};
	tx_head.StdId = CAN_CONTROL_ID_BASE;
	tx_head.IDE = CAN_ID_STD;
	tx_head.RTR = CAN_RTR_DATA;
	tx_head.DLC = 0x08;
	
	uint8_t buff[8] = {0};
	
	buff[0] = iq[0] >> 8;
	buff[1] = iq[0];
	buff[2] = iq[1] >> 8;
	buff[3] = iq[1];
	buff[4] = iq[2] >> 8;
	buff[5] = iq[2];
	buff[6] = iq[3] >> 8;
	buff[7] = iq[3];
    HAL_CAN_AddTxMessage(&hcan1, &tx_head, buff, &tx_mailbox);
}

void send_iq_by_can1_ex(int16_t iq[4])
{	
	CAN_TxHeaderTypeDef tx_head = {0};
	tx_head.StdId = CAN_CONTROL_ID_EXTEND;
	tx_head.IDE = CAN_ID_STD;
	tx_head.RTR = CAN_RTR_DATA;
	tx_head.DLC = 0x08;
	
	uint8_t buff[8] = {0};
	
	buff[0] = iq[0] >> 8;
	buff[1] = iq[0];
	buff[2] = iq[1] >> 8;
	buff[3] = iq[1];
	buff[4] = iq[2] >> 8;
	buff[5] = iq[2];
	buff[6] = iq[3] >> 8;
	buff[7] = iq[3];
    HAL_CAN_AddTxMessage(&hcan1, &tx_head, buff, &tx_mailbox);
}

void send_iq_by_can2(int16_t iq[4])
{
	CAN_TxHeaderTypeDef tx_head = {0};
	tx_head.StdId = CAN_CONTROL_ID_BASE;
	tx_head.IDE = CAN_ID_STD;
	tx_head.RTR = CAN_RTR_DATA;
	tx_head.DLC = 0x08;
	
	uint8_t buff[8] = {0};
	
	buff[0] = iq[0] >> 8;
	buff[1] = iq[0];
	buff[2] = iq[1] >> 8;
	buff[3] = iq[1];
	buff[4] = iq[2] >> 8;
	buff[5] = iq[2];
	buff[6] = iq[3] >> 8;
	buff[7] = iq[3];
    HAL_CAN_AddTxMessage(&hcan2, &tx_head, buff, &tx_mailbox);
}

void send_iq_by_can2_ex(int16_t iq[4])
{	
	CAN_TxHeaderTypeDef tx_head = {0};
	tx_head.StdId = CAN_CONTROL_ID_EXTEND;
	tx_head.IDE = CAN_ID_STD;
	tx_head.RTR = CAN_RTR_DATA;
	tx_head.DLC = 0x08;
	
	uint8_t buff[8] = {0};
	
	buff[0] = iq[0] >> 8;
	buff[1] = iq[0];
	buff[2] = iq[1] >> 8;
	buff[3] = iq[1];
	buff[4] = iq[2] >> 8;
	buff[5] = iq[2];
	buff[6] = iq[3] >> 8;
	buff[7] = iq[3];
    HAL_CAN_AddTxMessage(&hcan2, &tx_head, buff, &tx_mailbox);
}

void send_capacity_power_by_can(int16_t temPower)
{
	CAN_TxHeaderTypeDef cap_tx_head = {0};
	cap_tx_head.StdId = 0x210;
	cap_tx_head.IDE = CAN_ID_STD;
	cap_tx_head.RTR = CAN_RTR_DATA;
	cap_tx_head.DLC = 0x08;
	
	uint8_t buff[8] = {0};
	
	//赋值功率
	buff[0] = temPower >> 8;
	buff[1] = temPower;
	HAL_CAN_AddTxMessage(&hcan1, &cap_tx_head, buff, &tx_mailbox);
}

void can_user_init(CAN_HandleTypeDef* hcan )
{
  CAN_FilterTypeDef  can_filter;
	
  can_filter.FilterBank = 0;
  can_filter.FilterMode =  CAN_FILTERMODE_IDMASK;  	
  can_filter.FilterScale = CAN_FILTERSCALE_32BIT;
  can_filter.FilterIdHigh = 0;
  can_filter.FilterIdLow  = 0;
  can_filter.FilterMaskIdHigh = 0;
  can_filter.FilterMaskIdLow  = 0;
  can_filter.FilterFIFOAssignment = CAN_RX_FIFO0;
  can_filter.FilterActivation = ENABLE;
  can_filter.SlaveStartFilterBank  = 14;
   
  HAL_CAN_ConfigFilter(hcan, &can_filter);
  HAL_CAN_Start(hcan);
  HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
		
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &moto_rx_head_can1, moto_rx_data_can1);

		switch(moto_rx_head_can1.StdId)
		{
			case CAN_3508MOTO1_ID:
			case CAN_3508MOTO2_ID:
			case CAN_3508MOTO3_ID:
			case CAN_3508MOTO4_ID:
			{
				static uint8_t i;
				i = moto_rx_head_can1.StdId - CAN_3508MOTO1_ID;
				chassis_moto[i].msg_cnt++ <= 50	? get_moto3508_offset(&chassis_moto[i], moto_rx_data_can1) : get_moto3508_measure(&chassis_moto[i], moto_rx_data_can1);
			}
			break;
		}
	}else if(hcan->Instance == CAN2)
	{
		
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &moto_rx_head_can1, moto_rx_data_can2);
		switch(moto_rx_head_can2.StdId)
		{
			case 1:
				break;
			default:
				break;
		}
	}
}

// 电机的上电角度
void get_moto3508_offset(Moto3508_measure_s *ptr, uint8_t buff[])
{
	ptr->now_angle = (buff[0]<<8 | buff[1]);
	ptr->offset_angle = ptr->now_angle;
}

void get_moto2006_offset(Moto2006_measure_s *ptr, uint8_t buff[])
{
	ptr->now_angle = (buff[0]<<8 | buff[1]);
	ptr->offset_angle = ptr->now_angle;
}

// 电机的各种信息
void get_moto3508_measure(Moto3508_measure_s *ptr, uint8_t buff[])
{
	ptr->last_angle = ptr->now_angle;
	
	ptr->now_angle = buff[0]<<8 | buff[1];
	ptr->get_speed = (buff[2]<<8 | buff[3]);
	ptr->get_current = buff[4]<<8 | buff[5];
	ptr->temperature = buff[6];
	
	if(ptr->now_angle - ptr->last_angle > 4096) // 倒转
		ptr->round_cnt --;	
	else if (ptr->now_angle - ptr->last_angle < -4096)// 正转
		ptr->round_cnt ++;
	
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->now_angle - ptr->offset_angle;	
}


void get_moto6020_measure(Moto6020_measure_s *ptr, uint8_t buff[])
{
	ptr->last_angle = ptr->now_angle;
	
	ptr->now_angle = buff[0]<<8 | buff[1];
	ptr->get_speed = (buff[2]<<8 | buff[3]);
	ptr->get_current = buff[4]<<8 | buff[5];
	ptr->temperature = buff[6];
	
	if(ptr->now_angle - ptr->last_angle > 4096)
		ptr->round_cnt --;
	else if (ptr->now_angle - ptr->last_angle < -4096)
		ptr->round_cnt ++;
	
	ptr->total_angle = ptr->round_cnt * 8192 + ptr->now_angle ;	
}

void get_moto2006_measure(Moto2006_measure_s *ptr, uint8_t buff[])
{
	ptr->last_angle = ptr->now_angle;
	
	ptr->now_angle = (buff[0]<<8 | buff[1]);
	ptr->get_speed = (buff[2]<<8 | buff[3]);
	ptr->get_current = (buff[4]<<8 | buff[5]);
	ptr->temperature = buff[6];
	
	if(ptr->now_angle - ptr->last_angle > 4096)
		ptr->round_cnt --;
	else if (ptr->now_angle - ptr->last_angle < -4096)
		ptr->round_cnt ++;

	ptr->total_angle = ptr->round_cnt * 8192 + ptr->now_angle - ptr->offset_angle;
	ptr->total_radian_angle = (ptr->total_angle)/819.0f; //22.75*36=819,转化为0-360°
}




