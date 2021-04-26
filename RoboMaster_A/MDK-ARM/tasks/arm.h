#ifndef ARM_H
#define ARM_H

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "string.h"
#include "stdlib.h"

#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "bsp_uart.h"
#include "bsp_can.h"
#include "pid.h"
#include "control.h"
#include "chassis.h"


void send_arm_iq_by_can_1(int16_t iq[8]);
void send_arm_iq_by_can_2(int16_t iq[8]);
void RC_arm_control(void);		//Ò£¿ØÆ÷¿ØÖÆ
void KM_arm_control(void);		//¼üÊó¿ØÖÆ

#endif

