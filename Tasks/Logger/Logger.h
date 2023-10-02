/*
 * Logger.h
 *
 *  Created on: Oct 1, 2023
 *      Author: hugo
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include "stdint.h"
#include "lwrb/lwrb.h"

typedef struct LoggerMsg {
	uint8_t SenderId;
	uint8_t Size;
} LoggerMsg_t;

void LoggerInit();
extern lwrb_t LogBuffer;
extern SemaphoreHandle_t hLoggerMutex;
extern QueueHandle_t hLoggerInbox;

#endif /* LOGGER_LOGGER_H_ */
