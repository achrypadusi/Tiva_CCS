
#include "main.h"

extern "C" {
    int main_cpp(void);
}

extern "C" {
    extern void ButtonsInit(void);
    extern uint8_t ButtonsPoll(uint8_t *pui8Delta, uint8_t *pui8Raw);
}



const int textSize = 100;
char textToSend[textSize];
char textReceived[textSize];

void sendText(char* text) {
    while(*text != '\0') {
        UARTCharPut(UART0_BASE, *text);
        ++text;
    }
}

void sendText(int value) {
    char text[20];
    ltoa(value, text, 10);
    int i=0;
    while(text[i] != '\0') {
        UARTCharPut(UART0_BASE, text[i]);
        ++i;
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

void realTimeClock (void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    HibernateRTCEnable();
    HibernateRTCTrimSet(0x7FFF);

    struct tm tmS = {0, 0, 0, 1, 0, 0, 0, 0, 0};
    uint32_t actTime = -1;

    while ( ButtonsPoll(0, 0) & 1 ) {
        if (UARTCharGetNonBlocking(UART0_BASE)!= -1) {
            sendText("Enter Time: ");
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
    sendText(textToSend);
    sendText("\t");
    sendText(actTime);
    sendText("\r");
    SysCtlDelay(one_ms * 10);

    HibernateRTCMatchSet(0, actTime + 5);
    HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    HibernateRequest();
}

void UARTconfigure() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


int main_cpp(void) {
    ButtonsInit();

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    UARTconfigure();

    //Init interupts for UART
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //Init LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    realTimeClock();
}


