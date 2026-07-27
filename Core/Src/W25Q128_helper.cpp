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

}

void cs_h (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_SET);
}

void cs_l (void){
	HAL_GPIO_WritePin(cs_port,cs_pin,GPIO_PIN_RESET);
}

void W25Q128 :: write_enable () {
	uint8_t cmd = 0x06;

	cs_l;
	HAL_SPI_Transmit(hspi, &cmd, 1, 100);
	cs_h;
}

void W25Q128 :: write () {

}

void W25Q128 :: waitBusy () {

}

void W25Q128 :: Sector_erase () {

}

void W25Q128 :: Block_erase () {

}

void W25Q128 :: Chip_erase () {

}

void W25Q128 :: read () {

}
