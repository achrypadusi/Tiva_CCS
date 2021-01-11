#include <stdint.h>
#include <stdbool.h>
#include "utils/ustdlib.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"
#include "driverlib/gpio.h"

#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "driverlib/rom_map.h"

#define one_ms 16000

void ConfigureUART(void);
void realTimeClock (void);

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    ButtonsInit();
    while ( ButtonsPoll(0, 0) & 1 ) {
    }

    unsigned char ch;
    ConfigureUART();
    //while (1) {
        //ch = UARTgetc();
        //SysCtlDelay(one_ms * 1000);
    //}

    realTimeClock();
}

void realTimeClock (void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    HibernateRTCEnable();
    uint32_t actTime = HibernateRTCGet();
    ConfigureUART();
    UARTprintf("TIME: %d\n", actTime);
    HibernateRTCMatchSet(0, actTime + 5);
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);
    SysCtlDelay(one_ms * 10);
    HibernateRequest();
}

void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}
