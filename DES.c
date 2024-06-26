//
// Created by barna-tudor-cristian on 24/04/2024.
//

#include <stdio.h>

#include "DES.h"

//  INITIAL PERMUTATION
//  INITIAL PERMUTATION
static const uint8_t DES_INITIAL_PERM_TABLE[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};
//  INVERSE INITIAL PERMUTATION
static const uint8_t DES_INVERSE_PERM_TABLE[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
};
//  EXPANSION
static const uint8_t DES_EXPANSION_TABLE[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
};
//  S-BOXES
static const uint8_t DES_S_BOXES[8][64] = {
        {
                14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7,
                0,  15, 7,  4,  14, 2,  13, 1,  10, 6, 12, 11, 9,  5,  3,  8,
                4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0,
                15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0, 6,  13
        },
        {
                15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                13, 8, 10, 1, 3, 15, 4, 2, 11, 6,       7,  12, 0,  5, 14, 9
        },
        {
                10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8,
                13, 7,  0,  9,  3,  4,  6,  10, 2,  8, 5,  14, 12, 11, 15, 1,
                13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7,
                1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5, 2,  12
        },
        {
                7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15,
                13, 8,  11, 5,  6,  15, 0,  3,  4,  7, 2,  12, 1,  10, 14, 9,
                10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4,
                3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14
        },
        {
                2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9,
                14, 11, 2,  12, 4,  7,  13, 1,  5,  0, 15, 10, 3,  9,  8,  6,
                4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14,
                11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3
        },
        {
                12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11,
                10, 15, 4,  2,  7,  12, 9,  5,  6,  1, 13, 14, 0,  11, 3,  8,
                9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6,
                4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0, 8,  13
        },
        {
                4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1,
                13, 0,  11, 7,  4,  9,  1,  10, 14, 3, 5,  12, 2,  15, 8,  6,
                1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2,
                6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2, 3,  12
        },
        {
                13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7,
                1,  15, 13, 8,  10, 3,  7,  4,  12, 5, 6,  11, 0,  14, 9,  2,
                7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8,
                2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5, 6,  11
        }
};
//  P-PERMUTATION TABLE
static const uint8_t DES_P_TABLE[32] = {
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
};
//  PERMUTED CHOICE 1
static const uint8_t DES_PERM_CHOICE_1_TABLE[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
};

//  PERMUTED CHOICE 2
static const uint8_t DES_PERM_CHOICE_2_TABLE[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};

// SHIFT SIZES BY ROUND
static const unsigned int DES_SHIFTS[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
/* Globals */
uint64_t DES_key;
uint64_t DES_permuted_choice_1 = 0, DES_permuted_choice_2 = 0;
uint64_t DES_round_keys[16] = {0};


/* functions */

uint64_t DES_read_key_from_file(char *key_file_name);

void DES_set_round_keys();

/* true = encrypt, false = decrypt*/
uint64_t DES_block(uint64_t block, int encrypt);

void DES(char *input, char *output, char *key_file_name, int encrypt);

/* ------------------------------------------------------- */

void DES(char *input, char *output, char *key_file_name, int encrypt) {
    // pre-work
    DES_key = DES_read_key_from_file(key_file_name);
    DES_set_round_keys();

    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "wb");

    uint64_t combined_block = 0;
    uint64_t result_block = 0;
    uint8_t block[8] = {0};

    int i;
    size_t sizeRead = 0;
    while ((sizeRead = fread(block, 1, sizeof(block), in)) > 0) {
        // read
        for (i = 0; i < sizeRead; ++i) {
            combined_block <<= 8;
            combined_block |= block[i] & 0xFF;
        }

        while (i < 8) {
            combined_block <<= 8;
            i++;
        }
        // process
        result_block = DES_block(combined_block, encrypt);
        // write
        for (i = 0; i < 8; ++i) {
            fprintf(out, "%c", (char) ((result_block >> (7 - i) * 8)) & 0xFF);
        }
    }
}

