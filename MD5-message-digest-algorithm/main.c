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
char readFile();

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
			scanf_s("%s", userString);

			printf("%s", userString);

			break;
		case 2:
			strcpy_s(fileString, sizeof fileString, readFile());

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

char readFile()
{
	FILE *filep = NULL;
	char filePath[150];
	char fileString[300] = "";

	printf("\nPlease enter the file path to the file you would like to hash: ");
	scanf_s("%s", filePath);

	//open the that the player has entered if found
	filep = fopen_s(filep, filePath, "r");

	if (filep == NULL)
	{
		printf("The file cannot be opened\n");
	}

	else
	{
		while (!feof(filep))
		{
			//read in string from file.
			fscanf_s(filep, "%s", fileString);
		}
		fclose(filep); //close the file
	}

	return fileString;
}
