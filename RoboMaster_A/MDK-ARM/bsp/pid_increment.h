#ifndef _PID_INCREMENT
#define _PID_INCREMENT

#include "main.h"

#define LIMIT1_MIN_MAX(x,min,max) (x) = (((x)<=(min))?(min):(((x)>=(max))?(max):(x)))

typedef struct _pid_increment_t
{
  float kp;							//�������ϵ��
  float ki;							//�������ϵ��
  float kd;							//����΢��ϵ��
  float i_max;
  float out_max;
  float count;
	
  float set_speed;      //�����趨�Ƕ�
  float actual_speed; 	//����ʵ�ʽǶ�
  float err;   					//���嵱ǰ���
  float err_last;   		//������һ�����
	float err_llast;      //�������ϴ����

  float p_out;
  float i_out;
  float d_out;
  float output;
}pid_increment_t;

void pid_increment_init(pid_increment_t *pid,float kp,float ki,
												float kd,float i_max,float out_max);
float pid_increment(pid_increment_t *pid, float set_speed, float actual_speed);												
#endif

