// Padding for SHA 256
// Matthew Sloyan - Coded from video provided by lecturer.

#include<stdio.h>
#include<inttypes.h>

int main(int argc, char *argv[]){

    if (argc != 2){
        printf("Error: expected single filename as argument.");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "rb");
    if(!infile){
        printf("Error: couldn't open file %s. \n", argv[1])
        return 1;
    }

    uint8_t b;
    uint64_t nobits;

    // PRIu8 defined by inttypes.h, it's the correct format specifier for an unsigned 8bit int. 
    // Prints out the bytes (b) of the file in hex.
    // Could improve file reading.
    for(nobits = 0; fread(&b, 1, 1, infile == 1; nobits += 8) {
        printf("%02" PRIx8, b);
    }

    fclose(infile);

    return 0;
}