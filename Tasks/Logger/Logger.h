/*
 * Logger.h
 *
 *  Created on: Oct 1, 2023
 *      Author: hugo
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

void LoggerInit();
extern lwrb_t LogBuffer;
extern SemaphoreHandle_t hLoggerMutex;

#endif /* LOGGER_LOGGER_H_ */
