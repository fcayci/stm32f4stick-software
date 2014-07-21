/*
 * A Simple LED blinking example
 */

/*
 * STM32F4Stick board:
 * - LED1 is tied to PA0
 * - LED2 is tied to PA1
 */

#define LED_PORT GPIOA
#define LED1_PIN  GPIOA_PIN0
#define LED2_PIN  GPIOA_PIN1

#include "ch.h"
#include "hal.h"

int main(void) {

    halInit();
    chSysInit();

    palSetPadMode(LED_PORT, LED1_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(LED_PORT, LED2_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(LED_PORT, LED2_PIN);

    while (TRUE) {
        palTogglePad(LED_PORT, LED1_PIN);
        chThdSleepMilliseconds(500);
    }

    return 0;
}