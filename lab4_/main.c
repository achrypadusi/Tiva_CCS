#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

//uint8_t enableByButtons(void);
void editBritgtness(void);
const uint8_t maxBrightness = 9;
uint8_t brightness = 4;

int main(void)
{
    const uint8_t freq = 500;
    uint32_t ui32Period;

    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet() / freq) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    TimerEnable(TIMER0_BASE, TIMER_A);

    ButtonsInit();

    while (1)
    {
    }
}

void Timer0IntHandler(void)
{
    ///uint8_t enable = enableByButtons();
//    if (enable)
//    {
//        // Clear the timer interrupt
//        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//
//        // Read the current state of the GPIO pin and
//        // write back the opposite state
//        if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
//                         0);
//        }
//        else
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
//        }
//    }

        uint8_t onLed;
        static uint8_t brigthnessCnt = 0;

        editBritgtness();
        if (brigthnessCnt < brightness) {
            onLed = 1;
        } else {
            onLed = 0;
        }
        if (maxBrightness > brigthnessCnt)
            ++brigthnessCnt;
        else
            brigthnessCnt = 0;


        // Clear the timer interrupt
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        // Read the current state of the GPIO pin and
        // write back the opposite state
        if (onLed)
        {

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
        } else
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                         0);
        }
}

void editBritgtness(void)
{
    static uint8_t addB, prevAddB, subB, prevSubB;
    uint32_t ui32Buttons = ButtonsPoll(0, 0);

    if ((ui32Buttons & (1 << 4)) && prevAddB == 0) {
        addB = 1;
        prevAddB = 1;
    }
    else if ((ui32Buttons & (1 << 4)) && prevAddB == 1)
        addB = 0;
    else {
        addB = 0;
        prevAddB = 0;
    }

    if ((ui32Buttons & 1) && prevSubB == 0) {
        subB = 1;
        prevSubB = 1;
    }
    else if ((ui32Buttons & 1) && prevSubB == 1)
        subB = 0;
    else {
        subB = 0;
        prevSubB = 0;
    }

    if (addB && brightness < maxBrightness)
    {
        ++brightness;
    }
    else if (subB && brightness > 0)
    {
        --brightness;
    }
}
//}

//uint8_t enableByButtons(void)
//{
//    static uint8_t enableLED = 0;
//    uint32_t ui32Buttons = ButtonsPoll(0, 0);
//    if (ui32Buttons & (1 << 4))
//    {
//        enableLED = 1;
//    }
//    else if (ui32Buttons & 1)
//    {
//        enableLED = 0;
//    }
//    return enableLED;
//}
