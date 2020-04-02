// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>
#include<byteswap.h>

// Preprocessor variables.
#define WORD uint32_t

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

// Enum to determine if input is a file or a string.
enum input {FILETYPE, STRINGTYPE};

// union block that occupies the same address space and can take the form of a 64, 32, or 8 bit integer.
union block{
  uint64_t sixtyfour[8];
  uint32_t thirtytwo[16];
  uint8_t eight[64];
};

void nexthash(WORD *M, WORD *H){
	  // All steps to hash each 16 word block. Defined in section 3.4 
    unsigned int i, j, w;
    WORD W[16];
    WORD a, b, c, d;

    WORD abcd[4];

    // Copy message into new array.
    for (i = 0; i < 16; i++){
       W[i] = M[i];
    }
   
	  // Assign initial values to temp variables in memory.
	  a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];

    for (i=0; i<64; i++){
      if (i < 16){
        w = i; 
        transform(abcd[0], abcd[1], abcd[2], abcd[3], W[w], X[i], T[i], 0);
      } 
      else if (i >= 16 && i < 32){
        w = (5 * i + 1) % 16;
        transform(abcd[0], abcd[1], abcd[2], abcd[3], W[w], X[i], T[i], 1);
      } 
      else if (i >= 32 && i < 48){
        w = (3 * i + 5) % 16;
      } 
      else if (i >= 48){
        w = (7 * i) % 16;
      }

      // Move positions.
      if (i % == 0){
        abcd[0] = a;
        abcd[1] = b;
        abcd[2] = c;
        abcd[3] = d;
      } 
      if (i % == 0){
        abcd[0] = d;
        abcd[1] = a;
        abcd[2] = b;
        abcd[3] = c;
      } 
      else if (){
        abcd[0] = c;
        abcd[1] = d;
        abcd[2] = a;
        abcd[3] = b;
      } 
      else if (i >= 32 && i < 48){
        abcd[0] = b;
        abcd[1] = c;
        abcd[2] = d;
        abcd[3] = a;
      }     
    }

    // In time I will make this into a loop to cut down loc.
    // Code adapted from: https://github.com/Souravpunoriyar/md5-in-c
    // Also following steps from: https://tools.ietf.org/html/rfc1321
    // == Round 1 ==
    FF(a,b,c,d, W[0], X[0], T[0]);
    FF(d,a,b,c, W[1], X[1], T[1]);
    FF(c,d,a,b, W[2], X[2], T[2]);
    FF(b,c,d,a, W[3], X[3], T[3]);
    FF(a,b,c,d, W[4], X[4], T[4]);
    FF(d,a,b,c, W[5], X[5], T[5]);
    FF(c,d,a,b, W[6], X[6], T[6]);
    FF(b,c,d,a, W[7], X[7], T[7]);
    FF(a,b,c,d, W[8], X[8], T[8]);
    FF(d,a,b,c, W[9], X[9], T[9]);
    FF(c,d,a,b, W[10],X[10],T[10]);
    FF(b,c,d,a, W[11],X[11],T[11]);
    FF(a,b,c,d, W[12],X[12],T[12]);
    FF(d,a,b,c, W[13],X[13],T[13]);
    FF(c,d,a,b, W[14],X[14],T[14]);
    FF(b,c,d,a, W[15],X[15],T[15]);

    // == Round 2 ==
    GG(a,b,c,d, W[1], X[16],T[16]);
    GG(d,a,b,c, W[6], X[17],T[17]);
    GG(c,d,a,b, W[11],X[18],T[18]);
    GG(b,c,d,a, W[0], X[19],T[19]);
    GG(a,b,c,d, W[5], X[20],T[20]);
    GG(d,a,b,c, W[10],X[21],T[21]);
    GG(c,d,a,b, W[15],X[22],T[22]);
    GG(b,c,d,a, W[4], X[23],T[23]);
    GG(a,b,c,d, W[9], X[24],T[24]);
    GG(d,a,b,c, W[14],X[25],T[25]);
    GG(c,d,a,b, W[3], X[26],T[26]);
    GG(b,c,d,a, W[8], X[27],T[27]);
    GG(a,b,c,d, W[13],X[28],T[28]);
    GG(d,a,b,c, W[2], X[29],T[29]);
    GG(c,d,a,b, W[7], X[30],T[30]);
    GG(b,c,d,a, W[12],X[31],T[31]);

    // == Round 3 ==
    HH(a,b,c,d, W[5], X[32],T[32]);
    HH(d,a,b,c, W[8], X[33],T[33]);
    HH(c,d,a,b, W[11],X[34],T[34]);
    HH(b,c,d,a, W[14],X[35],T[35]);
    HH(a,b,c,d, W[1], X[36],T[36]);
    HH(d,a,b,c, W[4], X[37],T[37]);
    HH(c,d,a,b, W[7], X[38],T[38]);
    HH(b,c,d,a, W[10],X[39],T[39]);
    HH(a,b,c,d, W[13],X[40],T[40]);
    HH(d,a,b,c, W[0], X[41],T[41]);
    HH(c,d,a,b, W[3], X[42],T[42]);
    HH(b,c,d,a, W[6], X[43],T[43]);
    HH(a,b,c,d, W[9], X[44],T[44]);
    HH(d,a,b,c, W[12],X[45],T[45]);
    HH(c,d,a,b, W[15],X[46],T[46]);
    HH(b,c,d,a, W[2], X[47],T[47]);

    // == Round 4 ==
    II(a,b,c,d, W[0], X[48],T[48]);
    II(d,a,b,c, W[7], X[49],T[49]);
    II(c,d,a,b, W[14],X[50],T[50]);
    II(b,c,d,a, W[5], X[51],T[51]);
    II(a,b,c,d, W[12],X[52],T[52]);
    II(d,a,b,c, W[3], X[53],T[53]);
    II(c,d,a,b, W[10],X[54],T[54]);
    II(b,c,d,a, W[1], X[55],T[55]);
    II(a,b,c,d, W[8], X[56],T[56]);
    II(d,a,b,c, W[15],X[57],T[57]);
    II(c,d,a,b, W[6], X[58],T[58]);
    II(b,c,d,a, W[13],X[59],T[59]);
    II(a,b,c,d, W[4], X[60],T[60]);
    II(d,a,b,c, W[11],X[61],T[61]);
    II(c,d,a,b, W[2], X[62],T[62]);
    II(b,c,d,a, W[9], X[63],T[63]);

    // Final step, add up all hash values.
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
}

