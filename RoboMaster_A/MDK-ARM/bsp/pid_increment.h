#ifndef _PID_INCREMENT
#define _PID_INCREMENT

#include "main.h"

#define LIMIT1_MIN_MAX(x,min,max) (x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

typedef struct _pid_increment_t
{
  float kp;							//定义比例系数
  float ki;							//定义积分系数
  float kd;							//定义微分系数
  float i_max;
  float out_max;
  float count;
	
  float set_speed;      //定义设定角度
  float actual_speed; 	//定义实际角度
  float err;   					//定义当前误差
  float err_last;   		//定义上一次误差
	float err_llast;      //定义上上次误差

  float p_out;
  float i_out;
  float d_out;
  float output;
}pid_increment_t;

void pid_increment_init(pid_increment_t *pid,float kp,float ki,
												float kd,float i_max,float out_max);
float pid_increment(pid_increment_t *pid, float set_speed, float actual_speed);												
#endif

