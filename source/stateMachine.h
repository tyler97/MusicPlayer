#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum {
	PAUSE,
	NORMAL_PRESS,
	LONG_PRESS,
	PLAY,
	CHANGE_BIT,
	NORMAL_PRESS_PLAY,
	LONG_PRESS_PLAY,
	NORMAL_PRESS_NEXT,
	FORDWARE,
	CHANGE_SONG,
	NORMAL_PRESS_NEXT_PLAY_FW,
	CHANGE_BIT_FORDWARE,
	NORMAL_PRESS_PREV,
	CHANGE_SONG_PREV,
	NORMAL_PRESS_NEXT_PLAY_BW,
	BACKWARD,
	CHANGE_BIT_BACKWARD
} currentState;

typedef struct {
	currentState state;
	currentState nextState;
	uint32_t song;
	uint32_t bits;
	uint32_t counter;
	uint32_t play;
	uint32_t buttonInputs;
} stateMachine;

void musicPlayer(stateMachine *info) {
	switch (info->state) {
	case PAUSE:
		if (info->buttonInputs == 1) {
			info->counter = 0;
			info->nextState = NORMAL_PRESS;
		} else if (info->buttonInputs == 2) {
			info->counter = 0;
			info->nextState = NORMAL_PRESS_NEXT;
		} else if (info->buttonInputs == 3) {
			info->counter = 0;
			info->nextState = NORMAL_PRESS_PREV;
		}
		break;

	case NORMAL_PRESS:
		if (info->buttonInputs != 1 && info->counter >= 50) {
			info->counter = info->counter + 50;
			info->nextState = NORMAL_PRESS;
		} else if (info->buttonInputs == 1 && info->counter >= 1000) {
			info->nextState = LONG_PRESS;
		} else if (info->buttonInputs == 1) {
			info->counter = info->counter + 50;
			info->nextState = NORMAL_PRESS;
		} else if (info->buttonInputs != 1 && info->counter == 0) {
			info->nextState = PAUSE;
		} else if (info->buttonInputs != 1 && info->counter >= 50) {
			info->nextState = PLAY;
		}
		break;

	case LONG_PRESS:
		if (info->buttonInputs != 1) {
			info->song = 0;
			info->bits = 0;
			info->counter = 0;
			info->play = 0;
		} else {
			info->counter + 50;
		}
		break;

	case PLAY:
		if (info->counter >= 500) {
			info->nextState = CHANGE_BIT;
		} else if (info->buttonInputs == 1) {
			info->nextState = NORMAL_PRESS_PLAY;
		} else if (info->buttonInputs == 2) {
			info->nextState = NORMAL_PRESS_NEXT_PLAY_FW;
		} else if (info->buttonInputs == 3) {
			info->nextState = NORMAL_PRESS_NEXT_PLAY_BW;
		}
		info->counter = info->counter + 50;
		break;

	case CHANGE_BIT:
		info->counter = 0;
		info->bits = info->bits + 1;
		if (info->bits >= 3) {
			info->bits = 0;
		}
		if (info->buttonInputs == 1) {
			info->play = 0;
		}
		info->nextState = PLAY;
		break;

	case NORMAL_PRESS_PLAY:
		if (info->buttonInputs == 1 && info->play >= 1000) {
			info->nextState = LONG_PRESS_PLAY;
		} else if (info->buttonInputs == 1) {
			info->play = info->play + 50;
			info->counter = info->counter + 50;
			if (info->counter >= 500) {
				info->counter = 0;
				info->bits = info->bits + 1;
				if (info->bits >= 3) {
					info->bits = 0;
				}
			}
		} else if (info->buttonInputs != 1 && play == 0) {
			info->nextState = PLAY;
		} else if (info->buttonInputs != 1 && play >= 50) {
			info->counter = 0;
			info->play = 0;
			info->nextState = PAUSE;
		}
		break;

	case LONG_PRESS_PLAY:
		if (info->buttonInputs == 1) {
			info->counter = info->counter + 50;
			if (info->counter >= 500) {
				info->counter = 0;
				info->bits = info->bits + 1;
				if (info->bits >= 3) {
					info->bits = 0;
				}
			}
		} else if (info->buttonInputs != 1) {
			info->nextState = LONG_PRESS;
		}
		break;

	case NORMAL_PRESS_NEXT:
		if (info->buttonInputs != 2 && info->counter == 0) {
			info->nextState = PAUSE;
		} else if (info->buttonInputs != 2 && info->counter >= 1000) {
			info->nextState = PAUSE;
		} else if (info->buttonInputs != 2 && info->counter >= 50) {
			info->counter = 0;
			info->song = info->song + 1;
			if (info->song >= 4) {
				info->song = 0;
			}
			info->nextState = CHANGE_SONG;
		} else if (info->buttonInputs == 2) {
			info->counter = info->counter + 50;
		}
		break;

	case FORDWARE:
		if (info->buttonInputs == 2 && info->counter >= 100) {
			info->counter = 0;
			info->nextState = CHANGE_BIT_FORDWARE;
		} else if (info->buttonInputs != 2 && info->counter >= 50) {
			info->counter = 0;
			info->play = 0;
			info->song = info->song + 1;
			if (info->song >= 4) {
				info->song = 0;
			}
			info->nextState = PLAY;
		}
		info->counter = info->counter
		break;

	case CHANGE_SONG:
		info->counter = 0;
		info->nextState = PAUSE;
		break;

	case NORMAL_PRESS_NEXT_PLAY_FW:
		if (info->buttonInputs != 2 && info->play == 0) {
			info->counter = 0;
			info->nextState = PLAY;
		} else if (info->buttonInputs == 2 && info->play >= 1000) {
			info->nextState = FORDWARE;
		} else if (info->buttonInputs == 2) {
			info->counter = info->counter + 50;
		}
		break;

	case CHANGE_BIT_FORDWARE:
		info->counter = 0;
		info->bits = info->bits + 1;
		if (info->bits >= 3) {
			info->bits = 0;
		}
		info->nextState = CHANGE_BIT_FORDWARE;
		break;

	case NORMAL_PRESS_PREV:
		if (info->buttonInputs != 3 && info->counter >= 1000) {
			info->nextState = PAUSE;
		} else if (info->buttonInputs == 3) {
			info->counter = info->counter + 50;
		} else if (info->buttonInputs != 3 && info->counter >= 50) {
			info->counter = 0;
			info->song = info->song + 1;
			if (info->song < 0) {
				info->song = 3;
			}
			info->nextState = CHANGE_SONG_PREV;
		} else if (info->buttonInputs != 3 && info->counter == 0) {
			info->nextState = PAUSE;
		}
		break;

	case CHANGE_SONG_PREV:
		info->counter = 0;
		info->nextState = PAUSE;
		break;

	case NORMAL_PRESS_NEXT_PLAY_BW:
		if (info->buttonInputs == 3 && info->play >= 1000) {
			info->nextState = BACKWARD;
		} else if (info->buttonInputs != 3 && info->counter >= 50) {
			info->counter = 0;
			info->play = 0;
			info->song = info->song - 1;
			if (info->song < 0) {
				info->song = 3;
			}
			info->nextState = PLAY;
		} else if (info->buttonInputs == 3) {
			info->counter = info->counter + 50;
		} else if (info->buttonInputs != 3 && info->play == 0) {
			info->counter = 0;
			info->nextState = PLAY;
		}
		break;

	case BACKWARD:
		if (info->buttonInputs == 3 && info->counter >= 100) {
			info->counter = 0;
			info->nextState = CHANGE_BIT_BACKWARD;
		}
		info->counter = info->counter + 50;
		break;

	case CHANGE_BIT_BACKWARD:
		info->counter = 0;
		info->bits = info->bits - 1;
		if (info->bits < 0) {
			info->bits = 3;
		}
		info->nextState = BACKWARD;
		break;

	default:
		break;

		info->state = info->nextState;
	}
}

#endif /* STATEMACHINE_H_ */
