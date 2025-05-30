#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "gpio.h"
#include "i2c.h"

#define MPU_ADDR 0x00           // I2C address of the MPU-6050
#define PWR_MGMT_1 0x6B         // Power management register
#define ACCEL_XOUT_H 0x3B       // Starting register for accelerometer data

uint16_t sData[2];              // Send data buffer
uint16_t rData[14];             // Receive data buffer for 14 registers
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;  // Sensor data variables
uint16_t i;
bool dataReady = false;

__interrupt void i2cFIFOISR(void);
__interrupt void INT_sw_XINT_ISR(void);
__interrupt void INT_myI2C0_ISR(void);

void MPU6050_Init(void);
void MPU6050_ReadData(void);
void ProcessSensorData(void);

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
    
    // Configure I2C as controller
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setSlaveAddress(myI2C0_BASE, MPU_ADDR);
    I2C_setDataCount(myI2C0_BASE, 1);
    I2C_enableInterrupt(myI2C0_BASE, I2C_INT_RXFF | I2C_INT_TXFF);
    
    EINT;
    ERTM;
    
    // Initialize MPU-6050
    MPU6050_Init();
    
    while(1)
    {
        // Read sensor data periodically
        MPU6050_ReadData();
        ProcessSensorData();
        
        // Add delay equivalent to Arduino's delay(100)
        DEVICE_DELAY_US(100000); // 100ms delay
    }
}

//
// Initialize MPU-6050 sensor
//
void MPU6050_Init(void)
{
    // Wake up the MPU-6050 by writing 0 to PWR_MGMT_1 register
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setSlaveAddress(myI2C0_BASE, MPU_ADDR);
    I2C_setDataCount(myI2C0_BASE, 2);
    
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_putData(myI2C0_BASE, PWR_MGMT_1);  // Register address
    I2C_putData(myI2C0_BASE, 0x00);        // Data to write (wake up)
    I2C_sendStopCondition(myI2C0_BASE);
    
    DEVICE_DELAY_US(1000); // Small delay after initialization
}

//
// Read sensor data from MPU-6050
//
void MPU6050_ReadData(void)
{
    uint16_t j;
    
    // First, send the starting register address
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setSlaveAddress(myI2C0_BASE, MPU_ADDR);
    I2C_setDataCount(myI2C0_BASE, 1);
    
    I2C_sendStartCondition(myI2C0_BASE);
    I2C_putData(myI2C0_BASE, ACCEL_XOUT_H);  // Starting register
    // Don't send stop condition here for repeated start
    
    // Now switch to receive mode and read 14 registers
    I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_RECEIVE_MODE);
    I2C_setDataCount(myI2C0_BASE, 14);
    
    I2C_sendStartCondition(myI2C0_BASE);
    
    // Read 14 bytes of data
    for(j = 0; j < 14; j++)
    {
        while(!I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_RXFF)
        {
            // Wait for data to be available
        }
        rData[j] = I2C_getData(myI2C0_BASE);
    }
    
    I2C_sendStopCondition(myI2C0_BASE);
    dataReady = true;
}

//
// Process the raw sensor data
//
void ProcessSensorData(void)
{
    if(dataReady)
    {
        // Combine high and low bytes for each sensor reading
        AcX = (rData[0] << 8) | rData[1];   // ACCEL_XOUT
        AcY = (rData[2] << 8) | rData[3];   // ACCEL_YOUT
        AcZ = (rData[4] << 8) | rData[5];   // ACCEL_ZOUT
        Tmp = (rData[6] << 8) | rData[7];   // TEMP_OUT
        GyX = (rData[8] << 8) | rData[9];   // GYRO_XOUT
        GyY = (rData[10] << 8) | rData[11]; // GYRO_YOUT
        GyZ = (rData[12] << 8) | rData[13]; // GYRO_ZOUT
        
        // Here you can add code to transmit or process the data
        // For example, send via UART or store in memory
        // Note: C2000 doesn't have Serial.print like Arduino
        
        dataReady = false;
    }
}

//
// Switch interrupt handler (if needed for manual trigger)
//
__interrupt void INT_sw_XINT_ISR(void)
{
    GPIO_writePin(led, 0);
    
    // Trigger a sensor reading
    MPU6050_ReadData();
    ProcessSensorData();
    
    GPIO_writePin(led, 1);
    
    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);
    I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
    Interrupt_clearACKGroup(INT_sw_XINT_INTERRUPT_ACK_GROUP);
}

//
// I2C Transmit & Receive FIFO ISR
//
__interrupt void i2cFIFOISR(void)
{
    if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_RXFF) != 0)
    {
        // Handle receive FIFO interrupt if needed
        I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_RXFF);
    }
    
    if((I2C_getInterruptStatus(myI2C0_BASE) & I2C_INT_TXFF) != 0)
    {
        // Handle transmit FIFO interrupt if needed
        I2C_clearInterruptStatus(myI2C0_BASE, I2C_INT_TXFF);
    }

    Interrupt_clearACKGroup(INT_myI2C0_FIFO_INTERRUPT_ACK_GROUP);
}

//
// General I2C ISR
//
__interrupt void INT_myI2C0_ISR(void)
{
    // Handle other I2C interrupts if needed
    Interrupt_clearACKGroup(INT_myI2C0_INTERRUPT_ACK_GROUP);
}


//