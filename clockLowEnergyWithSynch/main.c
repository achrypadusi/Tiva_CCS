#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#include "driverlib/hibernate.h"

#include "driverlib/uart.h"

#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#include <time.h>
#include <stdlib.h>

#define one_ms 16000

void UARTIntHandler(void);
void realTimeClock (void);


const int textSize = 100;
char textToSend[textSize];
char textReceived[textSize];
void putString(char* text);
void setTimeBase(char* timeString, struct tm* t);
void tmToString(struct tm* t, char* string);

int main(void) {
    ButtonsInit();
//    while ( ButtonsPoll(0, 0) & 1 ) {
//    }

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    //SysCtlDelay(one_ms * 50);
    realTimeClock();
}


void UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
    SysCtlDelay(one_ms * 500);
    {
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE));
    }
}

void realTimeClock (void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    HibernateRTCEnable();


    struct tm tmS = {0, 0, 0, 1, 0, 0, 0, 0, 0};
    uint32_t actTime = -1;

    while ( ButtonsPoll(0, 0) & 1 ) {
        if (UARTCharGetNonBlocking(UART0_BASE)!= -1) {
            putString("Enter Time: ");
            int i;
            for (i = 0; i < 9; ++i) {
                textReceived[i] = UARTCharGet(UART0_BASE);
                //SysCtlDelay(one_ms * 1);
            }
            textReceived[i] = '\0';
            setTimeBase(textReceived, &tmS);
            actTime = mktime(&tmS);
            HibernateRTCSet(actTime);
        }
    }
    if (actTime == -1) {
        actTime = HibernateRTCGet();
        tmS = *(localtime(&actTime));
    }

    tmToString(&tmS, textToSend);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
    putString(textToSend);
    putString("\t");
    ltoa(actTime, textToSend, 10);
    putString(textToSend);
    putString("\r");
//    while(1) {
//        SysCtlDelay(one_ms * 500);
//        putString(textToSend);
//        putString("\n");
//    }
    SysCtlDelay(one_ms * 10);

    HibernateRTCMatchSet(0, actTime + 5);
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    HibernateRequest();
}

void putString(char* text) {
    while(*text != '\0') {
        UARTCharPut(UART0_BASE, *text);
        ++text;
    }
}

void setTimeBase(char* timeString, struct tm* t) {
    char temp[2];
    temp[0] = timeString[0];
    temp[1] = timeString[1];
    t->tm_hour = atoi(temp);
    temp[0] = timeString[3];
    temp[1] = timeString[4];
    t->tm_min = atoi(temp);
    temp[0] = timeString[6];
    temp[1] = timeString[7];
    t->tm_sec = atoi(temp);
}

void tmToString(struct tm* t, char* string) {
    char temp[3];
    ltoa(t->tm_hour, temp, 10);
    if (temp[1]=='\0') {
        temp[1]=temp[0];
        temp[0]='0';
    }
    string[0]=temp[0];
    string[1]=temp[1];
    string[2]=':';
    ltoa(t->tm_min, temp, 10);
    if (temp[1]=='\0') {
        temp[1]=temp[0];
        temp[0]='0';
    }
    string[3]=temp[0];
    string[4]=temp[1];
    string[5]=':';
    ltoa(t->tm_sec, temp, 10);
    if (temp[1]=='\0') {
        temp[1]=temp[0];
        temp[0]='0';
    }
    string[6]=temp[0];
    string[7]=temp[1];
    string[8]='\0';
}
