
#include "main.h"

extern "C" {
    int main_cpp(void);
    void UART0IntHandler(void);
    void UART2IntHandler (void);
    void Timer0IntHandler(void);
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

void lunchHibernate (void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    HibernateRTCEnable();
    HibernateRTCTrimSet(0x7FFF);

    uint32_t actTime = HibernateRTCGet();
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

void UART2IntHandler (void)
{

}

uint32_t timeHz(uint16_t mS ) {
    uint32_t timeBegin = TimerValueGet(TIMER0_BASE, TIMER_A);
    SysCtlDelay(one_ms * mS);
    return (timeBegin - TimerValueGet(TIMER0_BASE, TIMER_A));
}

void UART0IntHandler (void)
{
    uint32_t timeBegin = TimerValueGet(TIMER0_BASE, TIMER_A);

    const int sizeRecMsg = 50;
    char recMsg[sizeRecMsg];
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    int i = 0;
    while(UARTCharsAvail(UART0_BASE) && i < sizeRecMsg) { //loop while there are chars
        recMsg[i] = UARTCharGetNonBlocking(UART0_BASE);
        ++i;
    }
    recMsg[i] = '\0';
    //SysCtlDelay(one_ms * 500);
    sendText("feedback: ");
    sendText(recMsg);
    //sendText("  - time of execution: ");
    //sendText(timeBegin - TimerValueGet(TIMER0_BASE, TIMER_A));
    //sendText(" - one second: ");
   // sendText(timeHz(500));
    sendText("\n");
}

void TimeIntInital() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

//    ui32Period = (SysCtlClockGet() / 10) / 2;
    uint32_t ui32Period = SysCtlClockGet();
    TimerLoadSet(TIMER0_BASE, TIMER_A, (3 * ui32Period) -1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();

    TimerEnable(TIMER0_BASE, TIMER_A);
}

void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    lunchHibernate();
}

int main_cpp(void) {
    ButtonsInit();
    while ( ButtonsPoll(0, 0) & 1 ) {
    }

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    TimeIntInital();

    UARTconfigure();

    //Init interupts for UART
    IntMasterEnable();
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntPrioritySet(INT_UART0, 0xE0);


    //Init LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
//    realTimeClock();

    while(1) {
    }
}

