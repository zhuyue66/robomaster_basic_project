#include "pid_increment.h"

void pid_increment_init(pid_increment_t *pid,float kp,float ki, float kd,float i_max,float out_max)
{
	
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;
}

float pid_increment(pid_increment_t *pid, float set_angel, float actual_angel)
{
  pid->set_speed = set_angel;
  pid->actual_speed = actual_angel;
  pid->err = (pid->set_speed) - (pid->actual_speed);

  pid->p_out  = (pid->kp) * (pid->err - pid->err_last);
  pid->i_out  = (pid->ki) * (pid->err);
  pid->d_out  = (pid->kd) * (pid->err - 2 * (pid->err_last) + pid->err_llast);
  LIMIT1_MIN_MAX(pid->i_out, -pid->i_max, pid->i_max);
 
  pid->output = pid->p_out + pid->i_out + pid->d_out;
	
	pid->err_last = pid->err;
	pid->err_llast = pid->err_last;
  LIMIT1_MIN_MAX(pid->output, -pid->out_max, pid->out_max);
  return pid->output;
}

