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

## Test
I lot of testing went into to the development process, as described in the developer diary section of the README. After every new feature or change I made I would run several hashing tests on both files and strings. I would then compare the results with the samples supplied in the MD5 standard. Once I had full testing suites implemented, I would run my results with the testing method I created which sped up the testing process.

In the application I have implemented testing for the user to compare their result with the OpenSSL standard. This can be run two different ways. 
* If `--test/-t` is added to the command line with either `--file/-f` or `--string/-s` the result is compared to the result from the official OpenSSL implementation. As the OpenSSL package can only work with character arrays (strings) I have added code to open a file and read it into a buffer. However, it can only read text files (.txt). 
* If `--test/-t` is present on its own (`./main --test`) tests are run against predefined results from the MD5 standard and displayed to the user, with verification from the OpenSSL standard. These tests are laid out below.
1. ("") = d41d8cd98f00b204e9800998ecf8427e
2. ("a") = 0cc175b9c0f1b6a831c399e269772661
3. ("abc") = 900150983cd24fb0d6963f7d28e17f72
4. ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
5. ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
6. ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = d174ab98d277d9f5a5611c2c9f419d9f

## Algorithm
As outlined in the MD5 standard documentation there is five steps to perform the algorithm. We will first look at these five steps and then step through the implementation of this algorithm in this repository.

### MD5 Standard Algorithm
#### Step 1: Append Padding Bits
Padding is completed for each message block so that it is congruent to 448 bits, modulo 512 as defined in the MD5 standard [(MD5 Documentation)](https://tools.ietf.org/html/rfc1321). The message is extended to be 64 bits less than 512 bits. Padding is always performed even if the message is 448 bits, a full block of padding will be added after if this occurs. Padding is done by adding a “1” bit followed by any number of “0” bits until the padded message becomes 448 bits. 

#### Step 2: Append Padding Bits
64 bits are then added to complete the message from step 1. These 64 bits are the length of the message before padding bits were added. However, if this length is greater than 2^64, then only the low-order 64 bits are used. In this case the bits are added as two 32-bit words (low-order). The message is now 512 bits, which can be broken down into 16 32-bit words.

#### Step 3: Initialize MD Buffer
Before the hashing takes place an initial four-word buffer must be initialised (A, B, C and D) with the values below (low-order bytes first). These values will be updated and produce the final output.
* Word A: 01 23 45 67
* Word B: 89 ab cd ef
* Word C: fe dc ba 98
* Word D: 76 54 32 10

#### Step 4: Process Message in 16-Word Blocks
This is the most extensive step and contains the actual hashing. Initially four auxiliary functions must be defined which are described below. They are used to modify the bits accordingly and take in three 32-bit words and produce one 32-bit word.
* F(X,Y,Z) = XY v not(X) Z
* G(X,Y,Z) = XZ v Y not(Z)
* H(X,Y,Z) = X xor Y xor Z
* I(X,Y,Z) = Y xor (X v not(Z))

The next step is to loop over each of the 16-word blocks in the message. Begin by looping over each of the 16-word blocks in the message, then applying the four steps below on each iteration.
1. Copy the block to a new 32-bit array.
2. Copy initial hash values to variable a b c and d.
3. Undertake 4 rounds of 16 transforms, 64 in total using a formula specific to each round. Below is the formula for round 1 along with a description of what each value means. Values defined in the standard must be passed into each of these formulas for each round.
Round 1 formula: `a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)`
* **a, b, c, d** – initial hash values.
* **X[k]** – message.
* **T[i]** – 1 of 64 hash values defined in standard.
* **s** – number of positions to shift left by.
* **F(b,c,d)** - 1 of 4 auxiliary functions.
4. Add a b c and d to initial hash values A, B, C and D.

#### Step 5: Output
The message is completed (A, B, C, and D). It begins with low-order (little-endian) bytes and ends with high-order (big-endian) bytes.


