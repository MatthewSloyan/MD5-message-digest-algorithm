// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

// Imports
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

// Preprocessor variables.
#define WORD uint32_t

// Bitwise operators in C used in below functions.
// Learned about operators from: https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
// & (bitwise AND)   | (bitwise OR - v)
// ^ (bitwise XOR)   << (left shift)
// >> (right shift)  ~ (bitwise NOT(X))

// Four auxiliary functions (F, G, H and I) that each take as input three 32-bit words and produce as output one 32-bit word.
// Inline to descrease overhead and increase speed.
// Used in TRANSFORM.
// F(X,Y,Z) = XY v not(X) Z
// G(X,Y,Z) = XZ v Y not(Z)
// H(X,Y,Z) = X xor Y xor Z
// I(X,Y,Z) = Y xor (X v not(Z))
#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

// Push bits off to the left n places, however they are pushed in on the right again (loop around)
// Used in TRANSFORM.
#define ROTL(x, n) ((x << n) | (x >> (32 - n)))

// Bit shifting functions used in rounds 1-4
// Code initially created with four functions FF, GG, HH and II but I developed one inline
// function that works with all rounds of r.
// Initially adapted from: https://www.slideshare.net/sourav777/sourav-md5
// Also cleaned up by following steps from: https://tools.ietf.org/html/rfc1321

// a, b, c, d – initial hash values.
// m – message.
// s – number of positions to shift left by.
// t – 1 of 64 hash values defined in standard.
// r = round number (1-4).
// F(b,c,d) - 1 of 4 auxiliary functions.
#define TRANSFORM(a, b, c, d, m, s, t, r) \
{                                       \
  if (r == 1)                           \
    a += F(b, c, d) + m + t;            \
  else if (r == 2)                      \
    a += G(b, c, d) + m + t;            \
  else if (r == 3)                      \
    a += H(b, c, d) + m + t;            \
  else if (r == 4)                      \
    a += I(b, c, d) + m + t;            \
  a = b + ROTL(a, s);                   \
}

