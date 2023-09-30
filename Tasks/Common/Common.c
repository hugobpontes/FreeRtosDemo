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

static TimerHandle_t hTmr1000;
static StaticTimer_t Tmr1000Buff;
static TimerHandle_t hTmr500;
static StaticTimer_t Tmr500Buff;
static TimerHandle_t hTmr250;
static StaticTimer_t Tmr250Buff;

#define kTmr1000Ticks 1000
#define kTmr500Ticks 500
#define kTmr250Ticks 250

static void Tmr1000Callback( TimerHandle_t xTimer ){
	TRICE( ID(3203), "Hello from software timer 1000 \n");
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


}
