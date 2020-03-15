// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdint.h>

// Preprocessor variables.
#define WORD uint32_t

// Predifined hash values, defined in 
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

// union block that occupies the same address space and can take the form of a 64, 32, or 8 bit integer.
union block{
  uint64_t sixfour[8];
  uint32_t threetwo[16];
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
#define ROTL((x << n) | (x >> (32 - n)))

// Bit shifting functions used in rounds 1-4
// Code adapted from: https://www.slideshare.net/sourav777/sourav-md5
// Also cleaned up by following steps from: https://tools.ietf.org/html/rfc1321
#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; a = b + ROTL(a,s); }
#define GG(a,b,c,d,m,s,t) { a += G(b,c,d) + m + t; a = b + ROTL(a,s); }
#define HH(a,b,c,d,m,s,t) { a += H(b,c,d) + m + t; a = b + ROTL(a,s); }
#define II(a,b,c,d,m,s,t) { a += I(b,c,d) + m + t; a = b + ROTL(a,s); }

void nexthash(WORD *M, WORD *H){
	// All steps to hash each 16 word block. 
	// Adapted from documentation: https://tools.ietf.org/html/rfc1321
    WORD a, b, c, d;
    int i, j;

    for (i = 0; i < 16; i++){
        
    }

	// Assign initial values to temp variables in memory.
	a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
}

// PAD the message
int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status ){
    int i;

    // Replace with switch.
    if (*status = FINISH)
        return 0;

    if (*status = PAD0) {
        // Sets all bits to 0.
        // Take away 8byte int (64 - 8 = 56)
        for (i = 1; i < 56; i++){
            M->eight[i] = 0;  
        }

        M->sixfour[7] = bswap_64(*nobits);
        *status = FINISH;
        return 1;
    }

    // Read 1 byte 64 times.
    size_t nobytesread = fread(M->eight, 1, 64, infile);
    if (nobytesread == 64) {
        for (i = 0; i < 16; i++){
            M->threetwo[i] = bswap_32(M->threetwo[i]);
        }

        return 1;
    }

    // If we can fit all padding in last block in last block.
    if (nobytesread < 56){
        // Add 1 bit to the start.
        M->eight[nobytesread] = 0x80;
        for (i = nobytesread + 1; i < 56; i++){
            M->eight[i] = 0;
        }
        for (int i = 0; i < 14; i++){
            M->threetwo[i] = bswap_32(M->threetwo[i]);
        }

        M->sixfour[7] = bswap_64(*nobits);
        *status = FINISH;
        return 1;
    }

    // Read at least 56 bits but less than 64, so pad with 0's
    // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
    M->eight[nobytesread] = 0x80;
    for (i = nobytesread + 1; i < 64; i++){
        M->eight[i] = 0; 
    }
    for (int i = 0; i < 16; i++){
        M->threetwo[i] = bswap_32(M->threetwo[i]);
    }
    *status = PAD0;

    return 1;
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

char readFile()
{
	FILE *filep = NULL;
	char filePath[150];
	char fileString[300] = "";

	//printf("\nPlease enter the file path to the file you would like to hash: ");
	//scanf("%s", filePath);

	//open the that the player has entered if found
	filep = fopen("Test.txt", "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			//read in string from file.
			fscanf(filep, "%s", fileString);
		}
		printf("%s", fileString);
		fclose(filep); //close the file
	}

	return fileString;
}

void main()
{
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

    // Test wheter were on little or big endian machine.

    // The current padded message block.
    union block M;
    uint64_t nobits = 0;
    enum flag status = READ;

    // These 32 bit registers are initialized to the following values in hexadecimal, low-order bytes first.
    //const uint32_t digest[] = { 0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210 };
    // These 32 bit registers are initialized to the following values in hexadecimal, high-order bytes first.
    WORD H[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    // Read through all the padded message blocks.
    while (nextblock(&M, infile, &nobits, &status)){
      // Calculate the next hash value.
      // Pass memory address of M.
      nexthash(M.threetwo, H);
    }

    for(int i = 0; i < 8; i++){
      printf("%02" PRIx32, H[i]);
	}
    printf("\n");

    fclose(infile);

    return 0;

	// == MENU CODE == 
	// unsigned int userOption = 0;

	// char userString[100] = "";
	// char fileString[200] = "";

	// int i, j;

	// printf("MD5 Hash Algorithm\n");
	// printf("===============\n");

	// //allow the user to enter a selection from the menu (intitial read)
	// menuSystem(&userOption);

	// // main while loop of program until 0 is encountered
	// while (userOption != 0)
	// {
	// 	//switch based on the user input
	// 	switch (userOption)
	// 	{
	// 	case 1:
	// 		printf("\nPlease enter the string you would like to hash: ");
	// 		scanf("%s", userString);

	// 		printf("%s", userString);

	// 		break;
	// 	case 2:
	// 		strcpy(fileString, readFile());

	// 		if (fileString != "") {
	// 			printf("%s", fileString);
	// 		}
	// 		else {
	// 			printf("\nError loading file, please try again.");
	// 		}
	// 		break;
	// 	default:
	// 		printf("Invalid option\n");
	// 	}

	// 	//subsequent Read
	// 	menuSystem(&userOption);
	// } //while
}