// PAD the message
int nextblock(union block *M, FILE *infile, char *str, uint64_t *nobits, enum flag *status, enum input type){
    unsigned int i = 0;
    size_t nobytesread;

    // PAD0 = Doesn't have enough space to do all padding. Pad rest with 0's
    // PAD1 = Read to end block perfectly, E.g 512 bits + padding. 1 bit + 450 0 bits.
    // FINISH = Padding complete.
    switch(*status){
        case FINISH:
            // Block is padded.
            return 0;
        case PAD0:
            // Pad block with 0's.

            // Sets all bits to 0. Take away 8byte int (64 - 8 = 56)
            // We need an all-padding block without the 1 bit.
            for (i = 0; i < 56; i++){
                M->eight[i] = 0x00;
            }
            
            M->sixtyfour[7] = *nobits;
            *status = FINISH;
            break;
        default: 
            // Check if file or string input.
            if (type  == FILETYPE){
                // Try to read 64 bytes from the file.
                nobytesread = fread(M->eight, 1, 64, infile);
            }
            else {
               // Otherwise get the bytes from the file using the length.
               nobytesread = (size_t) strlen(str);

               i = 0;
               // Loop through string and copy into block.
               //Code adapted from: https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
               while(str[i] != '\0')
               {
                  M->eight[i++] = (uint8_t) str[i];
               }
            }

            *nobits += (8ULL * ((uint64_t) nobytesread));
            
            // We can put all padding in this block if < 56.
            // Message is perfect size and can be finished in one step.
            if (nobytesread < 56) {
                // Append 1 bit to the start.
                M->eight[nobytesread] = 0x80;

                // Pad with 0's
                for (i = nobytesread + 1; i < 56; i++){
                    M->eight[i] = 0x00;
                }

                M->sixtyfour[7] = *nobits;
                *status = FINISH;
            } 
            // Message will not fit so we will need another padding block.
            // Read at least 56 bits but less than 64, so pad with 0's
            // Otherwise we have to read between 56 (incl) and 64 (excl) bytes.
            else if (nobytesread < 64) {
                // Append 1 bit to the start.
                M->eight[nobytesread] = 0x80;

                // Pad with 0's
                for (i = nobytesread + 1; i < 64; i++){
                    M->eight[i] = 0x00;
                }
                *status = PAD0;
            }
    }
    return 1;
}

// Check if the current machine is little or big endian.
// Code adapted from: https://helloacm.com/how-to-find-out-whether-a-machine-is-big-endian-or-little-endian-in-cc/
int checkByteOrder() {
  short int word = 0x0001;
  char *b = (char *)&word;
  return (b[0] ? 1 : 0);
}

