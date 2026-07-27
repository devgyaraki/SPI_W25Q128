/*
 * W25Q128_helper.c
 *
 *  Created on: Jul 27, 2026
 *      Author: Roland
 */

#include "W25Q128_helper.h"
#include "main.h"

class W25Q128 {
	private:
	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* cs_port;
	uint16_t cs_pin;

	public:
	W25Q128 (SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin);
	void write_enable ();
	void write ();
	void read ();
	void erase ();
	void waitBusy ();
};

//Konstruktor
W25Q128 :: W25Q128 (SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin) {
	hspi = spi;
	cs_port = port;
	cs_pin = pin;
}	//-------------------------------------------Ready

void cs_h (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_SET);
}	//-------------------------------------------Ready

void cs_l (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_RESET);
}	//-------------------------------------------Ready

void W25Q128 :: write_enable () {
	uint8_t cmd = 0x06;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	cs_h ();
}	//-------------------------------------------Ready

void W25Q128 :: write (uint32_t addr, uint8_t* buf,uint16_t len) {
	write_enable ();

	uint8_t cmd [4];
	cmd [0] = 0x02;
	cmd [1] = (addr >> 16) & 0xFF;
	cmd [2] = (addr >> 8) & 0xFF;
	cmd [3] = addr & 0xFF;

	cs_l ();
	HAL_SPI_Transmit(hspi, cmd, 4, 100);
	HAL_SPI_Transmit(hspi, buf, len, 100);
	cs_h ();
}	//-------------------------------------------Ready

void W25Q128::read(uint32_t addr, uint8_t* pData, uint16_t size) {
    uint8_t cmd[4];
    cmd[0] = 0x03;
    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;

    cs_l();
    HAL_SPI_Transmit(hspi, cmd, 4, 100);
    HAL_SPI_Receive(hspi, pData, size, 100);
    cs_h();
}	//-------------------------------------------Ready

void W25Q128 :: waitBusy (uint8_t* pData) {
	uint8_t cmd;
	cmd = 0x05;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	HAL_SPI_Receive(hspi, pData, 1, 100);
	cs_h ();
}	//-------------------------------------------Ready

void W25Q128 :: Sector_erase (uint32_t addr) {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd [4];
	cmd [0] = 0x20;
	cmd [1] = (addr >> 16) & 0xFF;
	cmd [2] = (addr >> 8) & 0xFF;
	cmd [3] = addr & 0xFF;

	cs_l ();
	HAL_SPI_Transmit(hspi, cmd, 4, 100);
	cs_h ();

	do {
		waitBusy(&Status);
	}while ((Status & 0x01) == 1);
}	//-------------------------------------------Ready

void W25Q128 :: Block_erase (uint32_t addr) {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd [4];
		cmd [0] = 0xD8;
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

void W25Q128 :: Chip_erase () {
	write_enable ();

	uint8_t Status = 0;

	uint8_t cmd;
		cmd = 0xC7;

	cs_l ();
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	cs_h ();

	do {
		waitBusy(&Status);
	}while ((Status & 0x01) == 1);
}
