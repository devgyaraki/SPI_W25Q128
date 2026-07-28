/*
 * W25Q128_helper.c
 *
 *  Created on: Jul 27, 2026
 *      Author: Roland
 */

#include "W25Q128_helper.h"
#include "main.h"

//Konstruktor
W25Q128 :: W25Q128 (SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin) {
	hspi = spi;
	cs_port = port;
	cs_pin = pin;
}

//Chip select driving high
void W25Q128 :: cs_h (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_SET);
}

//Chip select driving low
void W25Q128 :: cs_l (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_RESET);
}


//Write enable command
void W25Q128 :: write_enable (void) {
	uint8_t cmd = W25_CMD_WRITE_ENABLE;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	cs_h ();
}

//Wait until BUSY bit clears
void W25Q128 :: waitBusy (uint8_t* pData) {
	uint8_t cmd = W25_CMD_READ_STATUS;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	HAL_SPI_Receive(hspi, pData, 1, 100);
	cs_h ();
}


//Page program
void W25Q128 :: write (uint32_t addr, uint8_t* buf,uint16_t len) {
	while (len > 0) {
		uint16_t page_offset = addr % 256;
		uint16_t space_left  = 256 - page_offset;

		uint16_t chunk = (space_left < len) ? space_left : len;

		write_enable ();

		uint8_t cmd [4];
		cmd [0] = W25_CMD_PROGRAM;
		cmd [1] = (addr >> 16) & 0xFF;
		cmd [2] = (addr >> 8) & 0xFF;
		cmd [3] = addr & 0xFF;

		cs_l ();
		HAL_SPI_Transmit(hspi, cmd, 4, 100);
		HAL_SPI_Transmit(hspi, buf, chunk, 100);
		cs_h ();

		uint8_t Status = 0;
		do {
			waitBusy(&Status);
		}while ((Status & 0x01) == 1);

		addr += chunk;
		buf  += chunk;
		len  -= chunk;
	}
}

void W25Q128::read(uint32_t addr, uint8_t* pData, uint16_t size) {
    uint8_t cmd[4];
    cmd[0] = W25_CMD_READ;
    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;

    cs_l();
    HAL_SPI_Transmit(hspi, cmd, 4, 100);
    HAL_SPI_Receive(hspi, pData, size, 100);
    cs_h();
}

//Sector deleting
void W25Q128 :: Sector_erase (uint32_t addr) {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd [4];
	cmd [0] = W25_CMD_SECTOR_ERASE;
	cmd [1] = (addr >> 16) & 0xFF;
	cmd [2] = (addr >> 8) & 0xFF;
	cmd [3] = addr & 0xFF;

	cs_l ();
	HAL_SPI_Transmit(hspi, cmd, 4, 100);
	cs_h ();

	do {
		waitBusy(&Status);
	}while ((Status & 0x01) == 1);
}

//Block deleting
void W25Q128 :: Block_erase (uint32_t addr) {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd [4];
		cmd [0] = W25_CMD_BLOCK_ERASE;
		cmd [1] = (addr >> 16) & 0xFF;
		cmd [2] = (addr >> 8) & 0xFF;
		cmd [3] = addr & 0xFF;

	cs_l ();
	HAL_SPI_Transmit(hspi, cmd, 4, 100);
	cs_h ();

	do {
		waitBusy(&Status);
	}while ((Status & 0x01) == 1);
}

//Complete Chip deleting
void W25Q128 :: Chip_erase (void) {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd;
	cmd = W25_CMD_CHIP_ERASE;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	cs_h ();

	do {
		waitBusy(&Status);
	}while ((Status & 0x01) == 1);
}


//Reas JEDEC ID
void W25Q128 :: JEDEC_ID (uint8_t* pData) {

	uint8_t cmd;
	cmd = W25_CMD_JEDEC;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	HAL_SPI_Receive(hspi, pData, 3, 100);
	cs_h ();
}
