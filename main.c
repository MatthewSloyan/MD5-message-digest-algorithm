// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>
#include<byteswap.h>

// Preprocessor variables.
#define WORD uint32_t

// Predifined values for each round of hashing, as definined in section 3.4.
const uint32_t X[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

// Predifined hash values, defined in section 3.4: https://tools.ietf.org/html/rfc1321
const uint32_t T[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

// Pad0 = get to eof, don't have enough space to do all padding. Pad rest with 0's
// pad1 = read to end block perfectly, E.g 512 bits + padding. 1 bit + 450 0 bits.
// Finish = Done all padding.
enum flag {READ, PAD0, FINISH};

// 
enum input {FILETYPE, STRINGTYPE};

// union block that occupies the same address space and can take the form of a 64, 32, or 8 bit integer.
union block{
  uint64_t sixtyfour[8];
  uint32_t thirtytwo[16];
  uint8_t eight[64];
};

// Bitwise operators in c
// & (bitwise AND)   | (bitwise OR - v)
// ^ (bitwise XOR)   << (left shift) 
// >> (right shift)  ~ (bitwise NOT(X))

// four auxiliary functions (f, g, h and i) that each take as input three 32-bit words and produce as output one 32-bit word.
// Inline to descrease overhead and increase speed.
// F(X,Y,Z) = XY v not(X) Z
// G(X,Y,Z) = XZ v Y not(Z)
// H(X,Y,Z) = X xor Y xor Z
// I(X,Y,Z) = Y xor (X v not(Z))
#define F(x, y, z) ((x & y) | (~x & z)) 
#define G(x, y, z) ((x & z) | (y & ~z)) 
#define H(x, y, z) (x ^ y ^ z) 
#define I(x, y, z) (y ^ (x | ~z)) 

// Push bits off to the left n places, however they are pushed in on the right again (loop around)
#define ROTL(x, n) ((x << n) | (x >> (32 - n)))

// Bit shifting functions used in rounds 1-4
// Code adapted from: https://www.slideshare.net/sourav777/sourav-md5
// Also cleaned up by following steps from: https://tools.ietf.org/html/rfc1321
#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; a = b + ROTL(a,s); }
#define GG(a,b,c,d,m,s,t) { a += G(b,c,d) + m + t; a = b + ROTL(a,s); }
#define HH(a,b,c,d,m,s,t) { a += H(b,c,d) + m + t; a = b + ROTL(a,s); }
#define II(a,b,c,d,m,s,t) { a += I(b,c,d) + m + t; a = b + ROTL(a,s); }

void nexthash(WORD *M, WORD *H){
	  // All steps to hash each 16 word block. 
    unsigned int i, j;
    WORD W[16];
    WORD a, b, c, d;

    for (i = 0; i < 16; i++){
       W[i] = M[i];
    }
   
	  // Assign initial values to temp variables in memory.
	  a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];

    // In time I will make this into a loop to cut down loc.
    // Code adapted from: https://github.com/Souravpunoriyar/md5-in-c
    // Also following steps from: https://tools.ietf.org/html/rfc1321
    // == Round 1 ==
    FF(a,b,c,d, W[0], X[0], 0xd76aa478);
    FF(d,a,b,c, W[1], X[1], 0xe8c7b756);
    FF(c,d,a,b, W[2], X[2], 0x242070db);
    FF(b,c,d,a, W[3], X[3], 0xc1bdceee);
    FF(a,b,c,d, W[4], X[4], 0xf57c0faf);
    FF(d,a,b,c, W[5], X[5], 0x4787c62a);
    FF(c,d,a,b, W[6], X[6], 0xa8304613);
    FF(b,c,d,a, W[7], X[7], 0xfd469501);
    FF(a,b,c,d, W[8], X[8], 0x698098d8);
    FF(d,a,b,c, W[9], X[9], 0x8b44f7af);
    FF(c,d,a,b, W[10],X[10],0xffff5bb1);
    FF(b,c,d,a, W[11],X[11],0x895cd7be);
    FF(a,b,c,d, W[12],X[12],0x6b901122);
    FF(d,a,b,c, W[13],X[13],0xfd987193);
    FF(c,d,a,b, W[14],X[14],0xa679438e);
    FF(b,c,d,a, W[15],X[15],0x49b40821);

    // == Round 2 ==
    GG(a,b,c,d, W[1], X[16],0xf61e2562);
    GG(d,a,b,c, W[6], X[17],0xc040b340);
    GG(c,d,a,b, W[11],X[18],0x265e5a51);
    GG(b,c,d,a, W[0], X[19],0xe9b6c7aa);
    GG(a,b,c,d, W[5], X[20],0xd62f105d);
    GG(d,a,b,c, W[10],X[21],0x02441453);
    GG(c,d,a,b, W[15],X[22],0xd8a1e681);
    GG(b,c,d,a, W[4], X[23],0xe7d3fbc8);
    GG(a,b,c,d, W[9], X[24],0x21e1cde6);
    GG(d,a,b,c, W[14],X[25],0xc33707d6);
    GG(c,d,a,b, W[3], X[26],0xf4d50d87);
    GG(b,c,d,a, W[8], X[27],0x455a14ed);
    GG(a,b,c,d, W[13],X[28],0xa9e3e905);
    GG(d,a,b,c, W[2], X[29],0xfcefa3f8);
    GG(c,d,a,b, W[7], X[30],0x676f02d9);
    GG(b,c,d,a, W[12],X[31],0x8d2a4c8a);

    // == Round 3 ==
    HH(a,b,c,d, W[5], X[32],0xfffa3942);
    HH(d,a,b,c, W[8], X[33],0x8771f681);
    HH(c,d,a,b, W[11],X[34],0x6d9d6122);
    HH(b,c,d,a, W[14],X[35],0xfde5380c);
    HH(a,b,c,d, W[1], X[36],0xa4beea44);
    HH(d,a,b,c, W[4], X[37],0x4bdecfa9);
    HH(c,d,a,b, W[7], X[38],0xf6bb4b60);
    HH(b,c,d,a, W[10],X[39],0xbebfbc70);
    HH(a,b,c,d, W[13],X[40],0x289b7ec6);
    HH(d,a,b,c, W[0], X[41],0xeaa127fa);
    HH(c,d,a,b, W[3], X[42],0xd4ef3085);
    HH(b,c,d,a, W[6], X[43],0x04881d05);
    HH(a,b,c,d, W[9], X[44],0xd9d4d039);
    HH(d,a,b,c, W[12],X[45],0xe6db99e5);
    HH(c,d,a,b, W[15],X[46],0x1fa27cf8);
    HH(b,c,d,a, W[2], X[47],0xc4ac5665);

    // == Round 4 ==
    II(a,b,c,d, W[0], X[48],0xf4292244);
    II(d,a,b,c, W[7], X[49],0x432aff97);
    II(c,d,a,b, W[14],X[50],0xab9423a7);
    II(b,c,d,a, W[5], X[51],0xfc93a039);
    II(a,b,c,d, W[12],X[52],0x655b59c3);
    II(d,a,b,c, W[3], X[53],0x8f0ccc92);
    II(c,d,a,b, W[10],X[54],0xffeff47d);
    II(b,c,d,a, W[1], X[55],0x85845dd1);
    II(a,b,c,d, W[8], X[56],0x6fa87e4f);
    II(d,a,b,c, W[15],X[57],0xfe2ce6e0);
    II(c,d,a,b, W[6], X[58],0xa3014314);
    II(b,c,d,a, W[13],X[59],0x4e0811a1);
    II(a,b,c,d, W[4], X[60],0xf7537e82);
    II(d,a,b,c, W[11],X[61],0xbd3af235);
    II(c,d,a,b, W[2], X[62],0x2ad7d2bb);
    II(b,c,d,a, W[9], X[63],0xeb86d391);

    // Final step, add up all hash values.
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
}

// PAD the message
int nextblock(union block *M, FILE *infile, char *str, uint64_t *nobits, enum flag *status, enum input type){
    unsigned int i;
    size_t nobytesread;

    switch(*status){
        case FINISH:
            return 0;
        case PAD0:
            // Sets all bits to 0. Take away 8byte int (64 - 8 = 56)
            // We need an all-padding block without the 1 bit.
            for (int i = 0; i < 56; i++){
                M->eight[i] = 0x00;
            }
            
            M->sixtyfour[7] = *nobits;
            *status = FINISH;
            break;
        default: 
            // Check
            if (type  == FILETYPE){
                // Try to read 64 bytes from the file.
                nobytesread = fread(M->eight, 1, 64, infile);

                //printf("N: %02x", nobytesread);

               // printf("M: %02x", M->eight);
            }
            else {
               nobytesread = (size_t) strlen(str);

               i = 0;

               //https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
               while(str[i] != '\0')
               {
                  M->eight[i++] = (uint8_t) str[i];
               }
            }

            //printf("\nTest");

            *nobits += (8ULL * ((uint64_t) nobytesread));
            
            if (nobytesread < 56) {
                // We can put all padding in this block.
                M->eight[nobytesread] = 0x80;

                for (i = nobytesread + 1; i < 56; i++){
                    M->eight[i] = 0x00;
                }

                M->sixtyfour[7] = *nobits;
                *status = FINISH;
            } 
            else if (nobytesread < 64) {
                // Read at least 56 bits but less than 64, so pad with 0's
                // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
                M->eight[nobytesread] = 0x80;

                for (int i = nobytesread + 1; i < 64; i++){
                    M->eight[i] = 0x00;
                }
                *status = PAD0;
            }
    }

    return 1;
}

void startMD5(FILE *infile, char *str, unsigned int userOption){
    // Test wheter were on little or big endian machine.

    // The current padded message block.
    union block M;
    uint64_t nobits = 0;
    enum flag status = READ;
    enum input type;
    //char str[] = "message digest";

    // These 32 bit registers are initialized to the following values in hexadecimal, low-order bytes first.
    //const uint32_t digest[] = { 0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210 };
    // These 32 bit registers are initialized to the following values in hexadecimal, high-order bytes first.
    WORD H[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    if (userOption == 0){
       type = FILETYPE;
    }
    else {
       type = STRINGTYPE;
    }

    // Read through all the padded message blocks.
    while (nextblock(&M, infile, str, &nobits, &status, type)){
      // Calculate the next hash value.
      // Pass memory address of M.
      nexthash(M.thirtytwo, H);
    }

    for(int i = 0; i< 4; i++)
    {
      // Display result in little endian.
      // Code adapted from: https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
      printf("%02x%02x%02x%02x", (H[i] >> 0 )&0x000000ff, (H[i] >> 8)&0x000000ff, 
                                 (H[i] >> 16)&0x000000ff, (H[i] >> 24)&0x000000ff);
    }
    
    printf("\n");

    for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", H[i]);
    }
    printf("\n");
}

void menuSystem(unsigned int *userOption)
{
	unsigned int userOptionCopy = 0;

	do
	{
		printf("\nPlease select an option\n [1] Enter text to hash\n [2] Hash with file\n");
		printf(" [0] To Exit\n");
		scanf("%d", &userOptionCopy);

		*userOption = userOptionCopy;

		if (*userOption < 0 || *userOption > 2) {
			printf("Error! The value entered must be between 0 and 2, please try again\n");
		}

	} while (*userOption < 0 || *userOption > 2); //validation to allow only numbers between 0 and 2
}

int main(int argc, char *argv[])
{
	// Expect and open a single filename.
    if (argc == 2){
        FILE *infile = fopen(argv[1], "rb");
        
        if(!infile){
            printf("Error: couldn't open file %s. \n", argv[1]);
            return 1;
        }   

        fclose(infile);

        return 1;
    }
    else {
        //== MENU CODE == 
	      unsigned int userOption = 0;

	      char userString[100] = "";
	      char fileString[200] = "";

	      int i, j;

	      printf("MD5 Hash Algorithm\n");
        printf("===============\n");

	      //allow the user to enter a selection from the menu (intitial read)
	      menuSystem(&userOption);

	      // main while loop of program until 0 is encountered
	      while (userOption != 0)
	      {
	          //switch based on the user input
	          switch (userOption)
	 	        {
	 	            case 1:
	 		              printf("\nPlease enter the string you would like to hash: ");
	 		              scanf("%s", userString);

	 		              printf("%s", userString);

	 		              break;
	 	            case 2:
	 		              //strcpy(fileString, readFile());

	 		              if (fileString != "") {
	 			                printf("%s", fileString);
	 		              }
	 		              else {
	 		  	              printf("\nError loading file, please try again.");
	 		              }
	  	              break;
	 	            default:
	 		              printf("Invalid option\n");
	 	        }

	 	        //subsequent Read
	          menuSystem(&userOption);
	      } //while
    }

    return 0;
  }
