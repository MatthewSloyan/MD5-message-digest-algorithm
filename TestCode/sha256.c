// Secure Hash Algorithm 256-bit - Coded from video supplied by lecturer.
#include<stdio.h>
#include<stdint.h>

// Array of constants of first thirty-two bits of the 
// fractional parts of the cube roots of the first sixty four prime numbers
// Section 4.2.2
const uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 
};

// Initial hash values
// Section 5.5.3
uint32_t H[] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

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

// One way bit rotation functions described in Section 4.1.2
uint32_t Sig0(uint32_t x){
    return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
}

uint32_t Sig1(uint32_t x){
    return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
}

uint32_t sig0(uint32_t x){
    return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3);
}

uint32_t sig1(uint32_t x){
    return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10);
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

    printf("SHR(x, 4)   = %08x\n", SHR(x, 4));
    printf("ROTR(x, 4)  = %08x\n", ROTR(x, 4));

    printf("Sig0(x)  = %08x\n", Sig0(x));
    printf("Sig1(x)  = %08x\n", Sig1(x));
    printf("sig0(x)  = %08x\n", sig0(x));
    printf("sig0(x)  = %08x\n", sig0(x));

    printf("K[20]    = %08x\n", K[20]);
    printf("H[2]     = %08x\n", H[2]);

    return 0;
}