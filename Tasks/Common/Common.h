/*
 * Common.h
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "event_groups.h"


void CommonInit();

extern SemaphoreHandle_t hBinSmph1000;
extern EventGroupHandle_t hEvGrp250_500;

#define kTmr250EvMsk 0x0001
#define kTmr500EvMsk 0x0002

#endif /* COMMON_COMMON_H_ */
