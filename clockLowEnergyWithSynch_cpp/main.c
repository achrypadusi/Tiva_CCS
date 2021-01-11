#include "main.h"

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

int main(void) {
    main_cpp();
}


