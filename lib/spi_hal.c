#include "spi_hal.h"
#include <stdint.h>
#include <stdio.h>


volatile uint8_t spi_rx_data = 0;
volatile uint8_t spi_txrx_done = 0;

ISR(SPI_STC_vect){

    if (SPSR & 0x40){
        spi_rx_data = SPDR;
        spi_rx_data = 0;
        spi_txrx_done = 1;
    } else {
        spi_rx_data = SPDR;
        spi_txrx_done = 1;
    }
}

void spi_master_init(void){
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);
    PORTB |= 1 << PORTB2;

    SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (0 << CPHA) | (0b11 << SPR0);

}

void spi_send(uint8_t *tx, uint8_t *rx){
    spi_txrx_done = 0;
    SPDR = *tx;
    while(spi_txrx_done == 0);
    *rx = spi_rx_data;
}

void spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t len){
    PORTB &= ~(1 << PORTB2); // DC low 
    _delay_us(100);
    for(uint16_t i=0; i < len;i++){
        spi_send(&tx[i],&rx[i]);
    }
    PORTB |= 1 << PORTB2; // release spi bus (DC high)
    _delay_us(100);
}