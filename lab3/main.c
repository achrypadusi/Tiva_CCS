#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


uint8_t ButtonsPoll(uint8_t *pui8Delta, uint8_t *pui8RawState);

const uint8_t LED_RED = 1<<1;
const uint8_t LED_BLUE = 1<<2;
const uint8_t LED_GREEN = 1<<3;

uint8_t ui8PinData = LED_RED;

int main(void)
{
    SysCtlClockSet(
            SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
                          GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    ButtonsInit();
    while (1)
    {
        uint32_t ui32Buttons = ButtonsPoll(0,0);
        //unit8_t rightButtonON = ui32Buttons & 16 ;
        //unit8_t lefttButtonOFF = ui32Buttons & 1 ;
        if (ui32Buttons & (1<<4)) {
            ui8PinData = LED_RED;
        } else if (ui32Buttons & 1) {
            ui8PinData = 0;
        }
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                            ui8PinData);

//        SysCtlDelay(2000000);
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
//                     0x00);
//        SysCtlDelay(5000000);
//        if ( ui8PinData == (LED_RED | LED_BLUE | LED_GREEN) )
//        {
//            ui8PinData = 0;
//        }
//        else
//        {
//            ui8PinData = ui8PinData + 2;
//        }
    }
}

//typedef struct
//{
//    uint32_t ui32Colors[3];
//    uint32_t ui32Mode;
//    uint32_t ui32Buttons;
//    uint32_t ui32ManualIndex;
//    uint32_t ui32ModeTimer;
//    float fColorWheelPos;
//    float fIntensity;
//
//}tAppState;

//void
//SysTickIntHandler(void)
//{
//
//    static float x;
//
//    g_sAppState.ui32Buttons = ButtonsPoll(0,0);
//    AppButtonHandler();
//
//    //
//    // Auto increment the color wheel if in the AUTO mode. AUTO mode is when
//    // device is active but user interaction has timed out.
//    //
//    if(g_sAppState.ui32Mode == APP_MODE_AUTO)
//    {
//        g_sAppState.fColorWheelPos += APP_AUTO_COLOR_STEP;
//    }
//
//    //
//    // Provide wrap around of the control variable from 0 to 1.5 times PI
//    //
//    if(g_sAppState.fColorWheelPos > (APP_PI * 1.5f))
//    {
//        g_sAppState.fColorWheelPos = 0.0f;
//    }
//    if(x < 0.0f)
//    {
//        g_sAppState.fColorWheelPos = APP_PI * 1.5f;
//    }
//
//    //
//    //    Set the RGB Color based on current control variable value.
//    //
//    AppRainbow(0);
//
//
//}
