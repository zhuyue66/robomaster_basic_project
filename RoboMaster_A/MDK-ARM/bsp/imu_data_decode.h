#ifndef __IMU_DATA_DECODE_H__
#define __IMU_DATA_DECODE_H__

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stm32f4xx_hal.h"


extern int32_t gro_usart_cnt;
extern float gro_angle_sum;
extern float gro_angle_average;


int imu_data_decode_init(void);
int get_raw_acc(int16_t* a);
int get_raw_gyo(int16_t* g);
int get_raw_mag(int16_t* m);
int get_id(uint8_t *user_id);
int get_eular(float* e);
int get_quat(float* q);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/*usart interrupt*/
extern float eular[3];
void uart8_IDLE_Rx_handler(UART_HandleTypeDef *huart);
void IMU_usart8_init(void);

#endif


