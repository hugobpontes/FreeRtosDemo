/*
 * Task1000.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"

#include "trice.h"
#include "timers.h"

#include "Common.h"

static TaskHandle_t hTask1000;

#define WAIT_FOR_BIN_SMPH_1000_TICKS 1500

static void Task1000(void* pvParams){
	while (1){
		TRICE( ID(6257), "INFO: Waiting for BinSmph1000 for %d \n",WAIT_FOR_BIN_SMPH_1000_TICKS);
        if( xSemaphoreTake( hBinSmph1000, ( TickType_t ) WAIT_FOR_BIN_SMPH_1000_TICKS ) == pdTRUE )
        {
        	TRICE( ID(1974), "INFO: Took BinSmph1000, doing stuff \n");
        	HAL_Delay(5);
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
