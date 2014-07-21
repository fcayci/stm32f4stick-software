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
#include "usbcfg.h"

/* Virtual serial port over USB.*/
SerialUSBDriver SDU1;

void initBoardDefaults(void);
void initSerialOverUSB(void);

int main(void) {

    halInit();
    chSysInit();

    initBoardDefaults();
    initSerialOverUSB();

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

void initSerialOverUSB(void){

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1000);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}