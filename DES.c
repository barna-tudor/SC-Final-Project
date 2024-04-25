//
// Created by barna-tudor-cristian on 24/04/2024.
//

#include <stdio.h>

#include "DES.h"

uint64_t DES_read_key(char *key_file_name) {

    FILE *input = fopen(key_file_name, "rb");

    fseek(input, 0, SEEK_END);
    size_t FILE_SIZE = ftell(input);
    fseek(input, 0, SEEK_SET);

    if (FILE_SIZE != 8) {
        fprintf(stderr, "ERROR: DES key size must be exactly 64 bits/8 bytes");
        fclose(input);
        return -1;
    }

    uint64_t key = 0;

    uint8_t in_arr[8];
    fread(in_arr, 1, sizeof(in_arr), input);

    for (int i = 0; i < 8; ++i) {
        key <<= 8;
        key |= in_arr[i] & 0xFF;
    }

    DES_KEY = key;

    return key;
}


uint64_t DES_initial_permutation(uint64_t block) {
    uint64_t result = 0;
    for (int i = 0; i < 64; ++i) {
        result = result << 1;
        //          because the DES standard counts bits from LEFT TO RIGHT
        result = result | ((block >> (64 - DES_INITIAL_PERM[i]))) & 1;
    }
    return result;
}

/* true = encrypt, false = decrypt*/
uint64_t DES(uint64_t block, _Bool mode) {

}