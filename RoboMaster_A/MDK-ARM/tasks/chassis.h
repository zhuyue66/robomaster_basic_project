#ifndef CHASSIS_H
#define CHASSIS_H

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

#define CHASSIS_VX_MAX_SPEED   	  8000
#define CHASSIS_VY_MAX_SPEED      8000
#define CHASSIS_OMEGA_MAX_SPEED   5000

void calc_mecanum(float vx, float vy, float omega, const int max_spd_of_each_wheel, int16_t speed[]);
void RC_chassis_control(void);
void KM_chassis_control(void);

#endif



