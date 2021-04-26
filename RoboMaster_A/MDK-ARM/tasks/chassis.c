#include "chassis.h"

int16_t 	chassis_iq[4] = {0,0,0,0};

void calc_mecanum(float vx, float vy, float omega, const int max_spd_of_each_wheel, int16_t speed[])
{
	int16_t buf[4] = {0};
	int32_t local_i =  0 ;
	float temp_max_speed = 0.0f;
	float	rate = 0.0f;
	
	vx 	   = vx >  CHASSIS_VX_MAX_SPEED ?  CHASSIS_VX_MAX_SPEED : vx;
	vx 	   = vx < -CHASSIS_VX_MAX_SPEED ? -CHASSIS_VX_MAX_SPEED : vx;
	vy 	   = vy >  CHASSIS_VY_MAX_SPEED ?  CHASSIS_VY_MAX_SPEED : vy;
	vy 	   = vy < -CHASSIS_VY_MAX_SPEED ? -CHASSIS_VY_MAX_SPEED : vy;	
	omega  = omega >  CHASSIS_OMEGA_MAX_SPEED ?  CHASSIS_OMEGA_MAX_SPEED : omega;
	omega  = omega < -CHASSIS_OMEGA_MAX_SPEED ? -CHASSIS_OMEGA_MAX_SPEED : omega;
	
	buf[0] = -vy - vx + omega;
	buf[1] =  vy - vx + omega;
	buf[2] =  vy + vx + omega;
	buf[3] = -vy + vx + omega;

	for (local_i=0; local_i<4; local_i++)
	{
	  if (abs(buf[local_i]) > temp_max_speed)
		{
		  temp_max_speed = abs(buf[local_i]);
		}
	}
	
	if (temp_max_speed > max_spd_of_each_wheel)
	{
	    rate = max_spd_of_each_wheel / temp_max_speed;
		for (local_i=0; local_i<4; local_i++)
		{
		  buf[local_i] *= rate;
		}
	}	
	memcpy(speed, buf, sizeof(int16_t) * 4);	
}

void ChassisTask(void const * argument)
{
  /* USER CODE BEGIN ChassisTask */
	
  /* Infinite loop */
  while(1)
  {
	  
	  send_iq_by_can1(chassis_iq);
	  osDelay(5);
  }
  /* USER CODE END ChassisTask */
}

void RC_chassis_control(void){
	
}


void KM_chassis_control(void){
	
}










