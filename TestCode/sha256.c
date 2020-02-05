// Secure Hash Algorithm 256-bit - Coded from video supplied by lecturer.
#include<stdio.h>
#include<stdint.h>

uint32_t Ch(uint32_t x, uint32_t y , uint32_t, z){
    // Section 4.1.2
    return (x & y) ^ (~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y , uint32_t, z){
    // Section 4.1.2
    return (x & y) ^ (x & z)^ (y & z);
}

// Push bits off to the right n places
uint32_t SHR(uint32_t x, int n){
    // Section 3.2
    return x >> n;
}

// Pushed bits off to the right n places but they are pushed in on the left again (loop around)
uint32_t ROTR(uint32_t x, int n){
    // Section 3.2
    // w = 32
    return (x >> n) | (x << (32 - n));
}

int main(int argc, char *argv[]){

    uint32_t x = 0x0f0f0f0f;
    uint32_t y = 0xcccccccc;
    uint32_t z = 0x55555555;

    // %08 = right aligned 8 characters padded with 0's from left.
    print("x            = %08x\n", x);
    print("y            = %08x\n", y);
    print("z            = %08x\n", z);

    printf("Ch(x, y, z) = %08x\n", Ch(x, y, z));
    printf("Maj(x, y, z)= %08x\n", Maj(x, y, z));

    return 0;
}