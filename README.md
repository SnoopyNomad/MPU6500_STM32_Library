# MPU6500 STM32 Library

A lightweight, easy-to-use STM32 library for interfacing with the InvenSense TDK MPU6500 6-axis motion tracking device. This library provides functions to read accelerometer and gyroscope data, and generate interrupts—allowing you to build motion-sensing and stabilization applications on STM32 microcontrollers.

## Features

- Initialize and configure MPU6500 via I²C  
- Read 3-axis accelerometer and gyroscope data   
- Configure full-scale ranges (±2/4/8/16 g; ±250/500/1000/2000 °/s)
- Data-ready interrupt handling  
- Compatible with STM32 HAL drivers  

## Prerequisites

- STM32 microcontroller  
- STM32Cube HAL drivers installed  
- I²C peripheral configured in your project  
- Power supply and wiring to MPU6500 per datasheet  
