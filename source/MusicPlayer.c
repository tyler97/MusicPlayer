/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MusicPlayer.c
 * @brief   Application entry point.
 */

/* TODO: insert other include files here. */

#include "MusicPlayer.h"

static uint8_t flagPIT0 = 0;

/*
 * @brief   Application entry point.
 */

/* Variables for TPM */
tpm_config_t tpmInfo;
tpm_chnl_pwm_signal_param_t tpmParam;

/* Variables for ADC16 */
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;

/* Variables for PIT */
pit_config_t My_PIT;
uint8_t flagPTI0 = 0;

gpioPin buttonPins[NUM_BUTTONS] = {
		{0, GPIOB},
		{1, GPIOB},
		{2, GPIOB}
};

gpioPin trackPins[2] = {
		{21, GPIOE},
		{20, GPIOE}
};

gpioPin songPins[3] = {
		{30, GPIOE},
		{29, GPIOE},
		{23, GPIOE}
};

actions buttonActions[NUM_BUTTONS] = {
		{playPause,stop},
		{next, forward},
		{prev, backward}
};

void InitAll(void);
void ChangeVolume(void);

int main(void) {

	debounceInfo buttonStates[NUM_BUTTONS];

	output pins[2] = {
			{trackPins, 2U},
			{songPins, 3U}
	};

	for(uint8_t i = 0; i < NUM_BUTTONS; i++)
	{
		InitDebounce(&buttonStates[i]);
	}

	inputButton buttons[NUM_BUTTONS];

	for(uint8_t i = 0; i < NUM_BUTTONS; i++)
	{
		buttons[i].button = buttonStates[i];
		buttons[i].action = buttonActions[i];
		buttons[i].pin = buttonPins[i];
	}

	playerInfo mPlayer;
	mPlayer.button = buttons;

	InitAll();
	InitPlayer(&mPlayer);


    while(1)
    {

    	//changing volume...
    	if(flagPIT0)
    	{
    		flagPIT0 = 0U;
    		ChangeVolume();

    	}

    	// reading input for each button...
    	for(uint8_t i = 0; i < NUM_BUTTONS; i++)
    	{

    		buttons[i].button.input = GPIO_ReadPinInput(buttons[i].pin.base, buttons[i].pin.pin);
    		debouncer(&buttons[i].button);

    	}

    	//getting actions for each button...
    	buttonAction(buttons, NUM_BUTTONS);

    	//calling state machine
		MusicPlayer(&mPlayer, pins);

		//cleaning timer if all buttons are off
    	TimerCheck(buttons, NUM_BUTTONS);

    }

    return 0;
}

void ChangeVolume(void)
{

	uint32_t adc = 0;

	ADC16_SetChannelConfig(ADC0, ADC_CHANNEL_GROUP, &adc16ChannelConfigStruct);

	while (0U == (kADC16_ChannelConversionDoneFlag &
				  ADC16_GetChannelStatusFlags(ADC0, ADC_CHANNEL_GROUP)))
	{
		//wait...
	}
	adc = ADC16_GetChannelConversionValue(ADC0, ADC_CHANNEL_GROUP);
	adc /= 409;

	TPM_UpdatePwmDutycycle(TPM0, kTPM_Chnl_1, kTPM_CenterAlignedPwm, adc * 10);

}

void InitAll(void)
{

	InitBoard();
	InitADC(&adc16ConfigStruct, &adc16ChannelConfigStruct);
	InitPIT(&My_PIT);
	InitTPM(&tpmInfo, &tpmParam);
	InitLPTMR();

}

//Interrupt Handler for PIT TIMER
void PIT_DriverIRQHandler(void){

	flagPIT0 = PIT_GetStatusFlags(PIT,kPIT_Chnl_0);

	if(flagPIT0)
	{
		PIT_ClearStatusFlags(PIT,kPIT_Chnl_0, kPIT_TimerFlag);
	}

}

