#ifndef TICKERISR_H
#define TICKERISR_H

#include <Arduino.h>
#include <Ticker.h>
#include "AcquisitionData.h"
#include "ALIVE_defs.h"

void init_tickers(void);
bool checkPID(void);

/* ISRs */
void ticker200mHzISR(void);
void ticker300mHzISR(void);
void ticker1HzISR(void);
void ticker2HzISR(void);
void ticker10HzISR(void);

#endif