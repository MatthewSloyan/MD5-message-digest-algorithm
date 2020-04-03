# Theory of Algorithms Project 

**Name:** Matthew Sloyan

**Student ID:** G00348036

# Project statement
You must write a program in the C programming language [2] that calculates the MD5 hash digest of an input. The algorithm is specified in the Request For Comments 1321 document supplied by the Internet Engineering Task Force [5]. The only pre-requisite is that your program performs the algorithm — you are free to decide what input the algorithm should be performed on. I suggest you allow the user to input some free text or a filename via the command line.

# Platforms
Coded and tested on a Linux Debian 10 (buster) Google Cloud Virtual Machine. All code was written in VI and compiled by connecting to the VM using SSH.

# How to run program
* First, clone the repository using the following command `git clone https://github.com/MatthewSloyan/MD5-message-digest-algorithm` 
* Traverse using the command line to the folder you have cloned using the cd command.
* Compile main.c file to execute using `gcc -o main main.c` or `make main` if build build-essentials is installed.
* Execute file using `./main` to load menu UI or `./main <filename.ex>` to quickly hash a file. (filename.ex is the path to a file with  it's extension).
* More information on how to use UI can be foud below in the User Guide section.

# User Guide
Below you’ll find a basic guide to the user interface, in the “How it works” section is a description of how this works in the code behind.

There are two ways to run the program, firstly it can be run quickly by using `./main test.txt` to get a hash result on the file passed in as a parameter (test.txt). To run the full program with a UI, enter `./main` and a menu will be presented with options 1, 2 or 0 which are described below.

* 1 – Allows the user to enter a string to hash. A prompt will be displayed to input a string. Once entered the program will hash the string and return the hash to the user.
* 2 – Allows the user to enter a file to hash. A prompt will be displayed to input a file path to a chosen file E.g `TestCode/test.txt`. Once entered and the file is found the program will hash the file and return the result to the user.
* 0 – Exit the program.

On all three options the user then has the option to print the result to a file. Presented is a menu with options 1 or 2. 1 is Yes and 2 is No. If yes is selected the user is given the option to enter the file name. This must include the file extension such as .txt. This file will be written to the current directory.

# How it works
More information on each of these steps above can be found in the Research & Development Diary section below.

### Padding the message
Padding is completed for each message block so that it is congruent to 448 bits, modulo 512 as defined in the MD5 standard [(MD5 Documentation)](https://tools.ietf.org/html/rfc1321). The message is extended to be 64 bits less than 512 bits. Padding is always performed even if the message is 448 bits, a full block of padding will be added after if this occurs. Padding is done by adding a “1” bit followed by any number of “0” bits until the padded message becomes 448 bits. 64 bits are then added to complete the message. These 64 bits are the length of the message before padding was added.

Initially the message (file or string) in bytes is passed into the padding function. This is run in a while loop until the message has been fully padded (status returns FINISH). This is achieved by first checking the status. If it’s the default status get the length of the message which will be appended at the end and check if the bytes are less than 56, if so then the message can be padded in one block. A “1” is added then a string of “0” up till 56 bits. The 64 bit value is then added to complete the padding. If bytes read is between 56 and 64 then a new block of padding is needed, so it will pad with zeros. Again, add a “1” bit to the start, pad till the end (64 bits) and set status to PAD0 for next iteration. If the status is PAD0 then pad a full block with zeros and append the 64 message length to finish the padding, and set status to FINISH. If the status is FINISH then the padding is complete which will return 0 and finish the loop.

### Hashing the message
Before the hashing takes place an initial four-word buffer must be initialised (MD – A B C D) with the values below. This buffer becomes the final hash output.
* word A: 01 23 45 67
* word B: 89 ab cd ef
* word C: fe dc ba 98
* word D: 76 54 32 10

When the message is padded the initial hash values above and message block are passed into the hashing function. This function hashes each 16 bit block as they are passed in and a number of steps are undertake as defined in section 3.4 [(MD5 Documentation)](https://tools.ietf.org/html/rfc1321). 
* Step 1 - Copy the block to a new 32 bit array W[].
* Step 2 – Copy initial hash values to variable A B C D
* Step 3 – Undertake 4 rounds of 16 transforms, 64 in total using a formula specific to each round. Below is the formula for round 1 along with what each value means.

`a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)`

**a, b, c, d** – initial hash values.
**X[k]** – message.
**T[i]** – 1 of 64 hash values defined in standard.
**s** – number of positions to shift left by.
**F(b,c,d)** - 1 of 4 auxiliary functions (Seen below).

In each round auxiliary functions F, G, H, I are used to provide bit operations on the three inputs.

* F(X,Y,Z) = XY v not(X) Z
* G(X,Y,Z) = XZ v Y not(Z)
* H(X,Y,Z) = X xor Y xor Z
* I(X,Y,Z) = Y xor (X v not(Z))

Once all transforms are applied append initial values onto A B C D.

### Output
When the message is hashed it is in big endian byte order, an initial check is done to check the architecture of the system. If it’s a little-endian machine the results is converted. If it’s big endian the result is just printed.

More information on each of these steps above can be found in the Research & Development Diary section below.

# Project Plan
* Week 1 - Initial research and setup.
* Week 2 - Setup Google Cloud VM and learn VI.
* Week 3 - Write basic menu and file writing functions.
* Week 4 - Start to implement the MD5 algorithm while continuing with videos.
* Week 5 - Continue MD5 implementation.
* Week 6 - Continue MD5 implementation.
* Week 7 - Improve and test implementation.
* Week 8 - Optimise solution.
* Week 9 - Adding finishing touches, tidying up code, and adding extras.

# Research & Development Diary

#### Start of Semester to 26-1-20
Each week I watched the various videos posted on Moodle and read into more about each topic such as Hash Functions, Turing Machines, SHA and MD5 standard. I also researched online more about C and working with VI as we haven’t worked with this in a little while. This has really helped me with this project and will be a valuable skill going forward in my career. 

#### Week of 26-1-20 to 2-2-20
From the project spec I realised the project would need an interface with the ability to read a file, so I decided to implement this in C which I would use down the line to implement the MD5 algorithm with. Also, using the videos supplied on Moodle, I setup the Google Virtual Machine and coded some basic test programs using VI in Python and C. 

#### Week of 2-2-20 to 9-2-20
This week I began to look at coding some C test files using VI on my Google Cloud VM. This helped me learn more about VI and using the command line. I watched a few tutorials to achieve this which helped a lot and will be useful for writing, testing and debugging the MD5 implementation [(VI Tutorial)](https://www.youtube.com/watch?v=HMpB28l1sLc). Some of the test files included learning about bits, so I researched what bits and bytes are to get a better understanding [(Bits and bytes)](https://web.stanford.edu/class/cs101/bits-bytes.html). I also learned how to shift bits around using << (left shift) and how they can be read, modified and printed to screen. This spawned further research into all the possible bitwise operators found in C which are listed below implementation [(Bitwise operators in C)](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/).

* & (bitwise AND)   
* | (bitwise OR - v)
* ^ (bitwise XOR)   
* << (left shift) 
* >> (right shift)  
* ~ (bitwise NOT(X))

#### Week of 9-2-20 to 16-2-20
This week I continued watching the videos supplied, which were based on the coding the Sha256 algorithm [(Sha256 Documentation)](https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf). From these I developed some test files on setting up the algorithm, adding bit shifting and auxiliary functions. I also learned more about types in C (8, 32 & 64 bit integers). I researched these further to learn about different types such as unsigned which is a data type specifier, that makes a variable only represent positive natural numbers. It can be applied to the int, short, long and char types only. [(C data types)](https://www.tutorialspoint.com/cprogramming/c_data_types.htm). Also using stdint.h import in C, access to integer types with a width of exactly 8, 16, 32, or 64 bits is possible using uint8_t, uint16_t, uint32_t and uint64_t as the type. This ensures consistency of types across any machine, which is especially useful when working with bits [(stdint.h)](http://www.cplusplus.com/reference/cstdint/).

#### Week of 16-2-20 to 23-2-20
This week I continued with the videos supplied by the lecturer to add a padding function to the Sha256 algorithm. This is to pad each message block so that it is congruent to 448 bits, modulo 512. The message is extended to be just 64 bits shy of 512 bits. Padding is always performed even if the message is 448 bits, a full block of padding will be added after if this occurs. Padding is done by adding a “1” bit followed by any number of “0” bits until the padded message becomes 448 bits. 64 bits are then added to complete the message. This allows the compiler to be able to find the message length and message by reading back until the “1” bit is found. This method of padding is used throughout multiple hashing algorithms and will be useful as a basis for coding the MD5 implementation [(Sha256 Documenation)](https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf). I also learned the ULL keyword in C, which is unsigned long long. E.g. This tells C compiler it should be a 64 bit integer.

#### Week of 23-2-20 to 1-3-20
Continuing with the video series supplied this week I implemented unions, fixed errors with the padding and added a flag to the padding. Unions are an interesting and quite similar to Structs in C. I did some further research to learn more about them. A union is a special data type in C which allows storage of different types in the same memory address. Only one member can contain a value at one time. They are an extremely efficient way of using the same memory location [(Unions)](https://www.tutorialspoint.com/cprogramming/c_unions.htm). The flag signals the padding function that the padding is complete. Essentially, it runs until an enum value “finished” is returned which signifies message block is 512 bits. 

This week I also continued with the MD5 implementation in the main.c class. From the steps defined in the MD5 documentation I implemented the auxiliary functions shown below using what I had learnt about bitwise operations in C a few weeks ago [(MD5 Documentation)](https://tools.ietf.org/html/rfc1321). 

* F(X,Y,Z) = XY v not(X) Z
* G(X,Y,Z) = XZ v Y not(Z)
* H(X,Y,Z) = X xor Y xor Z
* I(X,Y,Z) = Y xor (X v not(Z))

I also added the initial hash values which are fed into the algorithm at the start and modified by each of the various steps, which I will look at in the coming weeks. The initial four values are as follows (0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476). These are in big endian format but are supplied in little endian in the documentation, which is a requirement for the algorithm. I also did some more research into little and big endian to get a better understanding [(Endianness)]( https://en.wikipedia.org/wiki/Endianness).

#### Week of 1-3-20 to 8-3-20
This week I completed and tested the Sha256 algorithm coded from the videos supplied. I began by added the steps to hash the message outline in the documentation. These steps involve the auxiliary functions (Ch, Maj and SHR) implemented previously to shift the bits accordingly. The next step was to add byte swapping (Little to big endian or vice versa) to ensure the bits are in the correct order for the machine [(Endianness)]( https://en.wikipedia.org/wiki/Endianness). Some test code was added to swap the bits manually, but an import was used to do this more efficiently in the algorithm “#include<byteswap.h>”. Coding the Sha256 was a great learning experience and will help me finish my MD5 implementation in a number of ways.

For the MD5 algorithm I added a rotate bits function (ROTL) and union block this week. ROTL shifts the bits n number of times to the left, this loops around so bits that are push off to the left are pushed in on the right again.

#### Week of 8-3-20 to 15-3-20
This week I continued implementing the MD5 algorithm. I started by refactoring main method to allow parameter file reading so when you “run ./main empty” it reads in the empty file in the directory. This will speed up testing time rather than having to enter the file path in the UI which I developed earlier. However, I will still use this feature in the final build along with the ability to input your own message to hash. I also set up the main function to include a loop to run through the input block by block until it is padded. With this loop I created a separate padding method which takes influence from the sha256 padding, I have refactored it however with my own implementation and added a switch statement to tidy the code. With this implemented and fully tested to ensure correctness I began working on the steps defined in section 3.4 of the [MD5 Documentation](https://tools.ietf.org/html/rfc1321) to add the hashing. Included in this section is 64 steps which all have a formula for each round. E.g. a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). I added each step according to the documentation, but the code is quite long and from initial thoughts it seems a loop could be used to cut down this, which is something I will look at later. Another improvement I made was making the auxiliary functions inline, so the overhead is decreased especially as these methods are called 64 times on each iteration. With this added the full system was implemented but from testing the results were incorrect so I needed to do some more debugging.

#### Week of 15-3-20 to 22-3-20
After some more testing I realised the problem was due to the byte swapping I was doing, I was using big endian initial hash values, but then swapping the byte order to little endian during the padding. From research of the documentation and example provided it seems that the MD5 hashing must be done in big endian. [(MD5 Documentation)](https://tools.ietf.org/html/rfc1321). With this removed the result was correct however it was in the wrong order, so I added a loop which I adapted from StackOverflow to swap the byte order to little endian at end of the process [(Swap to Little endian)](https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem). I will later add a check depending on the machine run on, but this now works on my machine which is little endian.

#### Week of 22-3-20 to 29-3-20
This week I continued working on the MD5 implementation. The program as is could take a file in a parameter and return the hash value of that file. I wanted to be able to also take in a string from the user and hash that, so I began implementing this. From research I found that reading bytes from a string can be done by getting the length using strlength() [(strlength)]( https://www.programiz.com/c-programming/library-function/string.h/strlen) and then looping through each byte and copy it to M.eight[i] [(Bytes from string)](https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx). This is slightly different when reading in the bytes of a file and can be done in one step using fread and passing in the value of M.eight. To distinguish between the two ways, I added a 1 or 0 input into the method which is called by the menu system. There is now three ways to run the program. Firstly there is a quick way by running ./main <filename> which will instantly hash the file. Another way is to run ./main which displays a menu and gives the user two options (read from string or file).

#### Final week
On the final week I worked on getting the project ready for submission, adding final documentation and more comments. Another thing I looked at was optimising the code. One area where I focused on was improving the hashing method and removing the number of lines it took. My initial version had 64 function calls to hash each block, there isn’t a way to cut down the number of functions calls but as it’s a similar code I felt a loop could be developed to clean it up. I took what I already had and started testing different ideas. I needed a way to get the message value index which is certain multiples for each round. E.g. In round 2 it goes 1, 6, 11, 0, 5, 10 etc. I implemented some simple logic adapted from MD5 pseudocode which solved this [(MD5 Pseudocode)](https://en.wikipedia.org/wiki/MD5). With this worked I needed to change my inline transform functions. I modified them to create one single inline function that would work for all rounds. The last step was to work out how to send a b c and d into this function as for every four iterations the values need to be shifted right once. To achieve this, I added a series of modulus statements such as i % 4 == 0, I % 4 == 1 etc. This cut down the code significantly and improved the code readability. I also made improvements to where the bytes where read in removing it from the padding and into the startMD5 function. This cleaned up the padding functions and it’s parameters.
 
#### Conclusion
Overall, I am very happy with how the project turned out, and it has been an extremely good learning experience. It was interesting working on a lower level than usual, which is something that will help me in my career. I have also learned a lot more about C, the compiler, little/big endian, bytes/bits and hashing algorithms amongst others.

## References 
All references are found in this README or code in respective areas.

**Project Research**
* VI tutorials - https://www.guru99.com/the-vi-editor.html
https://www.youtube.com/watch?v=HMpB28l1sLc
* Bits and bytes - https://web.stanford.edu/class/cs101/bits-bytes.html
* Bitwise operators in C - https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
* Sha256 algorithm - https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf
* C datatypes - https://www.tutorialspoint.com/cprogramming/c_data_types.htm
* stdint.h - http://www.cplusplus.com/reference/cstdint/
* Unions - https://www.tutorialspoint.com/cprogramming/c_unions.htm
* MD5 Documentation - https://tools.ietf.org/html/rfc1321
* Endianness - https://en.wikipedia.org/wiki/Endianness
* Big Endian to Little Endian - https://stackoverflow.com/questions/4169424/little-endian-big-endian-problem
* strlength - https://www.programiz.com/c-programming/library-function/string.h/strlen
* Bytes from string - https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
* MD5 Pseudocode - https://en.wikipedia.org/wiki/MD5
* SHA 256 algorithm provided by lecturer: https://github.com/ianmcloughlin/sha256

