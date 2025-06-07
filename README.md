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
