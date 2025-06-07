# MPU6500 STM32 Library

A lightweight, easy-to-use STM32 library for interfacing with the InvenSense TDK MPU6500 6-axis motion tracking device. This library provides functions to read accelerometer and gyroscope data, and handle interrupts—allowing you to build motion-sensing and stabilization applications on STM32 microcontrollers.

## Features

- Initialize and configure MPU6500 via I²C  
- Read 3-axis accelerometer and gyroscope data   
- Configure full-scale ranges (±2/4/8/16 g; ±250/500/1000/2000 °/s)
- Data-ready interrupt generation
- Compatible with STM32 HAL drivers  

## Prerequisites

- STM32 microcontroller  
- STM32Cube HAL drivers installed  
- I²C peripheral configured in your project  
- Power supply and wiring to MPU6500 per datasheet  

## Installation

1. Clone this repository into your project directory:  
   ```bash
   git clone https://github.com/<your-username>/mpu6500-stm32-library.git

2. Copy mpu6500.c and mpu6500.h into your source and include folders.

3. Configure your pin definitions in main.h.

## Configuration

The library is configured with the following default settings:
- Accelerometer: ±16g full-scale range
- Gyroscope: ±2000°/s full-scale range
- Sample Rate: 1kHz
- Bandwidth: 20Hz

## Usage

### Initialization

Before using the MPU6500, you need to:

1. Configure I²C in your STM32 project:
```c
// In your main.c or system initialization
I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_I2C1_Init(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_I2C1_Init();
    // ... rest of your initialization code
}
```

2. Initialize the MPU6500:
```c
HAL_StatusTypeDef status;

// Basic initialization
status = MPU6500_Init();
if(status != HAL_OK){
    Error_Handler();
}

// Optional: Read WHO_AM_I register to verify communication
uint8_t whoami;
status = MPU6500_ReadWhoAmI(&whoami);
if(status != HAL_OK || whoami != 0x70){
    Error_Handler();
}
```

3. Configure interrupts (optional):
```c
// Enable data ready interrupts
status = MPU6500_EnableDataReadyInterrupts();
if(status != HAL_OK){
    Error_Handler();
}

// Configure your GPIO interrupt handler
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == MPU6500_INT_Pin)
    {
        // Handle data ready interrupt
        // Read sensor data here
    }
}
```

### Reading Sensor Data

## Error Handling

All functions return `HAL_StatusTypeDef`:
- `HAL_OK`: Operation successful
- `HAL_ERROR`: Operation failed
- `HAL_BUSY`: Device is busy
- `HAL_TIMEOUT`: Operation timed out

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- InvenSense TDK for the MPU6500 sensor
- STMicroelectronics for the STM32 HAL drivers 

