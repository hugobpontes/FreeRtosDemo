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
#include "event_groups.h"

#include "Common.h"

static TimerHandle_t hTmr1000;
static StaticTimer_t Tmr1000Buff;
static TimerHandle_t hTmr500;
static StaticTimer_t Tmr500Buff;
static TimerHandle_t hTmr250;
static StaticTimer_t Tmr250Buff;

SemaphoreHandle_t hBinSmph1000;
static StaticSemaphore_t BinSmph1000Buffer;

EventGroupHandle_t hEvGrp250_500;
static StaticEventGroup_t EvGrp250_500Buffer;

#define kTmr1000Ticks 1000
#define kTmr500Ticks 500
#define kTmr250Ticks 250

static void Tmr1000Callback( TimerHandle_t xTimer ){
	xSemaphoreGive(hBinSmph1000);
	TRICE( ID(3312), "SIGNAL: Tmr1000 Giving BinSmph1000 \n");
}

static void Tmr250Callback( TimerHandle_t xTimer ){
	xEventGroupSetBits(hEvGrp250_500,kTmr250EvMsk );
	TRICE( ID(4434), "SIGNAL: Setting Tmr250 Event flag \n");
}
static void Tmr500Callback( TimerHandle_t xTimer ){
	xEventGroupSetBits(hEvGrp250_500,kTmr500EvMsk );
	TRICE( ID(6178), "SIGNAL: Setting Tmr500 Event flag \n");
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

static inline void InitEvGroup(EventGroupHandle_t* phEvGrp,StaticEventGroup_t* pEvGrpBuffer){
	if ((*phEvGrp = xEventGroupCreateStatic(pEvGrpBuffer)) == pdFAIL ){
		TRICE( ID(6568), "Failed to create event group \n");
	}
}

void CommonInit(){
	InitAutoTimer(&hTmr1000,&Tmr1000Buff,kTmr1000Ticks+100,Tmr1000Callback,"Tmr1000");
	InitAutoTimer(&hTmr500,&Tmr500Buff,kTmr500Ticks,Tmr500Callback,"Tmr500");
	InitAutoTimer(&hTmr250,&Tmr250Buff,kTmr250Ticks,Tmr250Callback,"Tmr250");
	InitBinSemaphore(&hBinSmph1000,&BinSmph1000Buffer);
	InitEvGroup(&hEvGrp250_500,&EvGrp250_500Buffer);

}
