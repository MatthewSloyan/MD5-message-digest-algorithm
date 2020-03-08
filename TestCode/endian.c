// Endian tests - Coded from video supplied by lecturer.
#include<stdio.h>
#include<inttypes.h>
#include<byteswap.h>

uint64_t swap_endian(uint64_t x){
    uint64_t mask[8];
    mask[0] = 0xff;

    for (int i = 1; i < 8; i++){
        mask[i] = mask[0] << (8 * i);
    }

    uint64_t y = 
           (x >> 56) & mask[0]
        ^ ((x >> 40) & mask[1])
        ^ ((x >> 24) & mask[2])
        ^ ((x >>  8) & mask[3])
        ^ ((x <<  8) & mask[4])
        ^ ((x << 24) & mask[5])
        ^ ((x << 40) & mask[6])
        ^ ((x << 56) & mask[7]);

    return y;
}

int main(int argc, char *argv[]){
    uint64_t x = 0xaa0f5f0c7e810180;

    printf("%016" PRIx64 " -> %016" PRIx64 " -> %016" PRIx64 "\n", x, swap_endian(x), swap_endian(swap_endian(x)));

    printf("%016" PRIx64 " -> %016" PRIx64 " -> %016" PRIx64 "\n", x, bswap_64(x), bswap_64(bswap_64(x)));

    return 0;
}
