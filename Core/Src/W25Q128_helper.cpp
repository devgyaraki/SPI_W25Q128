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

}

void cs_l (void){

}

void W25Q128 :: write_enable () {

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
