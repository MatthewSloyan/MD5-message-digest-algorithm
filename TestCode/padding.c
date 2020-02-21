// Padding for SHA 256
// Matthew Sloyan - Coded from video provided by lecturer.

#include<stdio.h>
#include<inttypes.h>

union block{
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
};

// k = Number of zeros to append.
uint64_t nozerobytes(uint64_t nobits) {

    //ULL = unsigned long long. Tells C compiler it should be a 64 bit int.
    uint64_t result = 512ULL - (nobits % 512ULL);

    // Add another block.
    if (result < 65)
        result += 512;

    // Take away bits.
    result -= 72;

    return (result / 8ULL);
}

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Error: expected single filename as argument.");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "rb");
    if(!infile){
        printf("Error: couldn't open file %s. \n", argv[1]);
        return 1;
    }

    //uint8_t b;
    uint64_t nobits;
    union block M;
    uint8_t i;

    // PRIu8 defined by inttypes.h, it's the correct format specifier for an unsigned 8bit int.
    // Prints out the bytes (b) of the file in hex.
    // Could improve file reading.
    for(nobits = 0, i = 0; fread(&M.eight[i], 1, 1, infile) == 1; nobits += 8) {
        printf("%02" PRIx8, M.eight[i]);
    }

    // Add 1 bit
    // Bits: 1000 0000 = 1 bit followed by 7 zeros to pad. Always has to be 8bits.
    printf("%02" PRIx8, 0x80); 

    // Pad with zeros
    for(uint64_t i = nozerobytes(nobits); i > 0; i--) {
        printf("%02" PRIx8, 0x00);
    }

    // Print out the length of the file in bytes (big endian)
    printf("%016" PRIx64 "\n", nobits);

    // Message is now 512 bits.

    fclose(infile);

    return 0;
}
