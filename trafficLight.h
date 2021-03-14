#ifndef __trafficLight_H
#define __trafficLight_H

#include "cube_hal.h"
#include "x_nucleo_plc01a1.h"

#define System                  0
#define Ready                   1
#define Go                      2
#define Stop                    3
#define Attention               4
#define Drive                   5
#define Request  HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)
#define cycleTime               10
#define cycleCoefficient        1000/cycleTime

void loop(void);
void trafficLightState(void);

#endif

