/*
 * STM32F4Stick board pinout:
 *
 * GPIO:
 * PA0  : LED1
 * PA1  : LED2
 * PB2  : BTN
 *
 * SD CARD (SPI1)
 * PA4  : SD_CS
 * PA5  : SD_SCK
 * PA6  : SD_MISO
 * PA7  : SD_MOSI
 *
 * USB
 * PA9  : USB_VBUS
 * PA11 : USB_DM
 * PA12 : USB_DP
 *
 * nRF24L01+ (SPI2)
 * PB12 : RF_CS
 * PB13 : RF_SCK
 * PB14 : RF_MISO
 * PB15 : RF_MOSI
 * PC6  : RF_CE
 */

/*
 * Board pin definitions
 */
#define LED_PORT  GPIOA
#define LED1_PIN  GPIOA_PIN0
#define LED2_PIN  GPIOA_PIN1

#define BTN_PORT  GPIOB
#define BTN_PIN   GPIOB_PIN2

#include "ch.h"
#include "hal.h"

static void pwmcb(PWMDriver *pwmp);

static PWMConfig pwmCFG = {
    100000,                             /* 100kHz PWM clock frequency  */
    1000,                               /* PWM period (in ticks) 1mS (1/100kHz=0.1uS, 0.1us*10000 ticks=1mS) */
    pwmcb,                              /* Callback */
    {
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 0 */
        {PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* Enable Channel 1 */
        {PWM_OUTPUT_DISABLED, NULL},
        {PWM_OUTPUT_DISABLED, NULL}
    },
    0,                                  /* HW dependent part */
    0
};

/*
 * PWM callback.
 * Each time calculate the next duty cycle.
 */
static void pwmcb(PWMDriver *pwmp) {
    (void)pwmp;

    static uint16_t dir = 0, width = 0;

    if (dir == 0) {width = (width + 10);}
    else {width = (width - 10);}

    if (width >= 1000) {dir = 1;}
    else if (width == 0) {dir = 0;}

    pwmEnableChannel(&PWMD5, 0, width);
    pwmEnableChannel(&PWMD5, 1, 1000-width);
}

void initBoardDefaults(void);

int main(void) {

    halInit();
    chSysInit();

    initBoardDefaults();

    /* Reconfigure LEDs as PWM pins using TIM5 module */
    palSetPadMode(LED_PORT, LED1_PIN, PAL_MODE_ALTERNATE(2));  /* TIM5 CH1 */
    palSetPadMode(LED_PORT, LED2_PIN, PAL_MODE_ALTERNATE(2));  /* TIM5 CH2 */

    pwmStart(&PWMD5, &pwmCFG);

    while (TRUE) {
        chThdSleepMilliseconds(500);
    }

    return 0;
}

void initBoardDefaults(void) {
    palSetPadMode(LED_PORT, LED1_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(LED_PORT, LED2_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(BTN_PORT, BTN_PIN, PAL_MODE_INPUT);
}
