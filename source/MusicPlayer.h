/*
 * MusicPlayer.h
 *
 *  Created on: 30 mar. 2020
 *      Author: ruizt
 */
/*
*Ruiz Tyler Anthony
*Celis Regalado Paulo Enrique
*González Téllez José de Jesús
*
 */


#ifndef MUSICPLAYER_H_
#define MUSICPLAYER_H_

#include "debouncer.h"
#include "init.h"

#define PLAY 0
#define NEXT 1
#define PREV 2
#define NUM_BUTTONS 3
#define TRACKPIN 0
#define SONGPIN 1

typedef struct
{
	uint32_t pin;
	GPIO_Type * base;

}gpioPin;

typedef enum{

	pos1 = 0,
	pos2 = 1,
	pos3 = 2,
	pos4 = 4

}SONG_STATES;

typedef enum{

	track1 = 0,
	track2,
	track3,
	track4

}TRACK_STATES;

typedef enum{

	stopped,
	play,
	forwarding,
	backwards,
	pause,
	onRelease,
	onReleasePause

}PLAYER_STATES;

typedef struct {

	debounceInfo button;
	gpioPin pin;
    actions action;

}inputButton;

typedef struct {

	gpioPin* pins;
	uint8_t size;

}output;

typedef struct {

	TRACK_STATES track;
	SONG_STATES songPos;
	PLAYER_STATES curState;
	inputButton* button;

	uint64_t counter;
	uint64_t period;


}playerInfo;

void InitPlayer(playerInfo*);
void MusicPlayer(playerInfo* player, output*);
SONG_STATES Song(BUTTON_ACTION action,SONG_STATES songPos);
TRACK_STATES Track(BUTTON_ACTION action, TRACK_STATES track);
void TimerCheck(inputButton* buttonArray, uint8_t size);
void ButtonAction(debounceInfo* buttonArray, actions* buttonActions ,uint8_t size);
void WritePins(output* pins, uint8_t data);

void InitPlayer(playerInfo* player)
{
	player->counter = 0;
	player->curState = stopped;
	player->period = 0;
	player->songPos = pos1;
	player->track = track1;

}

void MusicPlayer(playerInfo* player, output* pins)
{

	switch(player->curState)
	{

	case stopped:

		if(player->button[PLAY].button.action == playPause)
		{
			player->curState = play;
			player->period = 500U;
			player->counter = 0;

			player->songPos = Song(playPause ,player->songPos);
			WritePins(&pins[SONGPIN] , (uint8_t) player->songPos);

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}

		break;

	case play:

		player->counter = 6000U - COUNT_TO_MSEC(PIT_GetCurrentTimerCount(PIT, kPIT_Chnl_1) , PIT_CLK_SRC_HZ_HP);

		if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[NEXT].button.action == forward)
		{
			player->curState = forwarding;

			player->counter = 0;
			player->period = 100U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->button[PREV].button.action == backward)
		{

			player->curState = backwards;

			player->counter = 0;
			player->period = 100U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->counter >= player->period)
		{
			player->songPos = Song(forward ,player->songPos);
			WritePins(&pins[SONGPIN] , (uint8_t) player->songPos);

			player->counter = 0U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->button[PLAY].button.action == playPause)
		{
			player->counter = 0;
			player->curState = pause;
			PIT_StopTimer(PIT, kPIT_Chnl_1);
		}
		else if(player->button[PLAY].button.action == stop)
		{
			player->curState = onRelease;

		}
		break;

	case onRelease:

		player->counter = 6000U - COUNT_TO_MSEC(PIT_GetCurrentTimerCount(PIT, kPIT_Chnl_1) , PIT_CLK_SRC_HZ_HP);

		if(player->button[PLAY].button.action != stop)
		{

			player->curState = stopped;

			player->track = Track(stop, player->track);
			player->songPos = Song(stop, player->songPos);

			player->counter = 0U;
			player->period = 0U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);

			WritePins(&pins[TRACKPIN], player->track);
			WritePins(&pins[SONGPIN], player->songPos);

		}
		else if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[NEXT].button.action == forward)
		{
			player->curState = forwarding;

			player->counter = 0;
			player->period = 100U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->button[PREV].button.action == backward)
		{

			player->curState = backwards;

			player->counter = 0;
			player->period = 100U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->counter >= player->period)
		{
			player->songPos = Song(forward ,player->songPos);
			WritePins(&pins[SONGPIN] , (uint8_t) player->songPos);

			player->counter = 0U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->button[PLAY].button.action == playPause)
		{
			player->counter = 0;
			player->curState = pause;
			PIT_StopTimer(PIT, kPIT_Chnl_1);
		}
		break;

	case forwarding:

		player->counter = 6000U - COUNT_TO_MSEC(PIT_GetCurrentTimerCount(PIT, kPIT_Chnl_1), PIT_CLK_SRC_HZ_HP);

		if(player->button[NEXT].button.action != forward)
		{
			player->curState = play;

			player->counter = 0;
			player->period = 500U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->counter >= player->period)
		{
			player->songPos = Song(forward ,player->songPos);
			WritePins(&pins[SONGPIN] , (uint8_t) player->songPos);

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}

		break;
	case backwards:

		player->counter = 6000U - COUNT_TO_MSEC(PIT_GetCurrentTimerCount(PIT, kPIT_Chnl_1), PIT_CLK_SRC_HZ_HP);

		if(player->button[PREV].button.action != backward)
		{
			player->curState = play;

			player->counter = 0;
			player->period = 500U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->counter >= player->period)
		{

			player->songPos = Song(backward ,player->songPos);
			WritePins(&pins[SONGPIN] , (uint8_t) player->songPos);

			PIT_StopTimer(PIT, kPIT_Chnl_1);
			PIT_StartTimer(PIT, kPIT_Chnl_1);

		}
		else if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}

		break;

	case pause:

		if(player->button[PLAY].button.action == playPause)
		{
			player->curState = play;
			player->counter = 0U;
			player->period = 500U;

			PIT_StartTimer(PIT, kPIT_Chnl_1);
		}
		else if(player->button[PLAY].button.action == stop)
		{
			player->curState = onReleasePause;

		}
		else if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}

		break;
	case onReleasePause:

		if(player->button[PLAY].button.action != stop)
		{
			player->curState = stopped;

			player->track = Track(stop, player->track);
			player->songPos = Song(stop, player->songPos);

			player->counter = 0U;
			player->period = 0U;

			PIT_StopTimer(PIT, kPIT_Chnl_1);

			WritePins(&pins[TRACKPIN], player->track);
			WritePins(&pins[SONGPIN], player->songPos);

		}

		else if(player->button[NEXT].button.action == next)
		{
			player->track = Track(next, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}
		else if(player->button[PREV].button.action == prev)
		{
			player->track = Track(prev, player->track);
			WritePins(&pins[TRACKPIN], player->track);
		}

		break;

	}

}