// Number of positions to shift left, as defined in documentation: https://tools.ietf.org/html/rfc1321
const uint32_t X[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 
    11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 
    10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

// Predifined hash values, as defined in documentation: https://tools.ietf.org/html/rfc1321
const uint32_t T[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

// Pad0 = get to eof, don't have enough space to do all padding. Pad rest with 0's
// pad1 = read to end block perfectly, E.g 512 bits + padding. 1 bit + 450 0 bits.
// Finish = Done all padding.
enum flag
{
  READ,
  PAD0,
  FINISH
};

// Union block that occupies the same address space and can take the form of a 64, 32, or 8 bit integer.
// Used to hold message.
// I learned more about unions from: https://www.tutorialspoint.com/cprogramming/c_unions.htm
union block {
  uint64_t sixtyfour[8];
  uint32_t thirtytwo[16];
  uint8_t eight[64];
};

// Flag set by ‘--verbose’.
static int verbose_flag;

// Options used by getops_options.
// Code adapted from: https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
static struct option long_options[] =
{
 // These options set a flag. */
 {"verbose", no_argument,       &verbose_flag, 1},
 {"brief",   no_argument,       &verbose_flag, 0},
 // These options don’t set a flag.
 // We distinguish them by their indices.
 {"test",    no_argument,       0, 't'},
 {"help",    no_argument,       0, 'h'},
 {"version", no_argument,       0, 'v'},
 {"string",  required_argument, 0, 's'},
 {"file",    required_argument, 0, 'f'},
 {0, 0, 0, 0}
};

// Global variable used to determine if little or big endian machine.
unsigned int order;

// === Hashing ===
// Function that hashes each 16 bit block,
// Using steps defined in section 3.4: https://tools.ietf.org/html/rfc1321
void hashBlock(WORD *M, WORD *H)
{
  unsigned int i, j, messageIndex, round;
  WORD W[16];
  WORD a, b, c, d;

  // Copy message into new array.
  for (i = 0; i < 16; i++)
  {
    W[i] = M[i];
  }

  // Assign initial values to temp variables in memory.
  a = H[0];
  b = H[1];
  c = H[2];
  d = H[3];

  // Loop for each step (4 rounds of 16 steps).
  for (i = 0; i < 64; i++)
  {
    // Check which round currently in (1 - 4).
    // If i < 16 then in round 1.
    // messageIndex is the index of the message to pass to transform.
    // Maths to calculate index was adapted from MD5 Pseudocode below:
    // https://en.wikipedia.org/wiki/MD5
    if (i < 16)
    {
      messageIndex = i;
      round = 1;
    }
    else if (i < 32)
    {
      messageIndex = (5 * i + 1) % 16;
      round = 2;
    }
    else if (i < 48)
    {
      messageIndex = (3 * i + 5) % 16;
      round = 3;
    }
    else
    {
      messageIndex = (7 * i) % 16;
      round = 4;
    }

    // Check which transform to use, a b c d rotates every 4 iterations.
    // This was developed from initial version with all steps had their own line.
    // I wanted to cut this down and make it simpler to understand.
    // Pass in round above to determine which auxiliary function to use.
    if (i % 4 == 0)
    {
      // W – message.
      // X – 1 of 64 hash values defined in standard.
      // T – number of positions to shift left by.
      TRANSFORM(a, b, c, d, W[messageIndex], X[i], T[i], round);
    }
    else if (i % 4 == 1)
    {
      TRANSFORM(d, a, b, c, W[messageIndex], X[i], T[i], round);
    }
    else if (i % 4 == 2)
    {
      TRANSFORM(c, d, a, b, W[messageIndex], X[i], T[i], round);
    }
    else if (i % 4 == 3)
    {
      TRANSFORM(b, c, d, a, W[messageIndex], X[i], T[i], round);
    }
  }

  // Final step, add updated hash values to intial hash values.
  H[0] += a;
  H[1] += b;
  H[2] += c;
  H[3] += d;
}

// === Padding ===
// block *M - pointer to message block
// bytesread - the number of bytes read in from file or string.
// *nobits - the length of the initial message to be appended to 448 bit block.
// *status - current status of padding. 
// Adapted from videos supplied: https://github.com/ianmcloughlin/sha256
int padBlock(union block *M, FILE *infile, char *str, uint64_t *nobits, enum flag *status, int userOption)
{
  unsigned int i = 0;
  size_t bytesread;

  // PAD0 = Doesn't have enough space to do all padding. Pad rest with 0's
  // PAD1 = Read to end block perfectly, E.g 512 bits + padding. 1 bit + 450 0 bits.
  // FINISH = Padding complete.
  switch (*status)
  {
  case FINISH:
    // Block is padded.
    return 0;
  case PAD0:
    // Pad block with 0's.
    // Sets all bits to 0. Take away 8byte int (64 - 8 = 56)
    // We need an all-padding block without the 1 bit.
    for (i = 0; i < 56; i++)
    {
      M->eight[i] = 0x00;
    }

    // Append the length of the message to finish padding. (512 bits)
    M->sixtyfour[7] = *nobits;
    *status = FINISH;
    break;
  default:
    // Check if file or string input.
    if (userOption == 0){
      // Try to read 64 bytes from the file.
      bytesread = fread(M->eight, 1, 64, infile);
    }
    else {  
      // Otherwise get the bytes from the file using the length.
      // Code adapted from: https://www.programiz.com/c-programming/library-function/string.h/strlen
      bytesread = (size_t) strlen(str);

      i = 0;
      // Loop through string and copy into block.
      //Code adapted from: https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
      while(str[i] != '\0')
      {
        M->eight[i++] = (uint8_t) str[i];
      }
    }
    // Get lenght of the inital message, to be appending to final block.
    *nobits += (8ULL * ((uint64_t)bytesread));

    // We can put all padding in this block if < 56.
    // Message is perfect size and can be finished in one step.
    if (bytesread < 56)
    {
      // Append 1 bit to the start.
      M->eight[bytesread] = 0x80;

      // Pad with 0's
      for (i = bytesread + 1; i < 56; i++)
      {
        M->eight[i] = 0x00;
      }

      // Append the length of the message to finish padding. (512 bits)
      M->sixtyfour[7] = *nobits;
      *status = FINISH;
    }
    // Message will not fit so we will need another padding block.
    // Read at least 56 bits but less than 64, so pad rest with 0's
    else if (bytesread < 64)
    {
      // Append 1 bit to the start.
      M->eight[bytesread] = 0x80;

      // Pad rest of message with 0s and set status to PAD0
      // so another padding block will be added.
      for (i = bytesread + 1; i < 64; i++)
      {
        M->eight[i] = 0x00;
      }
      *status = PAD0;
    }
  }
  return 1;
}

// == Helper Functions ==
// Check if the current machine is little or big endian.
// I learned more about Enianness from: https://en.wikipedia.org/wiki/Endianness
// Code adapted from: https://helloacm.com/how-to-find-out-whether-a-machine-is-big-endian-or-little-endian-in-cc/
int checkByteOrder()
{
  short int word = 0x0001;
  char *b = (char *)&word;
  return (b[0] ? 1 : 0);
}

// Print hash result to file.
void printToScreen(WORD *H, int order)
{
  printf("Hash: ");

  // Print final result in either little or big endian depending on check at the start.
  if (order == 1)
  {
    for (int i = 0; i < 4; i++)
    {
      // Display result in little endian.
      // Code adapted from: https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
      printf("%02x%02x%02x%02x", (H[i] >> 0) & 0x000000ff, (H[i] >> 8) & 0x000000ff,
             (H[i] >> 16) & 0x000000ff, (H[i] >> 24) & 0x000000ff);
    }
  }
  else if (order == 0)
  {
    // Print as is, in big endian.
    for (int i = 0; i < 4; i++)
    {
      printf("%08" PRIx32 "", H[i]);
    }
  }

  printf("\n");
}

// Print hash result to file.
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

    if (userOption < 1 || userOption > 2)
    {
      printf("Error! The value entered must be 1 or 2, please try again\n");
    }

  } while (userOption < 1 || userOption > 2); //validation

  //switch based on the user input
  switch (userOption)
  {
    case 1:
      // Yes option.
      printf("\nPlease enter the name of the file with extension (.txt): ");
      scanf("%s", fileString);

      // Open file for writing.
      // Code adapted from: https://www.tutorialspoint.com/cprogramming/c_file_io.htm
      file = fopen(fileString, "w+");

      if (!file)
      {
        printf("Error: Creating file. Please try again.\n");
      }
      else
      {
        // Print in either little or big endian depending on check at the start.
        if (order == 1)
        {
          for (int i = 0; i < 4; i++)
          {
            // Display result in little endian.
            // Code adapted from: https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
            fprintf(file, "%02x%02x%02x%02x", (H[i] >> 0) & 0x000000ff, (H[i] >> 8) & 0x000000ff,
                    (H[i] >> 16) & 0x000000ff, (H[i] >> 24) & 0x000000ff);
          }
        }
        else if (order == 0)
        {
          // Print as is, in big endian.
          for (int i = 0; i < 4; i++)
          {
            fprintf(file, "%08" PRIx32 "", H[i]);
          }
        }

        printf("\nResult printed to file successfully\n");
      }

      fclose(file);
      break;
    case 2:
      // No option.
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

    if (*userOption < 0 || *userOption > 2)
    {
      printf("Error! The value entered must be between 0 and 2, please try again\n");
    }

  } while (*userOption < 0 || *userOption > 2); //validation to allow only numbers between 0 and 2
}

