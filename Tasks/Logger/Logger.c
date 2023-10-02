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
#include "Logger.h"

#define LOG_BUFFER_SIZE 256
#define LOG_CHUNK_SIZE 1

#define INBOX_SIZE 20


static uint8_t LogBufferStorage[LOG_BUFFER_SIZE];
static uint8_t TempLogBuffer[LOG_CHUNK_SIZE];
static TaskHandle_t hTaskLogger;
lwrb_t LogBuffer;

SemaphoreHandle_t hLoggerMutex;
static StaticSemaphore_t LoggerMutexBuffer;

QueueHandle_t hLoggerInbox;
static StaticQueue_t LoggerInboxBuffer;
static uint8_t LoggerInboxStorage[INBOX_SIZE* sizeof(LoggerMsg_t)];

#define TICKS_TO_WAIT_FOR_LOGGER_MSG 2000

static void TaskLogger(void* pvParams){

	LoggerMsg_t RxLoggerMsg;
	while (1){
		if (xQueueReceive(hLoggerInbox,&RxLoggerMsg,TICKS_TO_WAIT_FOR_LOGGER_MSG) == pdTRUE){
			TRICE( ID(7470), "RECEIVE: Task %d wants me to read %d bytes from log buffer \n",RxLoggerMsg.SenderId,RxLoggerMsg.Size);
			lwrb_read(&LogBuffer, TempLogBuffer,RxLoggerMsg.Size);
			for (int idx = 0;idx<RxLoggerMsg.Size;idx++){
				TRICE( ID(5024), "RECEIVE: BYTE 0x%.2x \n",TempLogBuffer[idx]);
			}
		}
	}
}


void LoggerInit(){
	lwrb_init(&LogBuffer, LogBufferStorage, LOG_BUFFER_SIZE);
	xTaskCreate(TaskLogger, "Logger", 128, NULL, 2, &hTaskLogger);
	hLoggerMutex = xSemaphoreCreateMutexStatic( &LoggerMutexBuffer );
	hLoggerInbox = xQueueCreateStatic( INBOX_SIZE,
	                                 sizeof(LoggerMsg_t),
									 LoggerInboxStorage,
	                                 &LoggerInboxBuffer );
}
