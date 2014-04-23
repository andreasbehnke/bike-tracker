/*
 * fbus.h
 *
 *  Created on: 21.04.2014
 *      Author: andreasbehnke
 */

#ifndef FBUS_H_
#define FBUS_H_

#include <inttypes.h>
#include <stdio.h>
#include "fifo.h"

#define FBUS_FRAME_ID 0x1E
#define FBUS_PHONE_ID 0x00
#define FBUS_TERMINAL_ID 0x0D

#define FBUS_MAX_DATA_LENGTH 512

typedef struct {
    uint8_t command;
    uint16_t data_size;
    uint16_t data_pos;
    uint8_t data[FBUS_MAX_DATA_LENGTH];
    uint8_t odd_checksum;
    uint8_t even_checksum;
} FBUS_FRAME;

#define FBUS_STATE_NO_FRAME 0
#define FBUS_STATE_FRAME_ID_READ 1
#define FBUS_STATE_DEST_ADR_READ 2
#define FBUS_STATE_SRC_ADR_READ 3
#define FBUS_STATE_CMD_READ 4
#define FBUS_STATE_SIZE_MSB_READ 5
#define FBUS_STATE_SIZE_LSB_READ 6
#define FBUS_STATE_DATA_READ 7
#define FBUS_STATE_PADDING_BYTE_READ 8
#define FBUS_STATE_EVEN_CHK_READ 9
#define FBUS_STATE_ODD_CHK_READ 10
#define FBUS_STATE_FRAME_READY FBUS_STATE_ODD_CHK_READ

#define FBUS_STATE_FRAME_ERROR 255

uint8_t fbus_state = FBUS_STATE_NO_FRAME;

uint16_t fbus_bytes_read = 0;

FBUS_FRAME fbus_input_frame;

extern uint8_t fbus_read_frame(FIFO *input);

#endif /* FBUS_H_ */