#include "Driver_USART.h"               // ::CMSIS Driver:USART
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include <stdio.h>

#ifndef GPS_H
#define GPS_H

extern ARM_DRIVER_USART Driver_USART3;

void gps_init();
void event_UART(uint32_t event);

void gps_getData(float *lat, float *lon, char *h, char *m, float *s);
#endif