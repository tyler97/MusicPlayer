/*
 * MusicPlayer.h
 *
 *  Created on: 30 mar. 2020
 *      Author: ruizt
 */

#ifndef MUSICPLAYER_H_
#define MUSICPLAYER_H_

#include "debouncer.h"
#include "init.h"

typedef struct
{
	uint32_t pin;
	GPIO_Type * base;

}gpioPin;

typedef enum{

	pos1 = 0,
	pos2,
	pos3,
	pos4,
	pos5,
	pos6,
	pos7,
	pos8

}SONG_STATES;

typedef enum{

	track1 = 0,
	track2,
	track3,
	track4

}TRACK_STATES;

typedef enum{

	play,
	stopped


}PLAYER_STATES;

typedef struct {

	TRACK_STATES track;
	SONG_STATES songPos;
	PLAYER_STATES curState;
	debounceInfo* button;

}playerInfo;

void MusicPlayer(playerInfo* player);
void Song(playerInfo* player);
void Track(playerInfo*);
void TimerCheck(debounceInfo*, uint8_t);
void ButtonAction(debounceInfo* buttonArray, actions* buttonActions ,uint8_t size);
void WritePins(gpioPin* pins, uint8_t size, uint8_t data);


void MusicPlayer(playerInfo* player)
{


}

void Song(playerInfo* player)
{

}

void Track(playerInfo* player)
{

}

void WritePins(gpioPin* pins, uint8_t size, uint8_t data)
{
	uint8_t mask = 1U;
	uint8_t temp = 0U;

	for(uint8_t i = 0; i < size; i++)
	{

		temp = data & mask;
		temp = temp && temp;
		GPIO_WritePinOutput(pins[i].base, pins[i].pin, temp);
		mask <<= 1;

	}

}

void ButtonAction(debounceInfo* buttonArray, actions* buttonActions , uint8_t size)
{

	for(uint8_t i = 0; i < size; i++)
	{
		if(buttonArray[i].state == shortPress)
		{
			buttonArray[i].action = buttonActions[i].shortA;
		}
		else if(buttonArray[i].state == longPress)
		{
			buttonArray[i].action = buttonActions[i].longA;
		}
		else
		{
			buttonArray[i].action = none;
		}
	}

}

void TimerCheck(debounceInfo* buttonArray, uint8_t size)
{
	uint8_t flag = 1U;

	for(uint8_t i = 0; i < size; i++)
	{
		if(buttonArray[i].state == pressed)
		{
			flag = 0U;
		}
	}

	if(flag == 1U)
	{
		LPTMR_StopTimer(LPTMR0);
	}

}


#endif /* MUSICPLAYER_H_ */
