# MPU6500 STM32 Library

A lightweight, easy-to-use STM32 library for interfacing with the InvenSense TDK MPU6500 6-axis motion tracking device. This library provides functions to read accelerometer and gyroscope data, and handle interrupts—allowing you to build motion-sensing and stabilization applications on STM32 microcontrollers.

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
  - [Initialization](#initialization)
  - [Reading Sensor Data](#reading-sensor-data)
  - [Data Formats](#data-formats)
  - [Interrupt Handling](#interrupt-handling)
- [Error Handling](#error-handling)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

- Initialize and configure MPU6500 via I²C  
- Read 3-axis accelerometer and gyroscope data   
- Configure full-scale ranges:
  - Accelerometer: ±2/4/8/16 g
  - Gyroscope: ±250/500/1000/2000 °/s
- Data-ready interrupt generation
- Temperature sensor reading
- Compatible with STM32 HAL drivers
- Low power consumption modes
- Built-in self-test functionality

## Prerequisites

- STM32 microcontroller (F0, F1, F3, F4, F7, L0, L1, L4 series supported)
- STM32Cube HAL drivers installed
- I²C peripheral configured in your project
- Power supply and wiring to MPU6500 per datasheet
- Basic understanding of STM32 development

## Installation

1. Clone this repository into your project directory:  
   ```bash
   git clone https://github.com/<your-username>/mpu6500-stm32-library.git
   ```

2. Copy the following files into your project:
   - `mpu6500.c` → Your project's source folder
   - `mpu6500.h` → Your project's include folder

3. Configure your pin definitions in `main.h`:
   ```c
   #define MPU6500_INT_Pin        GPIO_PIN_0
   #define MPU6500_INT_GPIO_Port  GPIOA
   ```

## Configuration

The library is configured with the following default settings:
- Accelerometer: ±16g full-scale range
- Gyroscope: ±2000°/s full-scale range
- Sample Rate: 1kHz
- Bandwidth: 20Hz
- Clock Source: Internal oscillator
- Sleep Mode: Disabled
- Interrupts: Disabled

## Usage

### Initialization

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
2. **Include the Library**: Add the library header to your project.
   ```c
   #include "mpu6500.h"
   ```

3. Initialize the MPU6500:
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

### Reading Sensor Data

```c
int16_t accel_x, accel_y, accel_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;
float accel_g[3];    // Acceleration in g
float gyro_dps[3];   // Angular velocity in degrees per second
float temp_c;        // Temperature in Celsius

// Read raw sensor data
status = MPU6500_ReadAccel(&accel_x, &accel_y, &accel_z);
if(status != HAL_OK){
    Error_Handler();
}

status = MPU6500_ReadGyro(&gyro_x, &gyro_y, &gyro_z);
if(status != HAL_OK){
    Error_Handler();
}

status = MPU6500_ReadTemp(&temperature);
if(status != HAL_OK){
    Error_Handler();
}

// Convert raw data to physical units
// For ±16g range: 1g = 2048 LSB
accel_g[0] = (float)accel_x / 2048.0f;
accel_g[1] = (float)accel_y / 2048.0f;
accel_g[2] = (float)accel_z / 2048.0f;

// For ±2000°/s range: 1°/s = 16.4 LSB
gyro_dps[0] = (float)gyro_x / 16.4f;
gyro_dps[1] = (float)gyro_y / 16.4f;
gyro_dps[2] = (float)gyro_z / 16.4f;

// Temperature conversion: T(°C) = (TEMP_OUT / 340) + 36.53
temp_c = ((float)temperature / 340.0f) + 36.53f;
```

### Data Formats

1. **Accelerometer Data**
   - Raw data range: -32768 to +32767
   - Scale factors for different ranges:
     - ±2g: 16384 LSB/g
     - ±4g: 8192 LSB/g
     - ±8g: 4096 LSB/g
     - ±16g: 2048 LSB/g

2. **Gyroscope Data**
   - Raw data range: -32768 to +32767
   - Scale factors for different ranges:
     - ±250°/s: 131 LSB/°/s
     - ±500°/s: 65.5 LSB/°/s
     - ±1000°/s: 32.8 LSB/°/s
     - ±2000°/s: 16.4 LSB/°/s

3. **Temperature Data**
   - Raw data range: -32768 to +32767
   - Conversion formula: T(°C) = (TEMP_OUT / 340) + 36.53

### Interrupt Handling

1. Configure interrupts:
```c
// Enable data ready interrupts
status = MPU6500_EnableDataReadyInterrupts();
if(status != HAL_OK){
    Error_Handler();
}
```

2. Set up interrupt handler:
```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == MPU6500_INT_Pin)
    {
        int16_t accel_x, accel_y, accel_z;
        int16_t gyro_x, gyro_y, gyro_z;
        
        // Read sensor data
        MPU6500_ReadAccel(&accel_x, &accel_y, &accel_z);
        MPU6500_ReadGyro(&gyro_x, &gyro_y, &gyro_z);
        
        // Process data here
        // ...
    }
}
```

## Error Handling

All functions return `HAL_StatusTypeDef`:
- `HAL_OK`: Operation successful
- `HAL_ERROR`: Operation failed
- `HAL_BUSY`: Device is busy
- `HAL_TIMEOUT`: Operation timed out

Common issues:
- I²C communication failure
- Invalid device address
- Sensor unresponsive
- Misconfiguration

## Contributing

Contributions are welcome! Please follow these steps:
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

MIT – see [LICENSE](LICENSE).

## Acknowledgments

- InvenSense TDK (MPU6500)
- STMicroelectronics (HAL drivers)
- Community contributors

