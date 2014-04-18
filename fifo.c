/*
 * fifo.c
 *
 *  Created on: 15.04.2014
 *      Author: andreasbehnke
 */

#include <stdlib.h>
#include "include/fifo.h"

void fifo_clear(FIFO *fifo) {
    fifo->read = 0;
    fifo->write = 0;
}

uint8_t fifo_write(FIFO *fifo, uint8_t byte) {
    uint8_t next = ((fifo->write + 1) & FIFO_BUFFER_MASK);
    if (fifo->read == next) {
        return FIFO_FULL;
    }
    fifo->buffer[fifo->write] = byte;
    fifo->write = next;
    return FIFO_OK;
}

uint8_t fifo_read(FIFO *fifo, uint8_t *byte) {
    if (fifo->read == fifo->write) {
        return FIFO_EMPTY;
    }
    *byte = fifo->buffer[fifo->read];
    fifo->read = (fifo->read + 1) & FIFO_BUFFER_MASK;
    return FIFO_OK;
}
