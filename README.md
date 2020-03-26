# Theory of Algorithms Project 

Name: Matthew Sloyan
Student ID: G00348036

# Project statement
You must write a program in the C programming language [2] that calculates the MD5 hash digest of an input. The algorithm is specified in the Request For Comments 1321 document supplied by the Internet Engineering Task Force [5]. The only pre-requisite is that your program performs the algorithm — you are free to decide what input the algorithm should be performed on. I suggest you allow the user to input some free text or a filename via the command line.

# Platforms
Coded and tested on a Linux Debian 10 (buster) Google Cloud Virtual Machine. All code was written in VI and compiled by connecting to the VM using SSH.

# How to run program
* First, clone the repository using the following command `git clone https://github.com/MatthewSloyan/MD5-message-digest-algorithmt` 
* Traverse using the command line to the folder you have cloned using the cd command.
* Compile main.c file to execute using gcc -o main main.c
* Execute file using ./main

# User Guide
Below you’ll find a basic guide to the user interface, in the “How it works” section is a description of how this works in the code behind.

* You will be presented with a menu..

# How it works
More information on each of these steps above can be found in the Research & Development Diary section below.

# Project Plan
* Week 1 - Initial research and setup.
* Week 2 - Setup Google Cloud VM and learn VI.
* Week 3 - Write basic menu and file writing functions.
* Week 4 - Start to implement the MD5 algorithm.
* Week 5 - Continue implementation.
* Week 6 - Continue implementation.
* Week 7 - Improve and test implementation.
* Week 8 - Adding finishing touches, tidying up code, and adding extras.

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



#### Conclusion 

## References 
All references are also in code in respective areas.

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