// These 32 bit registers are initialized to the following values in hexadecimal, high-order bytes first.
void initialiseHash(WORD *H)
{
  H[0] = 0x67452301;
  H[1] = 0xefcdab89;
  H[2] = 0x98badcfe;
  H[3] = 0x10325476;
}

// == MD5 Runner ==
// MD5 method which controls, hashing and printing final hash values.
// Can take in string or file values.
void startMD5(WORD *H, FILE *infile, char *str, unsigned int userOption)
{ 
  // The current padded message block.
  union block M;
  uint64_t nobits = 0;
  enum flag status = READ;

  initialiseHash(H);

  // == PADDING & HASHING ==
  // Read through all the padded message blocks.
  while (padBlock(&M, infile, str, &nobits, &status, userOption))
  {
    // Calculate the next hash value.
    // Pass memory address of M and H.
    hashBlock(M.thirtytwo, H);
  }

  // Print the result to screen depending on architecture.
  printToScreen(H, order);  
}

// == HELP Display ==
void displayHelp()
{
  printf("\nBelow is some of the useful features of the application and how to run them.\n\n");

  printf("Hash file:            ./main.c --file/-f filename.txt\n");
  printf("Hash string:          ./main.c --string/-s filename.txt\n");
  printf("Run sample tests:     ./main.c --test/-s\n");
  printf("Run tests on file:    ./main.c --file/-f filename.txt --test/-t\n");
  printf("Run tests on string:  ./main.c --string/-s filename.txt --test/-t\n");
  printf("Run UI:               ./main.c\n");
  printf("Get help:             ./main.c --help/-h\n");
  printf("Check version:        ./main.c --version/-v\n");

  printf("\nAll the above command parameters can be shortened using just the first letter with -.\n");
  printf("E.g (--file/-f, --string/-s, --help/h, --version/v, --test/-t.)\n\n");
}

// == Display Version ==
void displayVersion()
{
  printf("\nVERSION:    1.0\n");
  printf("\nDEVELOPER:  Matthew Sloyan\n\n");
}

