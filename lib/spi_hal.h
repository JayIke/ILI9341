#ifndef SPI_HAL_H
#define SPI_HAL_H

#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>




void spi_master_init(void);
void spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t len);


#endif
