## Introduction
This repository contains a full implementation of the MD5 algorithm written in C. This version is written to be as user friendly as possible and contains functionality for hashing both strings and files. Full command line parameters, a menu UI and testing are also implemented which will be described in detail in the “Run” section.

#### What is MD5 algorithm?
MD5 is a hashing algorithm takes an input of any length and produces a 128-bit (4 x 32bit values) output or “message digest”. The MD5 algorithm is an extension of the MD4 message-digest algorithm however is slightly slower but more secure. However, the MD5 algorithm has been exploited and broken, so it is not advised for encryption purposes. It is still suitable for determining the partition for a key in a partitioned database [(MD5)]( https://en.wikipedia.org/wiki/MD5).

#### Repository overview
On the repository there are several files and folders, which I will now describe.
* overview.md – Information about the repository, how to run the application, the algorithm used, and its complexities can be found here in this document.
* TestCode – Several test files used throughout the development process. These test files are written in C and Python. Some examples include working with bits and unions in C. Also included is a full implementation of the SHA256 hashing algorithm supplied to us by our lecturer. This algorithm was used to help the development of the MD5 algorithms due to its similarities in padding the message.
* .gitignore – Standard .gitignore file for Python and C. 
* main.c – MD5 implementation. 
* README.md – Contains information on how to compile and run the application and how it works. There is also a week by week developer diary of the work undertaken throughout this project.

## Download
* First, clone the repository using the following command `git clone https://github.com/MatthewSloyan/MD5-message-digest-algorithm` 
* Traverse using the command line to the folder you have cloned using the cd command `cd MD5-message-digest-algorithm`.

## Compile
To compile an executable version of the application you will need a compiler and some additional packages. If on Linux, you can install GCC (GNU Compiler Collection). Also, you will also need to install libssl-dev, which contains development libraries and header files needed to import OpenSSL. **OpenSSL is only used to compare and test the results of the algorithm when `--test/-t` is run.** 
* To install libssl-dev enter `sudo apt-get install libssl-dev`
* To install GCC enter `sudo apt install gcc` and then `gcc -o main main.c -lssl -lcrypto` to compile and executable version of the main.c file. **`-lssl -lcrypto` must be added for OpenSSL use when testing. It links the matching library.** Also the path to the installed package might be required. Usually, if on an Ubuntu machine GCC will usually be installed by default. 
* build-essential can also installed by entering `sudo apt install build-essential`. build-essential installs the required packages needed to compile C and C++ code, and includes GCC/g++ compilers. So, I would recommend using this with `gcc -o main main.c -lssl -lcrypto` to compile the application.

## Run
### Run with command parameters
Once compiled there are two ways to run the program, firstly by using command parameters and secondly using a simple to use UI. I will first describe how to use the number of possible command parameters.
Initially execute the compiled application using `./main` along with any of the command parameters below. This application can handle multiple parameters, but some must be run together. 
#### --file/-f
Command parameter that handles file input. To use this command enter `./main --file filename.txt`.  ‘-f’ can also be used instead of `--file`. This will read the file you have specified and returned the hash result to the user. `filename.txt` is the name of your file, with its extension. The file name is required and will display an error if not present. 
#### --string/-s
Command parameter that handles string input. To use this command enter `./main --string ‘Sample String`.  ‘-s’ can also be used instead of `--file`. Brackets around the string are only required for string longer than one word. This will read the string you have specified and returned the hash result to the user. ‘Sample String’ is the string that will be hashed. This string is required and will display an error if not present. 

### Additional Parameters (Optional)
#### --version/-v
This command can be added to the end of any input, and can be run on its own with `./main --version` or `./main -v`. It displays the current version of the application along with information about how to contact the developer.
#### --help/-h
This command can be added to the end of any input, and can be run on its own with `./main --help` or `./main -h`. It displays useful information about how to run the application.
#### --print/-p
This command parameter must be added along with the `--file/-f` or `--string/-s`. It allows the user to print the hash result returned to a file for later use. Presented is a menu with options 1 or 2. (1 = Yes and 2 = No). If yes is selected the user is given the option to enter a file name. This must include the file extension such as `.txt`. This file will be written to the current directory if just the file name is supplied. However, if `Test/Test.txt` it will be written to the folder Test.
#### --clock/-c
This command parameter must be added along with the `--file/-f` or `--string/-s`. It displays the running time of the hashing algorithm on a given string or file.
#### --test/-t
This command can be added to the end of any input, and can be run on its own with `./main --test` or `./main -t`. If it is with other parameters tests are run on the result to ensure it is correct, by using the OpenSSL MD5 standard import. If it is present on its own tests are run against predefined results from the MD5 documentation. More information on how testing is implemented can be found below in the “Test” section. 

### Run with UI
To run the full program with a UI, enter “./main” and a menu will be presented with options 1, 2, 3 or 0 which are described below. This menu will loop until 0 (Exit) is entered.
* 1 – Allows the user to enter a string to hash. A prompt will be displayed to input a string. Once entered the program will hash the string and return the hash to the user.
* 2 – Allows the user to enter a file to hash. A prompt will be displayed to input a file path to a chosen file E.g “TestCode/test.txt”. Once entered and the file is found the program will hash the file and return the result to the user.
* 3 – Allows the user to run a series of predefined tests and compare the results using the OpenSSL standard. The same tests are run when entering `./main --test`.
* 0 – Exit the program.
The menu UI contains all the customisable parameters described above automatically after each hash result is returned. Information such as printing to file, running tests on the hash result, and displaying the running time are automatically displayed.

### Samples
Below are some sample images of the application running and the results returned. The first image is running the application through the command line. The string “abc” is hashed, it is tested with the OpenSSL standard and the clock time is displayed. The second image shows the UI where a file is hashed, and the result is printed to a file.