// print hash to file.
void printToFile(WORD *H, int order)
{
	unsigned int userOption = 0;
  char fileString[256] = "";
  FILE *file;

  // Menu system to ask the user if they want to print to file or not (Yes = 1, No = 2)
	do
	{
		printf("\nWould you like to print result to file?\n [1] Yes\n [2] No\n");
		scanf("%d", &userOption);

		if (userOption < 1 || userOption > 2) {
			printf("Error! The value entered must be 1 or 2, please try again\n");
		}

	} while (userOption < 1 || userOption > 2); //validation

  //switch based on the user input
	switch (userOption)
	{
	  case 1:
	    printf("\nPlease enter the name of the file with extension (.txt): ");
      scanf("%s", fileString);

      // Open file for writing.
      // Code adapted from: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
      file = fopen(fileString, "w+");

      if(!file){
        printf("Error: Creating file. Please try again.\n");
      }
      else {
          // Print in either little or big endian depending on check at the start.
         if (order == 1){
            for(int i = 0; i< 4; i++)
            {
            // Display result in little endian.
            // Code adapted from: https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
            fprintf(file, "%02x%02x%02x%02x", (H[i] >> 0 )&0x000000ff, (H[i] >> 8)&0x000000ff, 
                                              (H[i] >> 16)&0x000000ff, (H[i] >> 24)&0x000000ff);
            }
          }
          else if (order == 0) {
            // Print as is, in big endian.
            for (int i = 0; i < 4; i++){
              fprintf(file, "%08" PRIx32 "", H[i]);
            }
          }

          printf("\nResult printed to file successfully\n");      
      }

      fclose(file);
      break;    
    default:
	    printf("Invalid option\n");
    break;
  }
}

// Menu system used in main
void menuSystem(unsigned int *userOption)
{
	unsigned int userOptionCopy = 0;

  // Loop until correct input is entered.
	do
	{
		printf("\nPlease select an option\n [1] Enter text to hash\n [2] Hash with file\n");
		printf(" [0] To Exit\n");
		scanf("%d", &userOptionCopy);

    // userOption is updated back in main.
		*userOption = userOptionCopy;

		if (*userOption < 0 || *userOption > 2) {
			printf("Error! The value entered must be between 0 and 2, please try again\n");
		}

	} while (*userOption < 0 || *userOption > 2); //validation to allow only numbers between 0 and 2
}

// MD5 method which controls, hashing and printing final hash values.
int startMD5(FILE *infile, char *str, unsigned int userOption){

    // Test wheter were on little or big endian machine.
    int order = checkByteOrder();

    // The current padded message block.
    union block M;
    uint64_t nobits = 0;
    enum flag status = READ;
    enum input type;

    // These 32 bit registers are initialized to the following values in hexadecimal, high-order bytes first.
    WORD H[] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };

    // Set type depending on menu input.
    // 0 = Reading from a file.
    // 1 = Reading from a string.
    if (userOption == 0){
       type = FILETYPE;
    }
    else if (userOption == 1){
       type = STRINGTYPE;
    }
    else {
       return 1;
    }

    // Read through all the padded message blocks.
    while (nextblock(&M, infile, str, &nobits, &status, type)){
      // Calculate the next hash value.
      // Pass memory address of M and H.
      nexthash(M.thirtytwo, H);
    }

    printf("Hash: ");

    // Print final result in either little or big endian depending on check at the start.
    if (order == 1){
      for(int i = 0; i< 4; i++)
      {
        // Display result in little endian.
        // Code adapted from: https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
        printf("%02x%02x%02x%02x", (H[i] >> 0 )&0x000000ff, (H[i] >> 8)&0x000000ff, 
                                   (H[i] >> 16)&0x000000ff, (H[i] >> 24)&0x000000ff);
      }
    }
    else if (order == 0) {
      // Print as is, in big endian.
      for (int i = 0; i < 4; i++){
        printf("%08" PRIx32 "", H[i]);
      }
    }
    else {
      printf("Error hashing, please try again.");
    } 
    printf("\n");

    // Ask the user if they would like to print result to file.
    printToFile(H, order);
}

int main(int argc, char *argv[])
{
    FILE *infile;
    char str[] = "";

	  // Check if there's input from the company line,
    // as hashing can be completed quickly without menu UI. 
    if (argc == 2){
        infile = fopen(argv[1], "rb");
        
        if(!infile){
            printf("Error: couldn't open file %s. \n", argv[1]);
            return 1;
        } 
        
        // Start hashing the file.
        startMD5(infile, str, 0);
    }
    else {
        //== MENU CODE == 
	      unsigned int userOption = 0;

	      char userString[256] = "";
	      char fileString[256] = "";

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

                    printf("\nInput String: %s \n", userString);

                    // Start hashing the string.
                    startMD5(infile, userString, 1);
	 		              break;
	 	            case 2:
                    printf("\nPlease enter the file path of the file to hash: ");
	 		              scanf("%s", fileString);

                    infile = fopen(fileString, "rb");
        
                    if(!infile){
                        printf("Error: couldn't open file %s. \n", argv[1]);
                        return 1;
                    } 	 
                    
                    // Start hashing the file.
                    startMD5(infile, userString, 0);
                    break;
	 	            default:
	 		              printf("Invalid option\n");
	 	        }

	 	        //subsequent Read
	          menuSystem(&userOption);
	      } //while
    }

    fclose(infile);
    return 0;
  }
