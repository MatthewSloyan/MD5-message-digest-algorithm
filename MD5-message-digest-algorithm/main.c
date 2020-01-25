// C program that calculates the MD5 hash digest of an input - 4th year Theory of Algorithms
// by Matthew Sloyan G00348036

//Github Link:
//https://github.com/MatthewSloyan/MD5-message-digest-algorithm

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void main()
{
	FILE* filep;
	int userSelection = 0;

	printf("MD5 Hash Algorithm\n");
	printf("===============\n");

	//allow the user to enter a selection from the menu (intitial read)
	do
	{
		printf("\nPlease select an option\n [1] Enter text to hash\n [2] Hash with file\n");
		printf(" [0] To Exit\n");
		scanf_s("%d", &userSelection);

		if (userSelection < 0 || userSelection > 3) {
			printf("Error! The value entered must be between 0 and 2, please try again\n");
		}

	} while (userSelection < 0 || userSelection > 3); //validation to allow only numbers between 0 and 2

	// main while loop of program until 0 is encountered
	while (userSelection != 0)
	{
		//subsequent Read
		do
		{
			printf("\nPlease select an option\n [1] Enter text to hash\n [2] Hash with file\n");
			printf(" [0] To Exit\n");
			scanf_s("%d", &userSelection);

			if (userSelection < 0 || userSelection > 3) {
				printf("Error! The value entered must be between 0 and 2, please try again\n");
			}

		} while (userSelection < 0 || userSelection > 3); //validation to allow only numbers between 0 and 2
	} //while
}
