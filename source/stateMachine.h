#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

typedef enum
{
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
}currentState;

typedef struct
{
    currentState state;
    uint32_t song;
    uint32_t bits;
    uint32_t counter;
    uint32_t play;
    uint32_t buttonInputs;
}stateMachine;

void musicPlayer(stateMachine *info)
{
    switch(info->state)
    {
    case PAUSE:

        break;
    case NORMAL_PRESS:

        break;
    case LONG_PRESS:

        break;
    case PLAY:

        break;
    case CHANGE_BIT:

        break;
    case NORMAL_PRESS_PLAY:

        break;
    case LONG_PRESS_PLAY:

        break;
    case NORMAL_PRESS_NEXT:

        break;
    case FORDWARE:

        break;
    case CHANGE_SONG:

        break;
    case NORMAL_PRESS_NEXT_PLAY_FW:

        break;
    case CHANGE_BIT_FORDWARE:

        break;
    case NORMAL_PRESS_PREV:

        break;
    case CHANGE_SONG_PREV:

        break;
    case NORMAL_PRESS_NEXT_PLAY_BW:

        break;
    case BACKWARD:

        break;
    case CHANGE_BIT_BACKWARD:

        break;
    default:
        break;
    }
}

#endif /* STATEMACHINE_H_ */