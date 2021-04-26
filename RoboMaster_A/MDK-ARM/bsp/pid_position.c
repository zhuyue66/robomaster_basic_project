#include "pid_position.h"

void pid_position_init(pid_position_t *pid,float kp,float ki,
											 float kd,float i_max,float out_max)
{
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;								
}

float pid_position(pid_position_t *pid, float set_angel, float actual_angel)
{
  pid->set_angel = set_angel;
  pid->actual_angel = actual_angel;
  pid->err = (pid->set_angel)-(pid->actual_angel);

  
  pid->p_out  = (pid->kp) * (pid->err);
  pid->i_out += (pid->ki) * (pid->err);
  pid->d_out  = (pid->kd) * (pid->err - pid->err_last);
  LIMIT_MIN_MAX(pid->i_out, -pid->i_max, pid->i_max);
 
  pid->output = pid->p_out + pid->i_out + pid->d_out;
	pid->err_last = pid->err;	

  LIMIT_MIN_MAX(pid->output, -pid->out_max, pid->out_max);
  return pid->output;
}

