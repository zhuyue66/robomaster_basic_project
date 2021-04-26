#include "arm.h"

int16_t 	arm_iq[8] = {0};
uint8_t 	arm_tx_data_1[8] 		= {0};
uint8_t 	arm_tx_data_2[8] 		= {0};
uint32_t	arm_tx_mailbox 		= CAN_TX_MAILBOX0;


int16_t except_yaw_angle;        //yaw轴期望角度
int16_t except_pit_angle;        //pitch轴期望角度，电流由底盘任务can1发送
int16_t except_axis1_angel;      //第一自由度两个3508电机期望角度
int16_t except_axis2_angel;      //第二自由度两个2006电机期望角度
int16_t except_axis3_angel;      //第三自由度一个3508电机期望角度
int16_t except_axis4_claw_angel; //第四自由度爪子期望角度


void send_arm_iq_by_can_1(int16_t iq[8])
{	
	CAN_TxHeaderTypeDef arm_tx_head_1 = {0};
	arm_tx_head_1.StdId = 0x200;
	arm_tx_head_1.ExtId = 0x000;
	arm_tx_head_1.IDE = CAN_ID_STD;
	arm_tx_head_1.RTR = CAN_RTR_DATA;
	arm_tx_head_1.DLC = 0x08;
	
	arm_tx_data_1[0] = iq[0] >> 8;
	arm_tx_data_1[1] = iq[0]	 ;
	arm_tx_data_1[2] = iq[1] >> 8;
	arm_tx_data_1[3] = iq[1]     ;
	arm_tx_data_1[4] = iq[2] >> 8;
	arm_tx_data_1[5] = iq[2]     ;
	arm_tx_data_1[6] = iq[3] >> 8;
	arm_tx_data_1[7] = iq[3]     ;
    HAL_CAN_AddTxMessage(&hcan2, &arm_tx_head_1, arm_tx_data_1, &arm_tx_mailbox);
}

void send_arm_iq_by_can_2(int16_t iq[8])
{
	CAN_TxHeaderTypeDef arm_tx_head_2 = {0};
	arm_tx_head_2.StdId = 0x1ff;
	arm_tx_head_2.ExtId = 0x000;
	arm_tx_head_2.IDE = CAN_ID_STD;
	arm_tx_head_2.RTR = CAN_RTR_DATA;
	arm_tx_head_2.DLC = 0x08;
	
	arm_tx_data_2[0] = iq[4] >> 8;
	arm_tx_data_2[1] = iq[4]	 ;
	arm_tx_data_2[2] = iq[5] >> 8;
	arm_tx_data_2[3] = iq[5]     ;
	arm_tx_data_2[4] = iq[6] >> 8;
	arm_tx_data_2[5] = iq[6]     ;
	arm_tx_data_2[6] = iq[7] >> 8;
	arm_tx_data_2[7] = iq[7]     ;
	
	HAL_CAN_AddTxMessage(&hcan2, &arm_tx_head_2, arm_tx_data_2, &arm_tx_mailbox);
}


void ArmTask(void const * argument)
{
	while(1)
	{
	  //遥控器控制模式，遥控器没有离线
	  if(workState == RC_state && debus_off_line==0)
	  {
		  RC_arm_control();
	  }
	  else if(workState == KM_state && debus_off_line==0)
	  {
		  KM_arm_control();
	  }
	  else
	  {
		  system_protect();
	  }
	  
	  
	  pid_regulator(&axis1_3508_angle_pid, except_axis1_angel, axis1_3508_l.total_angle);
	  pid_regulator(&axis2_2006_angle_pid, except_axis2_angel, axis2_2006_l.total_angle);
	  pid_regulator(&axis3_3508_angle_pid, except_axis3_angel, axis3_3508.total_angle);
	  pid_regulator(&axis4_claw_2006_angle_pid, except_axis4_claw_angel, axis4_claw_2006.total_angle);
	  pid_regulator(&yaw_6020_angle_pid, except_yaw_angle, yaw_6020.total_angle);
	  pid_regulator(&pit_3508_angle_pid, except_pit_angle, pit_3508_l.total_angle);
	  
	  
	  arm_iq[0] =  axis1_3508_angle_pid.delta_out;
	  arm_iq[1] = -axis1_3508_angle_pid.delta_out;
	  arm_iq[2] =  axis2_2006_angle_pid.delta_out;
	  arm_iq[3] = -axis2_2006_angle_pid.delta_out;
	  arm_iq[4] =  axis3_3508_angle_pid.delta_out;
	  arm_iq[5] =  axis4_claw_2006_angle_pid.delta_out;
	  arm_iq[6] =  yaw_6020_angle_pid.delta_out;
	  
	  chassis_iq[4] =  pit_3508_omega_pid.delta_out;// 云台抬升由底盘任务CAN1发送
	  chassis_iq[5] = -pit_3508_omega_pid.delta_out;
	  
	  send_arm_iq_by_can_1(arm_iq);
	  send_arm_iq_by_can_2(arm_iq);
	  
	}
}

void RC_arm_control(void)
{
	if(a_flag == arm_yaw_pit)
	{
		except_yaw_angle += rc.ch3 * 0.001;
		except_pit_angle += rc.ch4 * 0.001;
	}
	else if(a_flag == arm_12)
	{
		except_axis1_angel +=  rc.ch4 * 0.001;
		except_axis2_angel += -rc.ch3 * 0.001;
	}
	else if(a_flag == arm_1234)
	{
		except_axis1_angel = rc.ch4 * 0.001;
		except_axis2_angel = -rc.ch3 * 0.001;
		except_axis3_angel = -rc.ch2 * 0.001;
		except_axis4_claw_angel = rc.ch1 * 0.001;
	}
	
}


void KM_arm_control(void)
{
	
}
