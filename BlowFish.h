//
// Created by barna-tudor-cristian on 24/04/2024.
//
#include "stdint.h"

#ifndef SC_FINAL_PROJECT_BLOWFISH_H
#define SC_FINAL_PROJECT_BLOWFISH_H
#ifndef MASK_32
#define MASK_32 0X00000000FFFFFFFF
#endif


void BLOWFISH(char *input, char *output, char *key_file_name, int encrypt);

#endif //SC_FINAL_PROJECT_BLOWFISH_H
