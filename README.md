# STM32F4Cx Driver Library for UART, I2C, and SPI with Proteus Simulation
This folder contains a collection of drivers for UART (Universal Asynchronous Receiver-Transmitter), I2C (Inter-Integrated Circuit), and SPI (Serial Peripheral Interface) peripherals for the STM32F4Cx microcontroller series. These drivers are designed to facilitate communication protocols commonly used in embedded systems.

Contents
UART Driver: Provides functions and utilities for configuring and using UART communication.
I2C Driver: Offers functionalities for initializing and utilizing I2C communication protocol.
SPI Driver: Enables configuration and usage of SPI communication interface.
Each driver module is contained within its respective directory along with necessary header files and source code files.

Usage
UART Driver:

Include uart.h header file in your project.
Initialize UART by calling UART_Init() function with appropriate parameters.
Utilize provided functions such as UART_SendData() and UART_ReceiveData() for communication.
I2C Driver:

Include i2c.h header file in your project.
Initialize I2C by calling I2C_Init() function with required configurations.
Employ functions like I2C_Read() and I2C_Write() to perform read and write operations on the I2C bus.
SPI Driver:

Include spi.h header file in your project.
Initialize SPI by calling SPI_Init() function with appropriate settings.
Use functions like SPI_Transmit() and SPI_Receive() for data transfer over SPI bus.
Proteus Simulation
Included in this folder is a Proteus simulation setup that allows you to test and validate the functionality of the drivers in a simulated environment. The simulation setup includes the STM32F4Cx microcontroller along with virtual UART, I2C, and SPI modules.

To use the Proteus simulation:

Open the Proteus project file (.pdsprj) provided in this folder.
Simulate the project to observe the behavior of the drivers under different scenarios.
Compatibility
These drivers are specifically designed for the STM32F4Cx microcontroller series. However, with appropriate modifications, they can be adapted for use with other microcontroller platforms as well.

Contributors
Oussema Raissi
License
No license is provided.

Feedback and Contributions
We welcome feedback and contributions to enhance the functionality and reliability of these drivers. Feel free to submit issues or pull requests through our [repository link] on GitHub.
