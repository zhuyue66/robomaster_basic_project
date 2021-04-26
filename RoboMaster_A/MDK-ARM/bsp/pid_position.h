#ifndef _PID_POSITION
#define _PID_POSITION

#include "main.h"

#define LIMIT_MIN_MAX(x,min,max) (x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

typedef struct _pid_position_t
{
  float kp;		//定义比例系数
  float ki;		//定义积分系数
  float kd;		//定义微分系数
  float i_max;
  float out_max;
  float count;
	
  float set_angel;      	// 定义设定角度
  float actual_angel; 	// 定义实际角度
  float err;   	// 定义当前误差
  float err_last;   	// 定义过去误差

  float p_out;
  float i_out;
  float d_out;
  float output;
}pid_position_t;

void pid_position_init(pid_position_t *pid,float kp,float ki,
											 float kd,float i_max,float out_max);
float pid_position(pid_position_t *pid, float set_angel, float actual_angel);

#endif



