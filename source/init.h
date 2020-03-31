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
#include "fsl_tpm.h"
#include "fsl_pit.h"
#include "fsl_adc16.h"
#include "fsl_lptmr.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define ADC_CHANNEL 15U
#define ADC_CHANNEL_GROUP 0U
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)
#define PIT_CLK_SRC_HZ_HP ((uint64_t)24000000)

void InitBoard(void);
void InitADC(adc16_config_t *, adc16_channel_config_t *);
void InitPIT(pit_config_t *);
void InitTPM(tpm_config_t *, tpm_chnl_pwm_signal_param_t *);

void InitBoard(void)
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
}

void InitPIT(pit_config_t * My_PIT)
{

    //Setting up Timer
    PIT_GetDefaultConfig(My_PIT);
    PIT_Init(PIT, My_PIT);

    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, MSEC_TO_COUNT(100,PIT_CLK_SRC_HZ_HP));
    PIT_EnableInterrupts(PIT,kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    PIT_StopTimer(PIT, kPIT_Chnl_0);

    //Setup timer for debounce...
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_1, MSEC_TO_COUNT(6000U,PIT_CLK_SRC_HZ_HP));
    PIT_DisableInterrupts(PIT, kPIT_Chnl_1, kPIT_TimerInterruptEnable);
    PIT_StopTimer(PIT, kPIT_Chnl_1);

    //Enabling Interrupts
    EnableIRQ(PIT_IRQn);
    PIT_StartTimer(PIT,kPIT_Chnl_0);
    PIT_StartTimer(PIT, kPIT_Chnl_1);

}

void InitADC(adc16_config_t * adc16ConfigStruct, adc16_channel_config_t * adc16ChannelConfigStruct)
{
	ADC16_GetDefaultConfig(adc16ConfigStruct);

	#ifdef BOARD_ADC_USE_ALT_VREF
	    adc16ConfigStruct->referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
	#endif
	    ADC16_Init(ADC0, adc16ConfigStruct);
	    ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */

	#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
	    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
	    {
	        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
	    }
	    else
	    {
	        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
	    }
	#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

	    adc16ChannelConfigStruct->channelNumber = ADC_CHANNEL;
	    adc16ChannelConfigStruct->enableInterruptOnConversionCompleted = false;
	#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	    adc16ChannelConfigStruct->enableDifferentialConversion = false;
	#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

}

void InitTPM(tpm_config_t * tpmInfo, tpm_chnl_pwm_signal_param_t * tpmParam)
{
    CLOCK_SetTpmClock(1U);

    TPM_GetDefaultConfig(tpmInfo);
    TPM_Init(TPM0, tpmInfo);

    tpmParam->chnlNumber = (tpm_chnl_t) kTPM_Chnl_1;
    tpmParam->dutyCyclePercent = 0U;
    tpmParam->level = kTPM_HighTrue;

    TPM_SetupPwm(TPM0, tpmParam, 1U, kTPM_CenterAlignedPwm, 24000U, TPM_SOURCE_CLOCK);
    TPM_StartTimer(TPM0, kTPM_SystemClock);

}

void InitLPTMR(void)
{
	lptmr_config_t lptmrConfig;

	LPTMR_GetDefaultConfig(&lptmrConfig);
    /* Initializes the LPTMR */

    LPTMR_Init(LPTMR0, &lptmrConfig);

	/* Sets the timer period */

    LPTMR_SetTimerPeriod(LPTMR0, MSEC_TO_COUNT(9000000U, LPO_CLK_FREQ));

}

#endif /* INIT_H_ */

