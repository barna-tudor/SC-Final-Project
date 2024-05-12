#include <stdio.h>
#include <unistd.h>

#include <stdbool.h>
#include <ctype.h> // for isprint()

#include "DES.h"


void printHelp() {
    printf("Usage:\n");
    printf("    SC_Final_Project.exe <-i FILE1> [-o FILE2] <{-e | -d}> <{-D | -B | -R}> <-k FILE3>\n");
    printf("    SC_Final_Project.exe [-h]\n");
    printf("Where:\n");
    printf("<-option> = mandatory\n");
    printf("[-option] = optional\n");
    printf("{ a | b } = choose 1, mutually exclusive\n");
    printf("Options:\n");
    printf("    <-i FILE>,\n");
    printf("        Indicates the FILE to be en/-decrypted;");
    printf("    [-o FILE],\n");
    printf("        Specifies output file;\n");
    printf("        Note: If not specified, the program will generate a file named 'output';\n");
    printf("    <{-e | -d}>,\n");
    printf("        Whether to Encrypt or Decrypt the input;\n");
    printf("        Note: -e and -d are mutually exclusive;\n");
    printf("              The right-most argument given will take priority;\n");
    printf("    <-k FILE>,\n");
    printf("        The FILE containing the key to be used;\n");
    printf("    <{-D|-B|-R}>,\n");
    printf("        The algorithm to be used in en-/decrypting:\n");
    printf("        DES | BlowFish | RSA\n");
    printf("        Note: mutually exclusive;\n");
    printf("              The right-most argument given will take priority;\n");
    printf("    [-h]\n");
    printf("        Display this message;\n");
    printf(" Note: Due to the nature of block cyphers, I had to append 0s to final blocks\n");
    printf("       that are smaller than 64 bits. As a result, when using DES/Blowfish to \n");
    printf("       en/de-crypt there will be trailing NULLs\n");
    printf("       (I don't know how to circumvent this)\n");
}

int main(int argc, char **argv) {
    // Flags
    bool iFlag = false;
    bool oFlag = false;
    bool eFlag = false;
    bool dFlag = false;
    bool kFlag = false;
    bool DESFlag = false;
    bool BLFSHFlag = false;
    bool RSAFlag = false;
    bool hFlag = false;

    // Option Arguments
    char *iValue = NULL;
    char *oValue = "output";
    char *kValue = NULL;

    // Files
    FILE *input = NULL;
    FILE *output = NULL;
    FILE *key = NULL;

    // Parsing Argv
    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, "deDBRhi:o:k:")) != -1) {
        switch (c) {
            case 'i':
                iFlag = true;
                iValue = optarg;
                break;
            case 'o':
                oFlag = true;
                oValue = optarg;
                break;
            case 'k':
                kFlag = true;
                kValue = optarg;
                break;
            case 'h':
                hFlag = true;
                break;
            case 'd':
                dFlag = true;
                break;
            case 'e':
                eFlag = true;
                break;
            case 'D':
                DESFlag = true;
                BLFSHFlag = false;
                RSAFlag = false;
                break;
            case 'B':
                DESFlag = false;
                BLFSHFlag = true;
                RSAFlag = false;
                break;
            case 'R':
                DESFlag = false;
                BLFSHFlag = false;
                RSAFlag = true;
                break;
            case '?':
                if (optopt == 'i' || optopt == 'o' || optopt == 'k')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                abort();
        }
    }

    if (hFlag ||
        (!iFlag && !oFlag && !kFlag &&
         (!DESFlag || !RSAFlag || !BLFSHFlag))) {
        printHelp();
        return 0;
    }
    input = fopen(iValue, "rb");
    if (input == NULL) {
        fprintf(stderr, "File '%s' not found!", iValue);
        abort();
    }
    fclose(input);
    key = fopen(kValue, "rb");
    if (key == NULL) {
        fprintf(stderr, "File '%s' not found!", iValue);
        abort();
    }
    fclose(key);

    if (DESFlag) {
        DES(iValue, oValue, kValue, eFlag);
        return 0;
    }
    if (BLFSHFlag) {

        return 0;
    }
    if (RSAFlag) {
        return 0;
    }
    return 0;
}
