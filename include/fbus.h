/*
 * fbus.h
 *
 *  Created on: 21.04.2014
 *      Author: andreasbehnke
 */

#ifndef FBUS_H_
#define FBUS_H_

#include <inttypes.h>
#include "hardware.h"
#include "fifo.h"

#define FBUS_FRAME_ID 0x1E
#define FBUS_PHONE_ID 0x00
#define FBUS_TERMINAL_ID 0x0C

typedef struct {
    uint8_t command;
    uint16_t data_size;
    uint16_t data_pos;
    uint8_t data[FBUS_MAX_DATA_LENGTH];
    uint8_t odd_checksum;
    uint8_t even_checksum;
} FBUS_FRAME;

// fbus frame parsing states
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

#define FBUS_STATE_INPUT_QUEUE_EMPTY 127
#define FBUS_STATE_FRAME_ERROR 255

#define IS_FBUS_ERROR() (fbus_state == FBUS_STATE_FRAME_ERROR)
#define IS_FBUS_READY() (fbus_state == FBUS_STATE_FRAME_READY)

#define FBUS_COMMAND_ACKNOWLEDGE 0x7f
#define FBUS_FRAME_HEADER 0x00, 0x01, 0x00

extern uint16_t fbus_bytes_read;

extern FBUS_FRAME fbus_input_frame;

extern void fbus_init(FILE *stream);

extern void fbus_input_clear();

extern uint8_t fbus_read_frame();

extern void fbus_reset_sequence();

extern void fbus_send_frame(uint8_t command, uint16_t data_size, uint8_t *data);

#ifdef DEBUG

#define fbus_debug_dump_frame(cmd, size, data) \
    fprintf(debug_stream, "command: %#.2x, length: %d, data: ", cmd, size); \
    for (int i = 0; i < size; ++i) { \
        if (data[i] == 0) { \
            fputs("0x00 ", debug_stream); \
        } else { \
            fprintf(debug_stream, "%#.2x ", data[i]); \
        } \
    } \
    fputs("\n", debug_stream); \

#define fbus_debug_dump_input() \
    fbus_debug_dump_frame(fbus_input_frame.command, fbus_input_frame.data_size, fbus_input_frame.data) \

#else
#define fbus_debug_dump_frame(cmd, size, data)
#define fbus_debug_dump_input()
#endif /* DEBUG */

#endif /* FBUS_H_ */
