STM32 W25Q128 External Flash Memory Driver & Storage Manager
This project is a robust, C++ based driver and interface solution for STM32 microcontrollers, specifically developed for the reliable management and data logging of the W25Q128 (16 MB / 128 Mbit) external SPI Flash memory chip.

🏗️ System Architecture
The software employs an object-oriented C++ approach to ensure a modular structure and clean boundary conditions for SPI communication:

Low-Level SPI Abstraction: Secure and efficient data transfer via the Hardware SPI peripheral, featuring optimized Chip Select (CS) management.

Flash Command Management: Full implementation of a low-level command set (Write Enable, Chip Erase, Sector Erase, Page Program, Read Data).

C++ Class Architecture: Encapsulated driver structure that facilitates seamless integration of the memory into any external FreeRTOS or bare-metal project.

Block-Based Read/Write: Sector and page-based management respecting the data integrity and physical constraints of flash memory (erase cycles).

🛠️ Technical Implementation
Development Environment (IDE): STM32CubeIDE (C++).

Hardware Components: STM32 microcontroller, W25Q128 SPI Flash memory (128 Mbit / 16 MB).

Communication: SPI bus protocol (Master mode, with GPIO-based or hardware NSS management).

Memory Specification:

256-byte page size

4 KB Sector Erase

Block and full-chip erase commands (Bulk Erase)

💡 Key Challenges & Solutions
Timing and Protocol Integrity: Strict adherence to the W25Q128 register and command sequence (e.g., mandatory issuance of the Write Enable command prior to any write/erase operation) to guarantee error-free communication.

Status Register Polling (Busy Flag Monitoring): Built-in waiting mechanism for internal write/erase execution times (checking the WEL and WIP – Write In Progress bits) to prevent command collisions.

Memory Addressing: Correct bitwise handling of the 24-bit addressing structure for precise positioning across the large-capacity (16 MB) storage space.

📂 Project Structure
Plaintext
/Core/Src       - Main application logic, testing routines
/Core/Inc       - W25Q128 C++ driver class definitions and constants
/Drivers        - STM32 HAL SPI peripheral drivers
/Debug          - Compilation and binary outputs
📄 Documentation
* **Schematic (PDF):** System hardware schematic showing the Nucleo F446RE and W25Q128 module connections, pinout, and NC flags, available in `Dokumentation/Schematic_V0.1.pdf`.
* **Datasheet:** Official Winbond W25Q128JV hardware datasheet.
* **Visual Reference:** Hardware layout photos and visual wiring aids.

📚 References & Acknowledgments
Winbond W25Q128FV/JV Datasheet

STM32 HAL SPI Documentation