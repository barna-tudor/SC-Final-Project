//
// Created by barna-tudor-cristian on 24/04/2024.
//
#include "stdint.h"

#ifndef SC_FINAL_PROJECT_DES_H
#define SC_FINAL_PROJECT_DES_H
#ifndef MASK_32
#define MASK_32 0X00000000FFFFFFFF
#endif
#ifndef MASK_28
#define MASK_28 0x000000000FFFFFFF
#endif
#define SHIFT_28(x, n) ( ((x << n) | (x >> (28-n)) ) & MASK_28 )
// 00000000 00000000 100001 00 and 40 0s, converted to hex
#define S_BOX_ROW 0x0000840000000000
// 00000000 00000000 011110 00 and 40 0s
#define S_BOX_COL 0x0000780000000000

/* FUNCTIONS */
void DES(char *input, char *output, char *key_file_name, int encrypt);

uint64_t DES_block(uint64_t block, int encrypt);

// For testing, exposed these funcs;
extern uint64_t DES_key;

void DES_set_round_keys();

#endif //SC_FINAL_PROJECT_DES_H