SONG_STATES Song(BUTTON_ACTION action, SONG_STATES songPos)
{

	switch(songPos)
	{

	case pos1:

		if(action == playPause)
		{
			songPos = pos2;
		}

		break;
	case pos2:

		if(action == backward)
		{
			songPos = pos4;
		}
		else if(action == stop)
		{
			songPos = pos1;
		}
		else
		{
			songPos = pos3;
		}


		break;
	case pos3:

		if(action == backward)
		{
			songPos = pos2;
		}
		else if(action == stop)
		{
			songPos = pos1;
		}
		else
		{
			songPos = pos4;
		}


		break;
	case pos4:

		if(action == backward)
		{
			songPos = pos3;
		}
		else if(action == stop)
		{
			songPos = pos1;
		}
		else
		{
			songPos = pos2;
		}


		break;
	}

	return songPos;
}

TRACK_STATES Track(BUTTON_ACTION action, TRACK_STATES track)
{

	switch(track)
	{
	case track1:

		if(action == prev)
		{
			track = track4;
		}
		else if(action == next)
		{
			track = track2;
		}
		else if(action == stop)
		{
			track = track1;
		}
		else
		{
			track = track1;
		}

		break;
	case track2:

		if(action == prev)
		{
			track = track1;
		}
		else if(action == next)
		{
			track = track3;
		}
		else if(action == stop)
		{
			track = track1;
		}
		else
		{
			track = track2;
		}

		break;
	case track3:

		if(action == prev)
		{
			track = track2;
		}
		else if(action == next)
		{
			track = track4;
		}
		else if(action == stop)
		{
			track = track1;
		}
		else
		{
			track = track3;
		}

		break;
	case track4:

		if(action == prev)
		{
			track = track3;
		}
		else if(action == next)
		{
			track = track1;
		}
		else if(action == stop)
		{
			track = track1;
		}
		else
		{
			track = track4;
		}

		break;
	}
	return track;
}

void WritePins(output* pins, uint8_t data)
{

	uint8_t mask = 1U;
	uint8_t temp = 0U;

	for(uint8_t i = 0; i < pins->size; i++)
	{

		temp = data & mask;
		temp = temp && temp;
		GPIO_WritePinOutput(pins->pins[i].base, pins->pins[i].pin, temp);
		mask <<= 1;

	}

}

void TimerCheck(inputButton* buttonArray, uint8_t size)
{
	uint8_t flag = 1U;

	for(uint8_t i = 0; i < size; i++)
	{
		if(buttonArray[i].button.state == pressed)
		{
			flag = 0U;
		}
	}

	if(flag == 1U)
	{
		LPTMR_StopTimer(LPTMR0);
	}

}

void buttonAction(inputButton* buttonArray, uint8_t size)
{
	for(uint8_t i = 0; i < size; i++)
	{
		if(buttonArray[i].button.state == shortPress)
		{
			buttonArray[i].button.action = buttonArray[i].action.shortA;
		}
		else if(buttonArray[i].button.state == longPress)
		{
			buttonArray[i].button.action = buttonArray[i].action.longA;
		}
		else
		{
			buttonArray[i].button.action = none;
		}
	}
}

#endif /* MUSICPLAYER_H_ */
