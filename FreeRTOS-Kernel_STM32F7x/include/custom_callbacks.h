/*
 * custom_callbacks.h
 *
 *  Created on: Sep 27, 2023
 *      Author: hugo
 */

#ifndef CUSTOM_CALLBACKS_H_
#define CUSTOM_CALLBACKS_H_

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file. */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vAssertCalled( uint32_t ulLine, const char *pcFile );


#endif /* CUSTOM_CALLBACKS_H_ */
