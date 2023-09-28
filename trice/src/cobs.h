//! \file cobs.h
//! \author Thomas.Hoehenleitner [at] seerose.net


#ifndef COBS_H_
#define COBS_H_

#include <stddef.h> //lint !e537 !e451  Warning 537: Repeated include file,  Warning 451: Header file repeatedly included but does not have a standard
#include <stdint.h> //lint !e537 !e451  Warning 537: Repeated include file,  Warning 451: Header file repeatedly included but does not have a standard
#include "trice.h"

size_t COBSEncode(void * RESTRICT out, const void * RESTRICT in, size_t length);
size_t COBSDecode(void * RESTRICT out, const void * RESTRICT in, size_t length);

#endif
