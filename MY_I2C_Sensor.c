
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


    // DEVICE_DELAY_US(2000);

    // I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    // I2C_sendStartCondition(myI2C0_BASE);
    // I2C_setSlaveAddress(myI2C0_BASE,0x68);
    // I2C_putData(myI2C0_BASE, 0x6B);
    // DEVICE_DELAY_US(200);
    // I2C_sendStopCondition(myI2C0_BASE);


    // I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    // I2C_sendStartCondition(myI2C0_BASE);
    // I2C_setSlaveAddress(myI2C0_BASE,0x68);
    // I2C_putData(myI2C0_BASE, 0x3B);
    // // DEVICE_DELAY_US(200);
    // I2C_sendStopCondition(myI2C0_BASE);


    // I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_RECEIVE_MODE);
    // I2C_sendStartCondition(myI2C0_BASE);
    // I2C_setSlaveAddress(myI2C0_BASE,0x68);
    // // DEVICE_DELAY_US(200);
    // I2C_setDataCount(myI2C0_BASE, 2);
    // for(i = 0; i < 5; i++)
    // {
    //     rData[i] = I2C_getData(myI2C0_BASE);
    //     // DEVICE_DELAY_US(200);
    // }
    // I2C_sendStopCondition(myI2C0_BASE);







    // Write register address
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_setSlaveAddress(myI2C0_BASE, 0x68);
    I2C_putData(myI2C0_BASE, 0x3B);

    // Do NOT send stop condition
    // Switch to read mode for repeated start
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_RECEIVE_MODE);

    // Issue repeated start
    I2C_sendStartCondition(myI2C0_BASE);  // This is the repeated start

    // Set how many bytes you expect to read (14 for all data)
    I2C_setDataCount(myI2C0_BASE, 14);

    // Read 14 bytes
    for (i = 0; i < 14; i++)
    {
        // while (!I2C_isDataReady(myI2C0_BASE));  // Wait for data
        rData[i] = I2C_getData(myI2C0_BASE);
    }

    // Finally send stop condition
    I2C_sendStopCondition(myI2C0_BASE);








    DEVICE_DELAY_US(500000);
    GPIO_writePin(led, 1);

    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);
    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
    Interrupt_clearACKGroup(INT_sw_XINT_INTERRUPT_ACK_GROUP);
}

//
