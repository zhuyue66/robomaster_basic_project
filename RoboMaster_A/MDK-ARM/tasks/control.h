#ifndef CONTROL_H
#define CONTROL_H

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


enum{
	RC_UP = 1,
	RC_MI = 3,
	RC_DN = 2,
};

typedef enum
{
	stop_state = -1,
	RC_state = 0,
	KM_state = 1,
}WorkState_e;

#endif



