// Secure Hash Algorithm 256-bit - Coded from video supplied by lecturer.
// https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
#include<stdio.h>
#include<inttypes.h>

// Preprocessor - Section 2.1
#define WORD uint32_t

// Array of constants of first thirty-two bits of the 
// fractional parts of the cube roots of the first sixty four prime numbers
// Section 4.2.2
const WORD K[] = {
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

// Section 4.1.2
// Inline methods already in memory.
#define Ch(x, y, z) ((x & y) ^ (~x & z))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHR(x, n) (x >> n)
#define ROTR(x, n) ((x >> n) | (x << (32 - n)))
#define Sig0(x) (ROTR(x,  2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define Sig1(x) (ROTR(x,  6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sig0(x) (ROTR(x,  7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define sig1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// A sixty-four byte block of memory, accessed with different types.
// Occupies the same space in memory. (Structs, unions are pass by value)
typedef union {
  uint64_t sixfour[8];
  uint32_t threetwo[16];
  uint8_t eight[64];
} BLOCK;

// Read = Still reading file.
// Pad0 = get to eof, don't have enough space to do all padding. Pad rest with 0's
// pad1 = read to end block perfectly, E.g 512 bits + padding. 1 bit + 450 0 bits.
// Finish = Done all padding.
enum flag {READ, PAD0, FINISH};

// Section 6.2.2
void nexthash(WORD block *M, WORD *H){
    
    // Section 6.2.2
    WORD W[64];
    WORD a, b, c, d, e, f, g, h, T1, T2;
    int t;

    for (t = 0; t < 16; t++){
        W[t] = M[t];
    }

    for (t = 16; t < 64; t++){
        W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
    }

    a = H[0]; b = H[1]; c = H[2]; d = H[3];
    e = H[4]; f = H[5]; g = H[6]; h = H[7]; 

    for (t = 0; t < 64; t++){
        T1 = h + Sig1(e) + Ch(e, f, g) + K[t] + W[t];
        T2 = Sig0(e) + Maj(a, b, c);
        h = g; g = f; f = e; e = d + T1;
        d = c; c = b; b = a; a = T1 + T2;
    }
    
    H[0] = a + H[0]; H[1] = b + H[1]; H[2] = c + H[2]; H[3] = d + H[3];
    H[4] = e + H[4]; H[5] = f + H[5]; H[6] = g + H[6]; H[7] = h + H[7]; 
}

int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status ){

    // Replace with switch.
    if (*status = FINISH)
        return 0;

    if (*status = PAD0) {
        // Sets all bits to 0.
        // Take away 8byte int (64 - 8 = 56)
        for (int i = 1; i < 56; i++){
            M->eight[i] = 0;  
        }

        M.sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
    }

    // Read 1 byte 64 times.
    size_t nobytesread = fread(M->eight, 1, 64, infile);
    if (nobytesread == 64)
        return 1;

    // If we can fit all padding in last block in last block.
    if (nobytesread < 56){
        // Add 1 bit to the start.
        M.eight[nobytesread] = 0x80;
        for (int i = nobytesread + 1; i < 56; i++){
            M->eight[i] = 0;
        }

        M->sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
    }

    // Read at least 56 bits but less than 64, so pad with 0's
    // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
    M->eight[nobytesread] = 0x80;
    for (int i = nobytesread + 1; i < 64; i++){
        M->eight[i] = 0;
    }
    *status = PAD0;
    return 1;
}

int main(int argc, char *argv[]){

    // Expect and open a single filename.
    if (argc != 2){
        printf("Error: expected single filename as argument.");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "rb");
    if(!infile){
        printf("Error: couldn't open file %s. \n", argv[1]);
        return 1;
    }   

    // Initial hash values
    // Section 5.5.3
    WORD H[] = {
       0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // The current padded message block.
    union block M;
    uint64_t nobits = 0;
    enum flag status = READ;

    // Read through all the padded message blocks.
    while (nextblock(&M, infile, &nobits, &status)){
      // Calculate the next hash value.
      // Pass memory address of M.
      nexthash(M.threetwo, H);
    }

    for(int i = 0; i < 8; i++)
      print("%02" PRIx32, H[i]);
    printf("\n");

    fclose(infile);

    return 0;
}
