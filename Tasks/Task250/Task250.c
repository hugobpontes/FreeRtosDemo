/*
 * Task250.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "trice.h"

#include "Common.h"

static TaskHandle_t hTask250;

#define WAIT_FOR_250_FLAG_TICKS 100

static void Task250(void* pvParams){
	EventBits_t SetFlags;
	while (1){
		TRICE( ID(3799), "INFO: Waiting for Tmr250 flag for %d \n",WAIT_FOR_250_FLAG_TICKS);
		SetFlags =  xEventGroupWaitBits(hEvGrp250_500,kTmr250EvMsk, pdTRUE,pdTRUE,WAIT_FOR_250_FLAG_TICKS );
		if (SetFlags & kTmr250EvMsk){
        	TRICE( ID(7231), "INFO: Received Tmr250 flag, doing stuff \n");
        	HAL_Delay(5);
		} else {
            TRICE( ID(5768), "ERROR: Did not receive tm250 flag in %d \n",WAIT_FOR_250_FLAG_TICKS);
		}
	}
}


void Task250Init(){
	xTaskCreate(Task250, "Task250", 128, NULL, 2, &hTask250);
}
