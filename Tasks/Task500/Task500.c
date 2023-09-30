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

#include "Common.h"

#define WAIT_FOR_500_FLAG_TICKS 600

static TaskHandle_t hTask500;


void Task500(void* pvParams){
	EventBits_t SetFlags;
	while (1){
		TRICE( ID(4726), "INFO: Waiting for Tmr500 flag for %d \n",WAIT_FOR_500_FLAG_TICKS);
		SetFlags =  xEventGroupWaitBits(hEvGrp250_500,kTmr500EvMsk, pdTRUE,pdTRUE,WAIT_FOR_500_FLAG_TICKS );
		if (SetFlags & kTmr500EvMsk){
        	TRICE( ID(3296), "INFO: Received Tmr500 flag, doing stuff \n");
        	HAL_Delay(5);
		} else {
            TRICE( ID(2150), "ERROR: Did not receive tm500 flag in %d \n",WAIT_FOR_500_FLAG_TICKS);
		}
	}

}


void Task500Init(){
	xTaskCreate(Task500, "Task500", 128, NULL, 3, &hTask500);
}
