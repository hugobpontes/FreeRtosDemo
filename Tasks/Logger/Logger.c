/*
 * Logger.c
 *
 *  Created on: Oct 1, 2023
 *      Author: hugo
 */
#include "FreeRTOS.h"
#include "task.h"

#include "trice.h"
#include "lwrb/lwrb.h"

#include "Common.h"

#define LOG_BUFFER_SIZE 256

static uint8_t LogBufferStorage[LOG_BUFFER_SIZE];
static TaskHandle_t hTaskLogger;
lwrb_t LogBuffer;


static void TaskLogger(void* pvParams){
	while (1){

	}
}


void LoggerInit(){
	lwrb_init(&LogBuffer, LogBufferStorage, LOG_BUFFER_SIZE);
	xTaskCreate(TaskLogger, "Logger", 128, NULL, 1, &hTaskLogger);
}
