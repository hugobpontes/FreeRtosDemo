/*
 * Common.c
 *
 *  Created on: Sep 30, 2023
 *      Author: hugo
 */

#include "FreeRTOS.h"
#include "task.h"
#include "trice.h"
#include "timers.h"
#include "semphr.h"

#include "Common.h"

static TimerHandle_t hTmr1000;
static StaticTimer_t Tmr1000Buff;
static TimerHandle_t hTmr500;
static StaticTimer_t Tmr500Buff;
static TimerHandle_t hTmr250;
static StaticTimer_t Tmr250Buff;

SemaphoreHandle_t hBinSmph1000;
static StaticSemaphore_t BinSmph1000Buffer;

#define kTmr1000Ticks 1000
#define kTmr500Ticks 500
#define kTmr250Ticks 250

static void Tmr1000Callback( TimerHandle_t xTimer ){
	xSemaphoreGive(hBinSmph1000);
	TRICE( ID(3312), "SIGNAL: Tmr1000 Giving BinSmph1000 \n");
}


void CommonInit(){
	if ((hTmr1000 = xTimerCreateStatic("tmr1000",kTmr1000Ticks,
						pdTRUE,(void *) 0,Tmr1000Callback,
						&Tmr1000Buff)) == pdFAIL){
		TRICE( ID(6056), "Failed to create timer 1000 \n");
	} else {
		if( xTimerStart( hTmr1000, 0 ) == pdFAIL )
		{
			TRICE( ID(1703), "Failed to start timer 1000 \n");
		}
	}

	if ((hBinSmph1000 = xSemaphoreCreateBinaryStatic(&BinSmph1000Buffer)) == pdFAIL ){
		TRICE( ID(4568), "Failed to create binary semaphore 1000");
	} else {
		xSemaphoreTake(hBinSmph1000,0);
	}

}
