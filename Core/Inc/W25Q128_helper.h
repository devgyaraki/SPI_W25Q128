/*
 * W25Q128_helper.h
 *
 *  Created on: Jul 27, 2026
 *      Author: Roland
 */

#ifndef INC_W25Q128_HELPER_H_
#define INC_W25Q128_HELPER_H_

#define W25_CMD_WRITE_ENABLE 0x06
#define W25_CMD_READ_STATUS  0x05
#define W25_CMD_READ         0x03
#define W25_CMD_PROGRAM      0x02
#define W25_CMD_SECTOR_ERASE 0x20
#define W25_CMD_BLOCK_ERASE  0xD8
#define W25_CMD_CHIP_ERASE   0xC7
#define W25_CMD_JEDEC        0x9F

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class W25Q128 {
private:
    SPI_HandleTypeDef* hspi;
    GPIO_TypeDef* cs_port;
    uint16_t cs_pin;

public:
    W25Q128(SPI_HandleTypeDef* spi, GPIO_TypeDef* port, uint16_t pin);
    void cs_h(void);
    void cs_l(void);
    void write_enable(void);
    void write(uint32_t addr, uint8_t* buf, uint16_t len);
    void read(uint32_t addr, uint8_t* pData, uint16_t size);
    void waitBusy(uint8_t* pData);
    void Sector_erase(uint32_t addr);
    void Block_erase(uint32_t addr);
    void Chip_erase(void);
    void JEDEC_ID(uint8_t* pData);
};
#endif

#endif /* INC_W25Q128_HELPER_H_ */
