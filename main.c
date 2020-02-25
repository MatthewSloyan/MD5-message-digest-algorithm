// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdint.h>

// Function Definition
void menuSystem(unsigned int *userOption);
char readFile();
uint32_t f(uint32_t x, uint32_t y , uint32_t, z);

// hese 32 bit registers are initialized to the following values in hexadecimal, low-order bytes first.
const uint32_t digest[] = { 0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210 };

//F(X,Y,Z) = XY v not(X) Z
//G(X,Y,Z) = XZ v Y not(Z)
//H(X,Y,Z) = X xor Y xor Z
//I(X,Y,Z) = Y xor (X v not(Z))

// & (bitwise AND)
// | (bitwise OR - v)
// ^ (bitwise XOR)
// << (left shift) 
// >> (right shift) 
// ~ (bitwise NOT(X))

// four auxiliary functions (f, g, h and i) that each take as input three 32-bit words and produce as output one 32-bit word.

uint32_t h(uint32_t x, uint32_t y , uint32_t, z){
    return x ^ y ^ z;
}

uint32_t i(uint32_t x, uint32_t y , uint32_t, z){
    return y ^ (x |~ z);
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
			strcpy(fileString, readFile());

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