// == Tests ==
// Run predefined tests.
void runTests(WORD *H)
{
  FILE *file;
  char arr[6][128] = {
    "", "a", "abc", "message digest", "abcdefghijklmnopqrstuvwxyz",
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" 
  };

  for (int i = 0; i < 6; i++)
  {
    printf("Value: %s ", arr[i]);
    printf("\n");

    // Run startMD5 with string option.
    startMD5(H, file, arr[i], 1);
    
    // Compare against OpenSSL MD5

    printf("\n\n");
  }

  exit (0);
}

// == main == 
// Runner that handles different ways to run program.
// E.g. Hashing from file through command line parameter, hash string or hash a file from a file path.
int main(int argc, char *argv[])
{
  FILE *infile;
  int c;
  unsigned int fFlag = 0, sFlag = 0, tFlag = 0;
  char fileToHash[256] = "", stringToHash[256] = "";

  // These 32 bit registers are initialized to the following values in hexadecimal, high-order bytes first.
  // Will be initialised each time in each startMD5 method call.
  WORD H[4];

  // Test wheter were on little or big endian machine.
  // Stored as global variable as it's never edited.
  order = checkByteOrder();

  // Check if there's input from the comand line,
  // as hashing can be completed quickly without menu UI.
  if (argc >= 2)
  {
    // Code adapted from: https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html   
    while (1)
    {
      // getopt_long stores the option index here.
      int option_index = 0;

      c = getopt_long (argc, argv, "thvs:f:", long_options, &option_index);

      // Detect the end of the options.
      if (c == -1)
        break;

      switch (c)
      {
        case 0:
          // If this option set a flag, do nothing else now.
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 't':
          tFlag = 1; 
          break;

        case 'h':         
          displayHelp();     
          break;

        case 'v':
          displayVersion();
          break;

        case 's':
          sFlag = 1;
          strcpy (stringToHash, optarg);
          //printf ("option -s with value `%s'\n", optarg);
          break;

        case 'f':
          fFlag = 1;
          strcpy (fileToHash, optarg);
          //printf ("option -f with value `%s'\n", optarg);
          break;

        case '?':
          // getopt_long already printed an error message.
          break;

        default:
          abort ();
       }
    }

    // Check flags (If string, if file, if just tests).
    if (sFlag == 1){      
      startMD5(H, infile, stringToHash, 1);

      if (tFlag == 1){
        // Hash string and test result.
      }
    }
    else if (fFlag == 1){     
      infile = fopen(fileToHash, "rb");

      if (!infile)
      {
         printf("Error: couldn't open file %s. \n", fileToHash);
         return 1;
      }

      startMD5(H, infile, stringToHash, 0);

      if (tFlag == 1){
        // Hash file and test result.
      }
    }
    else if (tFlag == 1){
      printf ("option value: Tests \n");

      // Just print tests
      runTests(H);
    }

    // Instead of reporting ‘--verbose’and ‘--brief’ as they are encountered,
    // we report the final status resulting from them. 
    if (verbose_flag)
      puts ("verbose flag is set");

    // Print any remaining command line arguments (not options).
    if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    } 

    exit (0);
  }
  else
  {
    //== MENU CODE ==
    unsigned int userOption = 0;

    char userString[256] = "";
    char fileString[256] = "";

    int i, j;

    printf("MD5 Hash Algorithm\n");
    printf("==================\n");

    // Allow the user to enter a selection from the menu (intitial read)
    // userOption is updated in function using pointer.
    menuSystem(&userOption);

    // Main while loop of program until 0 is encountered
    while (userOption != 0)
    {
      // switch based on the user input
      switch (userOption)
      {
      case 1:
        printf("\nPlease enter the string you would like to hash: ");
        scanf("%s", userString);

        printf("\nInput String: %s \n", userString);

        // Start hashing the string. 1 = string.
        startMD5(H, infile, userString, 1);

        // Ask the user if they would like to print result to file.
        printToFile(H, order);
        break;
      case 2:
        printf("\nPlease enter the file path of the file to hash: ");
        scanf("%s", fileString);

        infile = fopen(fileString, "rb");

        if (!infile)
        {
          printf("Error: couldn't open file %s.\n");
          return 1;
        }

        // Start hashing the file. 0 = file.
        startMD5(H, infile, userString, 0);

        // Ask the user if they would like to print result to file.
        printToFile(H, order);
        break;
      default:
        printf("Invalid option\n");
      }

      // Subsequent Read
      menuSystem(&userOption);
    } // while
  }

  fclose(infile);
  return 0;
}

