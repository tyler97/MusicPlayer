/*
 * init.h
 *
 *  Created on: 20 mar. 2020
 *      Author: ruizt
 */

#ifndef INIT_H_
#define INIT_H_

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"


void InitBoard(void);

void InitBoard(void)
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
}

#endif /* INIT_H_ */
