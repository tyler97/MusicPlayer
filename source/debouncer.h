/*
 * debouncer.h
 *
 *  Created on: 20 mar. 2020
 *      Author: ruizt
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#include "fsl_lptmr.h"
#include "fsl_debug_console.h"

#define TIME_INIT 0
#define LOW 0
#define HIGH 1

typedef enum{

	notPressed = 0,
	pressed,
	shortPress,
	longPress,
	invalid

}DEBOUNCE_STATE;

typedef enum{

	playPause = 0,
	stop,
	next,
	forward,
	prev,
	backward,
	none


}BUTTON_ACTION;

typedef struct
{
	BUTTON_ACTION shortA;
	BUTTON_ACTION longA;

}actions;

typedef struct
{
    DEBOUNCE_STATE state;
    uint8_t input;
    uint32_t time;
    BUTTON_ACTION action;

}debounceInfo;


void InitDebounce(debounceInfo * info)
{
	info->state = notPressed;
	info->input = LOW;
	info->time = TIME_INIT;
}

void debouncer(debounceInfo * stateMachine)
{

	uint32_t totalTime;

	switch(stateMachine->state)
	{

	case notPressed:

		if(stateMachine->input == HIGH)
		{

			stateMachine->time  =  LPTMR_GetCurrentTimerCount(LPTMR0);

			if(stateMachine->time == 0U)
			{
				LPTMR_StartTimer(LPTMR0);
			}

			stateMachine->state = pressed;

		}
		else
		{

		}

		break;
	case pressed:

		totalTime = LPTMR_GetCurrentTimerCount(LPTMR0) - stateMachine->time;

		if(stateMachine->input == LOW && totalTime <= 49 && totalTime >= 35)
		{

			stateMachine->state = notPressed;

		}
		else if(stateMachine->input == LOW && totalTime >= 50U && totalTime < 1000U)
		{

			stateMachine->state = shortPress;

		}
		else if(stateMachine->input == HIGH && totalTime >= 1000U)
		{

			stateMachine->state = longPress;

		}

		else
		{

			stateMachine->state = pressed;

		}

		break;

	case shortPress:

		stateMachine->state = notPressed;
		stateMachine->time = TIME_INIT;

		break;

	case longPress:

		if(stateMachine->input == HIGH)
		{
			stateMachine->state = longPress;
		}
		else
		{
			stateMachine->state = notPressed;
			stateMachine->time = TIME_INIT;
		}

		break;

	default:

		stateMachine->state = notPressed;
		stateMachine->time = TIME_INIT;

		break;

	}

}

#endif /* DEBOUNCER_H_ */
