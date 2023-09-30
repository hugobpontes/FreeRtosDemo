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


static inline void InitAutoTimer(TimerHandle_t* phTmr,StaticTimer_t* pTmrBuff, TickType_t TmrPeriod,TimerCallbackFunction_t TmrCallback, char* TmrName){
	if ((*phTmr = xTimerCreateStatic(TmrName,TmrPeriod,
							pdTRUE,(void *) 0,TmrCallback,
							pTmrBuff)) == pdFAIL){
			TRICE( ID(2352), "Failed to create timer \n");
		} else {
			if( xTimerStart( *phTmr, 0 ) == pdFAIL )
			{
				TRICE( ID(2431), "Failed to start timer \n");
			}
		}
}

static inline void InitBinSemaphore(SemaphoreHandle_t* phSmph,StaticSemaphore_t* pSmphBuffer){
	if ((*phSmph = xSemaphoreCreateBinaryStatic(pSmphBuffer)) == pdFAIL ){
		TRICE( ID(6996), "Failed to create binary semaphore \n");
	} else {
		xSemaphoreTake(*phSmph,0);
	}

}

void CommonInit(){
	InitAutoTimer(&hTmr1000,&Tmr1000Buff,kTmr1000Ticks,Tmr1000Callback,"Tmr1000");
	InitBinSemaphore(&hBinSmph1000,&BinSmph1000Buffer);

}
