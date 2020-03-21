/*
 * debouncer.h
 *
 *  Created on: 20 mar. 2020
 *      Author: ruizt
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#define DISABLE 0
#define ENABLE 1
#define HIGH 1
#define LOW 0

typedef enum
{
    DISABLES,
    COUNT_ENABLE,
    ENABLES,
    COUNT_DIS,
    NUM_OF_STATES

}DEBOUNCE_STATE;

typedef struct
{
    DEBOUNCE_STATE state;
    uint32_t input;
    uint32_t output;
    uint32_t counter;

}machineInfo;

//prototypes
void Init(machineInfo * info);
void disableToCountEnable(machineInfo * info);
void countEnableToDisable(machineInfo * info);
void countEnableToCountEnable(machineInfo * info);
void countEnableToEnable(machineInfo * info);
void enableToCountDisable(machineInfo * info);
void countDisableToCountDisable(machineInfo * info);
void countDisableToEnable(machineInfo * info);
void countDisableToDisable(machineInfo * info);

//event functions
void disableToCountEnable(machineInfo * info)
{
    info->counter = 0;
    info->output = DISABLE;
    info->state = COUNT_ENABLE;
}

void countEnableToDisable(machineInfo * info)
{
    info->counter = 0;
    info->output = DISABLE;
    info->state = DISABLES;

}

void countEnableToCountEnable(machineInfo * info)
{
    info->counter = info->counter + 1;
    info->output = DISABLE;
    info->state = COUNT_ENABLE;

}

void countEnableToEnable(machineInfo * info)
{
    info->output = ENABLE;
    info->state = ENABLES;

}

void enableToCountDisable(machineInfo * info)
{
    info->counter = 0;
    info->output = ENABLE;
    info->state = COUNT_DIS;
}

void countDisableToCountDisable(machineInfo * info)
{
    info->counter = info->counter + 1;
    info->output = ENABLE;
    info->state = COUNT_DIS;

}

void countDisableToEnable(machineInfo * info)
{
    info->counter = 0;
    info->output = ENABLE;
    info->state = ENABLES;

}

void countDisableToDisable(machineInfo * info)
{
    info->output = DISABLE;
    info->state = DISABLES;
}

void Init(machineInfo * info)
{
    info->counter = 0;
    info->input = LOW;
    info->output = DISABLE;
    info->state = DISABLES;
}

//state machine
void debouncer(machineInfo * info)
{

    switch(info->state)
    {
    case DISABLES:

        if(info->input == HIGH)
        {
            disableToCountEnable(info);
        }

        break;
    case COUNT_ENABLE:

        if((info->input == HIGH) && (info->counter >= 4))
        {
            countEnableToEnable(info);
        }
        else if(info->input == HIGH)
        {
            countEnableToCountEnable(info);
        }
        else if(info->input == LOW)
        {
            countEnableToDisable(info);
        }

        break;
    case ENABLES:

        if(info->input == LOW)
        {
            enableToCountDisable(info);
        }

        break;
    case COUNT_DIS:

        if(info->input == HIGH)
        {
            countDisableToEnable(info);
        }
        else if((info->input == LOW) && (info->counter >= 3))
        {
            countDisableToDisable(info);
        }
        else if(info->input == LOW)
        {
            countDisableToCountDisable(info);
        }

        break;

    default:
        break;
    }
}

#endif /* DEBOUNCER_H_ */
