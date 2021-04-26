/****************************************************************************
 *  Copyright (C) 2018 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __BSP_CAN
#define __BSP_CAN

#include "can.h"

#define FEEDBACK_ID_BASE      0x200
#define CAN_CONTROL_ID_BASE   0x200
#define CAN_CONTROL_ID_EXTEND 0x1ff
#define MOTOR_MAX_NUM         10

typedef struct 
{
	uint32_t    msg_cnt;
	uint16_t	offset_angle;//上电角度
	
	int16_t  	set_speed;/* rpm */
	int16_t	 	get_speed;/* rpm */
	
	int32_t   	set_angle;
	uint16_t 	now_angle; 
  
	uint16_t 	last_angle;	 
	int32_t		round_cnt;
	int32_t		total_angle;


	int16_t  	set_current;/* -16384~16384 map to -20~20A */
	int16_t  	get_current;/* -16384~16384 map to -20~20A */	
	
	uint8_t   temperature;
}Moto3508_measure_s;

typedef struct 
{
	uint32_t  	msg_cnt;
	int16_t   	center_offset;
	int16_t   	relative_pos;
	int16_t   	reference_pos;
	
	float    	 set_angle;
	int16_t 	now_angle;   
	int16_t 	last_angle;	
	
	int16_t	 	set_speed;
	int16_t	 	get_speed;
	
	int16_t  	set_current;
	int16_t  	get_current;

	int32_t   	total_angle;
	int32_t		round_cnt;
	uint8_t   	temperature;
}Moto6020_measure_s;

typedef struct 
{	
	uint32_t  	msg_cnt;
	uint16_t	offset_angle;
	
	float	 	set_angle;
	uint16_t 	now_angle; 
  
	uint16_t 	last_angle;	 
	int32_t		round_cnt;
	
	float		total_radian_angle;
	int32_t		total_angle;
	
	int16_t	 	set_speed;/* rpm */
	int16_t	 	get_speed;/* rpm */
	
	int16_t  	set_current;
	int16_t  	get_current;
	
	uint8_t     temperature;
}Moto2006_measure_s;


typedef enum
{	
	CAN_3508MOTO1_ID = 0x201,// 底盘
	CAN_3508MOTO2_ID = 0x202,
	CAN_3508MOTO3_ID = 0x203,
	CAN_3508MOTO4_ID = 0x204,
	
	CAN_YAW_FEEDBACK_ID  = 0x205,//云台
	CAN_PIT_FEEDBACK_ID  = 0x206,
	
	CAN_POKE_FEEDBACK_ID = 0x207,//拨弹
	
	CAN_SUPER_CAP_ID = 0x211,//超级电容
}CAN_Message_ID;

void get_moto3508_offset(Moto3508_measure_s *ptr, uint8_t buff[]);
void get_moto2006_offset(Moto2006_measure_s *ptr, uint8_t buff[]);
void get_moto3508_measure(Moto3508_measure_s *ptr, uint8_t buff[]);
void get_moto2006_measure(Moto2006_measure_s *ptr, uint8_t buff[]);
void get_moto6020_measure(Moto6020_measure_s *ptr, uint8_t buff[]);

void send_iq_by_can1(int16_t iq[8]);
void send_iq_by_can1_ex(int16_t iq[8]);
void send_iq_by_can2(int16_t iq[8]);
void send_iq_by_can2_ex(int16_t iq[8]);
void send_capacity_power_by_can(int16_t temPower);

void can_user_init(CAN_HandleTypeDef* hcan);

extern Moto3508_measure_s chassis_moto[4];
extern Moto6020_measure_s yaw_moto ;
extern Moto6020_measure_s pit_moto ;
extern Moto2006_measure_s pok_moto ;
extern float PowerData[4];

#endif
