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

void CommonInit();

extern SemaphoreHandle_t hBinSmph1000;


#endif /* COMMON_COMMON_H_ */
