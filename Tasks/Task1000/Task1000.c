/*
 * Task1000.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "trice.h"
#include "lwrb/lwrb.h"

#include "Common.h"
#include "Logger.h"

#define TASK_1000_DATA_SIZE 4

static TaskHandle_t hTask1000;
static uint8_t Task1000Data[TASK_1000_DATA_SIZE] = {0xA1,0xA2,0xA3,0xA4};

#define WAIT_FOR_BIN_SMPH_1000_TICKS 1500
#define WAIT_FOR_LOGGER_MUTEX_1000_TICKS 100

static void Task1000(void* pvParams){
	while (1){
		TRICE( ID(6257), "INFO: Waiting for BinSmph1000 for %d \n",WAIT_FOR_BIN_SMPH_1000_TICKS);
        if( xSemaphoreTake( hBinSmph1000, ( TickType_t ) WAIT_FOR_BIN_SMPH_1000_TICKS ) == pdTRUE )
        {
        	TRICE( ID(7634), "INFO: Took BinSmph1000, waiting for logger mutex for %d \n",WAIT_FOR_LOGGER_MUTEX_1000_TICKS);
        	if( xSemaphoreTake( hLoggerMutex, WAIT_FOR_LOGGER_MUTEX_1000_TICKS ) == pdTRUE ){
            	TRICE( ID(4647), "INFO: Took logger mutex, writing A1A2A3A4 \n");
            	lwrb_write(&LogBuffer, Task1000Data, TASK_1000_DATA_SIZE);
            	TRICE( ID(7257), "INFO: Releasing logger mutex \n");
            	xSemaphoreGive(hLoggerMutex);
        	} else {
                TRICE( ID(7883), "ERROR: Could not take logger mutex in %d \n",WAIT_FOR_LOGGER_MUTEX_1000_TICKS);
        	}
        }
        else
        {
            TRICE( ID(1008), "ERROR: Could not take BinSmph1000 in %d \n",WAIT_FOR_BIN_SMPH_1000_TICKS);
        }
	}

}

void Task1000Init(){
	if(xTaskCreate(Task1000, "Task1000", 128, NULL, 4, &hTask1000) == pdFAIL){
		TRICE( ID(2790), "Failed to create task 1000 \n");
	}
}
