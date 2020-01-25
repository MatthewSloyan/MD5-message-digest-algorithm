// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

// Functions
void menuSystem(unsigned int *userOption);

void main()
{
	FILE *filep;
	unsigned int userOption = 0;

	char userString[100];
	char filePath[150];

	printf("MD5 Hash Algorithm\n");
	printf("===============\n");

	//allow the user to enter a selection from the menu (intitial read)
	menuSystem(&userOption);

	// main while loop of program until 0 is encountered
	while (userOption != 0)
	{

		//subsequent Read
		menuSystem(&userOption);
	} //while
}

void menuSystem(unsigned int *userOption)
{
	unsigned int userOptionCopy = 0;

	do
	{
		printf("\nPlease select an option\n [1] Enter text to hash\n [2] Hash with file\n");
		printf(" [0] To Exit\n");
		scanf_s("%d", &userOptionCopy);

		*userOption = userOptionCopy;

		if (*userOption < 0 || *userOption > 2) {
			printf("Error! The value entered must be between 0 and 2, please try again\n");
		}

	} while (*userOption < 0 || *userOption > 2); //validation to allow only numbers between 0 and 2
}
