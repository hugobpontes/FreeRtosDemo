/*
 * Task500.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "trice.h"
#include "lwrb/lwrb.h"

#include "Common.h"
#include "Logger.h"

#define WAIT_FOR_500_FLAG_TICKS 600
#define WAIT_FOR_LOGGER_MUTEX_500_TICKS 100
#define TASK_500_DATA_SIZE 5

static uint8_t Task500Data[TASK_500_DATA_SIZE] = {0xB1,0xB2,0xB3,0xB4,0xB5};

static TaskHandle_t hTask500;


void Task500(void* pvParams){

	EventBits_t SetFlags;
	LoggerMsg_t Task500Msg;
	Task500Msg.SenderId = 5;
	Task500Msg.Size = TASK_500_DATA_SIZE;

	while (1){
		TRICE( ID(4726), "INFO: Waiting for Tmr500 flag for %d \n",WAIT_FOR_500_FLAG_TICKS);
		SetFlags =  xEventGroupWaitBits(hEvGrp250_500,kTmr500EvMsk, pdTRUE,pdTRUE,WAIT_FOR_500_FLAG_TICKS );
		if (SetFlags & kTmr500EvMsk){
        	TRICE( ID(2839), "INFO: Received Tmr500 flag, waiting for logger mutex for %d \n",WAIT_FOR_LOGGER_MUTEX_500_TICKS);
        	if( xSemaphoreTake( hLoggerMutex, WAIT_FOR_LOGGER_MUTEX_500_TICKS ) == pdTRUE ){
        	            	TRICE( ID(2006), "INFO: Took logger mutex, writing B1B2B3B4B5 \n");
        	            	lwrb_write(&LogBuffer, Task500Data, TASK_500_DATA_SIZE);
        	            	HAL_Delay(150);
        	            	if (xQueueSend(hLoggerInbox,&Task500Msg,0) == pdFALSE){
        	            		 TRICE( ID(2785), "ERROR: Could not post msg to logger inbox \n");
        	            	}
        	            	TRICE( ID(6324), "INFO: Releasing logger mutex \n");
        	            	xSemaphoreGive(hLoggerMutex);
			} else {
				TRICE( ID(5850), "ERROR: Could not take logger mutex in %d \n",WAIT_FOR_LOGGER_MUTEX_500_TICKS);
			}
		} else {
            TRICE( ID(2150), "ERROR: Did not receive tm500 flag in %d \n",WAIT_FOR_500_FLAG_TICKS);
		}
	}

}


void Task500Init(){
	xTaskCreate(Task500, "Task500", 128, NULL, 4, &hTask500);
}
