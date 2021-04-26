#include "system.h"

uint16_t dbus_offline_cnt = 0;
uint16_t gro_off_line_cnt = 0;

void chassis_protect(void){
}

void system_protect(void){
	chassis_protect();
}

void system_reset(void){

}

