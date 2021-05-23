#ifndef __RADIO_COMM__H
#define __RADIO_COMM__H

#include "stdint.h"
#include "command.h"
#include <stdbool.h>

#define NRF_CHNNEL1 7
#define NRF_CHNNEL2 23
#define NRF_CHNNEL3 59
#define NRF_CHNNEL4 109
#define NRF_CHNNEL5 112
#define NRF_ADDRESS1 0x1234567893
#define NRF_PAYLOAD_SIZE 12

static void panic(void);
void radio_init(int channel);

void radio_read(char *buffer, uint8_t len);
int8_t radio_write(char *buffer, uint8_t len);

bool radio_transmit_command(struct Command cmd);

#endif

