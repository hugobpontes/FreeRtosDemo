/*
 * Trace.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "trice.h"

static TaskHandle_t hTaskTrace;


static void TaskTrace(void* pvParams){
	while (1)
	{
		TriceTransfer();
		if (TriceOutDepthUartA()){
			triceServeTransmitUartA();
		}
	}
}


void TraceInit(){
    TriceInit();
	xTaskCreate(TaskTrace, "Trace", 128, NULL, 1, &hTaskTrace);
}
