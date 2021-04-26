#include "pid.h"

Pid_s chassis_pid[4]   = {0};
Pid_s chassis_3508_rf_pid = {0}; //ÓÒÇ°
Pid_s chassis_3508_lf_pid = {0};
Pid_s chassis_3508_lb_pid = {0}; //×óºó
Pid_s chassis_3508_rb_pid = {0};

Pid_s yaw_angle_pid    = {0};
Pid_s yaw_omega_pid    = {0};
Pid_s pit_angle_pid    = {0};
Pid_s pit_omega_pid    = {0};
Pid_s pok_angle_pid    = {0};
Pid_s pok_omega_pid    = {0};
Pid_s follow_omega_pid = {0};


void pid_clear(Pid_s * pid)
{
	if (pid == NULL)
	{
		return;
	}
	
	pid->pout = pid->iout = pid->dout = 0.0f;
	pid->delta_out = pid->delta_u = pid->last_delta_out = 0.0f;
	pid->err[0] = pid->err[1] = pid->err[2] = 0.0f;
	pid->set[NOW] = 0.0f;
	pid->get[NOW] = 0.0f;
}


float pid_regulator(Pid_s* pid, float set_speed, float get_speed)
{
	pid->set[NOW] = set_speed ;
	pid->get[NOW] = get_speed ;	
	pid->err[NOW] = set_speed - get_speed;
	pid->pout = pid->p * pid->err[NOW];
	pid->iout = pid->i * pid->err[NOW];
	pid->dout = pid->d * (pid->err[NOW] - 2 * pid->err[LAST] + pid->err[LLAST]);
		
	abs_limit(&(pid->iout), pid->IntegralLimit);
	pid->delta_u = pid->pout + pid->iout + pid->dout;
	pid->delta_out = pid->delta_u;
	abs_limit(&(pid->delta_out), pid->MaxOutput);
	pid->last_delta_out = pid->delta_out;
	
	
	pid->err[LLAST] = pid->err[LAST];
	pid->err[LAST]  = pid->err[NOW];
	pid->get[LLAST] = pid->get[LAST];
	pid->get[LAST]  = pid->get[NOW];
	pid->set[LLAST] = pid->set[LAST];
	pid->set[LAST]  = pid->set[NOW];
	
	return pid->delta_out;
}


void abs_limit(float * x, float ABS_MAX)
{
	if (*x > ABS_MAX)
	{
		*x = ABS_MAX;
	}
	if (*x < (ABS_MAX * (-1.0)))
	{
		*x = ABS_MAX * (-1.0);
	}
}


void pid_param_init(Pid_s *pid, uint32_t intergral_limit, uint32_t max_output,float kp, float ki, float	kd)
{    
	pid->IntegralLimit = intergral_limit;
	pid->MaxOutput = max_output;
	
	pid->p = kp;
	pid->i = ki;
	pid->d = kd;    
}

void pid_reset(Pid_s	*pid, float kp, float ki, float kd)
{
	pid->p = kp;
	pid->i = ki;
	pid->d = kd;
}

void pid_struct_init(Pid_s* pid, uint32_t intergral_limit, uint32_t maxout, float kp, float ki, float kd)
{
	/*init function pointer*/
	pid->f_param_init = pid_param_init;
	pid->f_pid_reset = pid_reset;
	
	/*init pid param */
	pid->f_param_init(pid, intergral_limit, maxout, kp, ki, kd);
	pid->f_pid_reset(pid,kp,ki, kd);
}


void pid_parameter_init(void)
{
}
