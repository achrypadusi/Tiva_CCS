
#include "main.h"

extern "C" {
    int main_cpp(void);
}

//*****************************************************************************
//
// Number of I2C data packets to send.
//
//*****************************************************************************
//#define NUM_I2C_DATA 3

//*****************************************************************************
//
// Set the address for slave module. This is a 7-bit address sent in the
// following format:
//                      [A6:A5:A4:A3:A2:A1:A0:RS]
//
// A zero in the "RS" position of the first byte means that the master
// transmits (sends) data to the selected slave, and a one in this position
// means that the master receives data from the slave.
//
//*****************************************************************************
#define SLAVE_ADDRESS 0x3C
//#define SLAVE_ADDRESS 0x77
#define NUM_I2C_DATA 3

int main_cpp(void) {

    uint32_t pui32DataTx[NUM_I2C_DATA];
    uint32_t pui32DataRx[NUM_I2C_DATA];
    uint32_t ui32Index;



    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_5);


//    HWREG(I2C0_BASE + I2C_O_MCR) |= 0x01;
//    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    // Enable loopback mode.  Loopback mode is a built in feature that is
    // useful for debugging I2C operations.  It internally connects the I2C
    // master and slave terminals, which effectively let's you send data as
    // a master and receive data as a slave.
    // NOTE: For external I2C operation you will need to use external pullups
    // that are stronger than the internal pullups.  Refer to the datasheet for
    // more information.

//    I2CLoopbackEnable(I2C0_BASE);
//    I2CLoopbackEnable(I2C2_BASE);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.  For this example we will use a data rate of 100kbps.

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
    //
    // Enable the I2C0 slave module. This module is enabled only for testing
    // purposes.  It does not need to be enabled for proper operation of the
    // I2Cx master module.
    //
    I2CSlaveEnable(I2C2_BASE);

    //
    // Set the slave address to SLAVE_ADDRESS.  In loopback mode, it's an
    // arbitrary 7-bit number (set in a macro above) that is sent to the
    // I2CMasterSlaveAddrSet function.
    //
    I2CSlaveInit(I2C2_BASE, SLAVE_ADDRESS);
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;

    // Tell the master module what address it will place on the bus when
    // communicating with the slave.  Set the address to SLAVE_ADDRESS
    // (as set in the slave module).  The receive parameter is set to false
    // which indicates the I2C Master is initiating a writes to the slave.  If
    // true, that would indicate that the I2C Master is initiating reads from
    // the slave.
    //
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, false);

    // Initalize the data to send.
    //
    pui32DataTx[0] = 'I';
    pui32DataTx[1] = '2';
    pui32DataTx[2] = 'C';

    //
    // Initalize the receive buffer.
    //
    for(ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        pui32DataRx[ui32Index] = 0;
    }


    for(ui32Index = 0; ui32Index < NUM_I2C_DATA; ui32Index++)
    {
        //
        // Place the data to be sent in the data register
        //
        I2CMasterDataPut(I2C0_BASE, pui32DataTx[ui32Index]);

        //
        // Initiate send of data from the master.  Since the loopback
        // mode is enabled, the master and slave units are connected
        // allowing us to receive the same data that we sent out.
        //
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        //
        // Wait until the slave has received and acknowledged the data.
        //
//        while(!(I2CSlaveStatus(I2C2_BASE) & I2C_SLAVE_ACT_RREQ))
//        {
//        }
        while(I2CMasterBusy(I2C0_BASE));
        while(I2CSlaveStatus(I2C2_BASE));
        //SysCtlDelay(one_ms * 5);
        //
        // Read the data from the slave.
        //
        pui32DataRx[ui32Index] = I2CSlaveDataGet(I2C2_BASE);

        //
        // Wait until master module is done transferring.
        //
        while(I2CMasterBusy(I2C0_BASE));
        while(I2CSlaveStatus(I2C2_BASE));
    }


    while(1) {
    }
}


