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

/*
 * SPI2 configuration structure.
 * Speed 21MHz, CPHA=0, CPOL=0, 8bits frames, MSb transmitted first.
 * The slave select line is the pin 12 on the port GPIOB.
 */
static const SPIConfig spi2cfg = {
  NULL,
  /* HW dependent part.*/
  GPIOB,
  12,
  0
};


void initBoardDefaults(void);
void initNRF24L01(void);

int main(void) {

    halInit();
    chSysInit();

    initBoardDefaults();
    initNRF24L01();

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

/*
 * Initializes the SPI driver 2 for nRF24L01+ module. The SPI2 signals are routed as follow:
 * PB12 - NSS
 * PB13 - SCK
 * PB14 - MISO
 * PB15 - MOSI
 * PC6  - RF_CE
 */
void initNRF24L01(void) {
    spiStart(&SPID2, &spi2cfg);
    palSetPad(GPIOB, 12);
    palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);  /* NSS  */
    palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) |  PAL_STM32_OSPEED_HIGHEST);    /* SCK  */
    palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5));                                /* MISO */
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);     /* MOSI */
    palSetPadMode(GPIOC, 5, PAL_MODE_OUTPUT_PUSHPULL);
}