/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v7.0
processor: MKL25Z128xxx4
package_id: MKL25Z128VLK4
mcu_data: ksdk2_0
processor_version: 7.0.1
board: FRDM-KL25Z
pin_labels:
- {pin_num: '13', pin_signal: ADC0_DP0/ADC0_SE0/PTE20/TPM1_CH0/UART0_TX, label: 'J10[1]', identifier: TrackLED2}
- {pin_num: '14', pin_signal: ADC0_DM0/ADC0_SE4a/PTE21/TPM1_CH1/UART0_RX, label: 'J10[3]', identifier: TrackLED1}
- {pin_num: '15', pin_signal: ADC0_DP3/ADC0_SE3/PTE22/TPM2_CH0/UART2_TX, label: 'J10[5]', identifier: InputTest}
- {pin_num: '16', pin_signal: ADC0_DM3/ADC0_SE7a/PTE23/TPM2_CH1/UART2_RX, label: 'J10[7]', identifier: SongLED3}
- {pin_num: '21', pin_signal: CMP0_IN5/ADC0_SE4b/PTE29/TPM0_CH2/TPM_CLKIN0, label: 'J10[9]', identifier: SongLED2}
- {pin_num: '22', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1, label: 'J10[11]', identifier: SongLED1}
- {pin_num: '43', pin_signal: ADC0_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, label: 'J10[2]/A0', identifier: Prev}
- {pin_num: '44', pin_signal: ADC0_SE9/TSI0_CH6/PTB1/I2C0_SDA/TPM1_CH1, label: 'J10[4]/A1', identifier: FastFwd;Next}
- {pin_num: '45', pin_signal: ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/TPM2_CH0, label: 'J10[6]/A2', identifier: PlayButton;Play}
- {pin_num: '56', pin_signal: ADC0_SE15/TSI0_CH14/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0, label: 'J10[12]/U6[31]/A5', identifier: VolumeInput}
- {pin_num: '57', pin_signal: ADC0_SE11/TSI0_CH15/PTC2/I2C1_SDA/TPM0_CH1, label: 'J10[10]/A4', identifier: VolumeOutput}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '28', peripheral: UART0, signal: TX, pin_signal: TSI0_CH3/PTA2/UART0_TX/TPM2_CH1}
  - {pin_num: '27', peripheral: UART0, signal: RX, pin_signal: TSI0_CH2/PTA1/UART0_RX/TPM2_CH0}
  - {pin_num: '13', peripheral: GPIOE, signal: 'GPIO, 20', pin_signal: ADC0_DP0/ADC0_SE0/PTE20/TPM1_CH0/UART0_TX, direction: OUTPUT}
  - {pin_num: '14', peripheral: GPIOE, signal: 'GPIO, 21', pin_signal: ADC0_DM0/ADC0_SE4a/PTE21/TPM1_CH1/UART0_RX, direction: OUTPUT}
  - {pin_num: '21', peripheral: GPIOE, signal: 'GPIO, 29', pin_signal: CMP0_IN5/ADC0_SE4b/PTE29/TPM0_CH2/TPM_CLKIN0, direction: OUTPUT}
  - {pin_num: '43', peripheral: GPIOB, signal: 'GPIO, 0', pin_signal: ADC0_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, direction: INPUT}
  - {pin_num: '44', peripheral: GPIOB, signal: 'GPIO, 1', pin_signal: ADC0_SE9/TSI0_CH6/PTB1/I2C0_SDA/TPM1_CH1, identifier: Next, direction: INPUT}
  - {pin_num: '45', peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/TPM2_CH0, identifier: Play, direction: INPUT}
  - {pin_num: '22', peripheral: GPIOE, signal: 'GPIO, 30', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1, direction: OUTPUT, gpio_init_state: 'false'}
  - {pin_num: '16', peripheral: GPIOE, signal: 'GPIO, 23', pin_signal: ADC0_DM3/ADC0_SE7a/PTE23/TPM2_CH1/UART2_RX, direction: OUTPUT}
  - {pin_num: '56', peripheral: ADC0, signal: 'SE, 15', pin_signal: ADC0_SE15/TSI0_CH14/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0}
  - {pin_num: '57', peripheral: TPM0, signal: 'CH, 1', pin_signal: ADC0_SE11/TSI0_CH15/PTC2/I2C1_SDA/TPM0_CH1, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t Prev_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB0 (pin 43)  */
    GPIO_PinInit(BOARD_INITPINS_Prev_GPIO, BOARD_INITPINS_Prev_PIN, &Prev_config);

    gpio_pin_config_t Next_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB1 (pin 44)  */
    GPIO_PinInit(BOARD_INITPINS_Next_GPIO, BOARD_INITPINS_Next_PIN, &Next_config);

    gpio_pin_config_t Play_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB2 (pin 45)  */
    GPIO_PinInit(BOARD_INITPINS_Play_GPIO, BOARD_INITPINS_Play_PIN, &Play_config);

    gpio_pin_config_t TrackLED2_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE20 (pin 13)  */
    GPIO_PinInit(BOARD_INITPINS_TrackLED2_GPIO, BOARD_INITPINS_TrackLED2_PIN, &TrackLED2_config);

    gpio_pin_config_t TrackLED1_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE21 (pin 14)  */
    GPIO_PinInit(BOARD_INITPINS_TrackLED1_GPIO, BOARD_INITPINS_TrackLED1_PIN, &TrackLED1_config);

    gpio_pin_config_t SongLED3_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE23 (pin 16)  */
    GPIO_PinInit(BOARD_INITPINS_SongLED3_GPIO, BOARD_INITPINS_SongLED3_PIN, &SongLED3_config);

    gpio_pin_config_t SongLED2_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE29 (pin 21)  */
    GPIO_PinInit(BOARD_INITPINS_SongLED2_GPIO, BOARD_INITPINS_SongLED2_PIN, &SongLED2_config);

    gpio_pin_config_t SongLED1_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE30 (pin 22)  */
    GPIO_PinInit(BOARD_INITPINS_SongLED1_GPIO, BOARD_INITPINS_SongLED1_PIN, &SongLED1_config);

    /* PORTA1 (pin 27) is configured as UART0_RX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_RX_PORT, BOARD_INITPINS_DEBUG_UART_RX_PIN, kPORT_MuxAlt2);

    /* PORTA2 (pin 28) is configured as UART0_TX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_TX_PORT, BOARD_INITPINS_DEBUG_UART_TX_PIN, kPORT_MuxAlt2);

    /* PORTB0 (pin 43) is configured as PTB0 */
    PORT_SetPinMux(BOARD_INITPINS_Prev_PORT, BOARD_INITPINS_Prev_PIN, kPORT_MuxAsGpio);

    /* PORTB1 (pin 44) is configured as PTB1 */
    PORT_SetPinMux(BOARD_INITPINS_Next_PORT, BOARD_INITPINS_Next_PIN, kPORT_MuxAsGpio);

    /* PORTB2 (pin 45) is configured as PTB2 */
    PORT_SetPinMux(BOARD_INITPINS_Play_PORT, BOARD_INITPINS_Play_PIN, kPORT_MuxAsGpio);

    /* PORTC1 (pin 56) is configured as ADC0_SE15 */
    PORT_SetPinMux(BOARD_INITPINS_VolumeInput_PORT, BOARD_INITPINS_VolumeInput_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC2 (pin 57) is configured as TPM0_CH1 */
    PORT_SetPinMux(BOARD_INITPINS_VolumeOutput_PORT, BOARD_INITPINS_VolumeOutput_PIN, kPORT_MuxAlt4);

    /* PORTE20 (pin 13) is configured as PTE20 */
    PORT_SetPinMux(BOARD_INITPINS_TrackLED2_PORT, BOARD_INITPINS_TrackLED2_PIN, kPORT_MuxAsGpio);

    /* PORTE21 (pin 14) is configured as PTE21 */
    PORT_SetPinMux(BOARD_INITPINS_TrackLED1_PORT, BOARD_INITPINS_TrackLED1_PIN, kPORT_MuxAsGpio);

    /* PORTE23 (pin 16) is configured as PTE23 */
    PORT_SetPinMux(BOARD_INITPINS_SongLED3_PORT, BOARD_INITPINS_SongLED3_PIN, kPORT_MuxAsGpio);

    /* PORTE29 (pin 21) is configured as PTE29 */
    PORT_SetPinMux(BOARD_INITPINS_SongLED2_PORT, BOARD_INITPINS_SongLED2_PIN, kPORT_MuxAsGpio);

    /* PORTE30 (pin 22) is configured as PTE30 */
    PORT_SetPinMux(BOARD_INITPINS_SongLED1_PORT, BOARD_INITPINS_SongLED1_PIN, kPORT_MuxAsGpio);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK)))

                  /* UART0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)

                  /* UART0 receive data source select: UART0_RX pin. */
                  | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