uint64_t DES_block(uint64_t block, int encrypt) {
    int i, j;
    uint32_t temp;
    // for S_boxes
    uint8_t row, col;

    uint32_t L, R;
    uint32_t sBoxOutput;
    uint32_t fFuncResult;

    // only using 48 bits
    uint64_t sBoxInput;

    uint64_t initPerm, invInitPerm;
    uint64_t preOutput;

    // Initial Permutation
    initPerm = 0;
    for (i = 0; i < 64; ++i) {
        initPerm = initPerm << 1;
        // DES_block -> LEFT to RIGHT -> (64 - init_perm)
        initPerm = initPerm | ((block >> (64 - DES_INITIAL_PERM_TABLE[i])) & 1);
    }

    // Separate into L|R
    L = (uint32_t) ((initPerm >> 32) & MASK_32);
    R = (uint32_t) (initPerm & MASK_32);

    // 16 rounds
    for (i = 0; i < 16; ++i) {
        sBoxInput = 0;
        // expand R
        for (j = 0; j < 48; j++) {
            sBoxInput <<= 1;
            sBoxInput = sBoxInput | (
                    (uint64_t) ((R >> (32 - DES_EXPANSION_TABLE[j])) & 1));
        }
        // encrypt/decrypt?
        if (encrypt == 1) {
            // XOR with current Round's key
            sBoxInput = sBoxInput ^ DES_round_keys[i];
        } else {
            // Decryption is the same, just using reverse key order;
            sBoxInput = sBoxInput ^ DES_round_keys[15 - i];
        }
        // S-Box Processing
        // 8 * 6 -> 8 * 4
        sBoxOutput = 0;
        for (j = 0; j < 8; j++) {
            //     Move 100001 mask to correct place V
            //  get the first,last bits V            |
            row = (uint8_t) ((sBoxInput & (S_BOX_ROW >> 6 * j)) >> (42 - 6 * j));
            //                       move the number to the end  ^

            //         x 0000 y -> xy
            row = (row >> 4) | (row & 1);
            //     Move 011110 mask to correct place V
            //  get the middle     bits V            |
            col = (uint8_t) ((sBoxInput & (S_BOX_COL >> 6 * j)) >> (42 - 6 * j + 1));
            //                       move the number to the end ^  abcd0 -> abcd ^

            sBoxOutput <<= 4;
            sBoxOutput |= (uint32_t) (DES_S_BOXES[j][16 * row + col] & 0x0f);

        }
        fFuncResult = 0;
        for (j = 0; j < 32; j++) {

            fFuncResult <<= 1;
            fFuncResult |= (sBoxOutput >> (32 - DES_P_TABLE[j])) & 1;

        }

        temp = R;
        R = L ^ fFuncResult;
        L = temp;
    }
    preOutput = (((uint64_t) R) << 32) | (uint64_t) L;
    invInitPerm = 0;
    for (i = 0; i < 64; i++) {
        invInitPerm <<= 1;
        invInitPerm |= (preOutput >> (64 - DES_INVERSE_PERM_TABLE[i])) & 1;

    }

    return invInitPerm;
}

uint64_t DES_read_key_from_file(char *key_file_name) {
    FILE *input = fopen(key_file_name, "rb");

    fseek(input, 0, SEEK_END);
    size_t FILE_SIZE = ftell(input);
    fseek(input, 0, SEEK_SET);

    if (FILE_SIZE != 8) {
        fprintf(stderr, "ERROR: DES_block key size must be exactly 64 bits/8 bytes");
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
    return key;

}


void DES_set_round_keys() {
    int i, j;
    // only using 28 bits;
    uint32_t C = 0, D = 0;

    for (i = 0; i < 56; i++) {
        DES_permuted_choice_1 <<= 1;
        DES_permuted_choice_1 = DES_permuted_choice_1 | (
                (DES_key >> (64 - DES_PERM_CHOICE_1_TABLE[i])) & 1);
    }

    C = (uint32_t) ((DES_permuted_choice_1 >> 28) & MASK_28);
    D = (uint32_t) (DES_permuted_choice_1 & MASK_28);

    for (i = 0; i < 16; ++i) {
        C = SHIFT_28(C, DES_SHIFTS[i]);
        D = SHIFT_28(D, DES_SHIFTS[i]);
        DES_permuted_choice_2 = (((uint64_t) C) << 28) | (uint64_t) D;
        for (j = 0; j < 48; ++j) {
            DES_round_keys[i] <<= 1;
            DES_round_keys[i] = DES_round_keys[i] | (
                    (DES_permuted_choice_2 >> (56 - DES_PERM_CHOICE_2_TABLE[j])) & 1);
        }
    }
}