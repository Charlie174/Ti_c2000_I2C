//
// Included Files
//
#include "driver_inclusive_terminology_mapping.h"
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "gpio.h"
#include "i2c.h"


//
// Globals
//
uint16_t sData[2];                  // Send data buffer
uint16_t rData[20] = {0};                  // Receive data buffer
char rmsg[10] = "I Love You";
uint16_t rDataPoint = 0;            // To keep track of where we are in the
                                    // data stream to check received data

// uint16_t i;

__interrupt void i2cFIFOISR(void);

//
// Main
//
void main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();

    Interrupt_initVectorTable();

    Board_init();

    // I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    // I2C_sendStartCondition(myI2C0_BASE);


    EINT;
    ERTM;

    while(1)
    {
     ;
    }

}

__interrupt void INT_sw_XINT_ISR(void)
{
    uint16_t i = 0;
    GPIO_writePin(led, 0);


    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_setSlaveAddress(myI2C0_BASE,0x08);
    I2C_setDataCount(myI2C0_BASE, 10);
    // I2C_putData(myI2C0_BASE, 'H');
    // I2C_putData(myI2C0_BASE, 'I');
    for(i = 0; i < 10; i++)
    {
        I2C_putData(myI2C0_BASE, rmsg[i]);
        DEVICE_DELAY_US(2000);

    }
    I2C_sendStopCondition(myI2C0_BASE);


    DEVICE_DELAY_US(2000);


    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_RECEIVE_MODE);
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_setSlaveAddress(myI2C0_BASE,0x08);
    I2C_setDataCount(myI2C0_BASE, 14);
    for(i = 0; i < 14; i++)
    {
        rData[i] = I2C_getData(myI2C0_BASE);
        DEVICE_DELAY_US(2000);
    }
    I2C_sendStopCondition(myI2C0_BASE);


    DEVICE_DELAY_US(500000);
    GPIO_writePin(led, 1);

    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);
    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
    Interrupt_clearACKGroup(INT_sw_XINT_INTERRUPT_ACK_GROUP);
}

// __interrupt void INT_myI2C0_FIFO_ISR(void){
//     uint16_t i;

//     if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_RXFF) != 0)
//     {
//         for(i = 0; i < 20; i++)
//         {
//             rData[i] = I2C_getData(myI2C0_BASE);
//         }

//         I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);

//     }


//     else if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_TXFF) != 0)
//     {
//         for(i = 0; i < 2; i++)
//         {
//             I2C_putData(myI2C0_BASE, sData[i]);
//         }

//         // I2C_sendStartCondition(myI2C0_BASE);

//         // I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
//     }

//     Interrupt_clearACKGroup(INT_myI2C0_FIFO_INTERRUPT_ACK_GROUP);
// }



// __interrupt void INT_myI2C0_ISR(void){

//     Interrupt_clearACKGroup(INT_myI2C0_INTERRUPT_ACK_GROUP);
// }



//
// I2C A Transmit & Receive FIFO ISR.
//
//  __interrupt void i2cFIFOISR(void){
//     uint16_t i;

//     //
//     // If receive FIFO interrupt flag is set, read data
//     //
//     if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_RXFF) != 0)
//     {
//         for(i = 0; i < 20; i++)
//         {
//             rData[i] = I2C_getData(myI2C0_BASE);
//         }

//         I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);

//     }


//     // else if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_TXFF) != 0)
//     // {
//     //     for(i = 0; i < 2; i++)
//     //     {
//     //         I2C_putData(myI2C0_BASE, sData[i]);
//     //     }

//     //     // I2C_sendStartCondition(myI2C0_BASE);

//     //     // //
//     //     // // Increment data for next cycle
//     //     // //
//     //     // for(i = 0; i < 2; i++)
//     //     // {
//     //     //    sData[i] = (sData[i] + 1) & 0xFF;
//     //     // }

