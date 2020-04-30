## Introduction
This repository contains a full implementation of the MD5 algorithm written in C. This version is written to be as user friendly as possible and contains functionality for hashing both strings and files. Full command line parameters, a menu UI and testing are also implemented which will be described in detail in the “Run” section.

#### What is MD5 algorithm?
MD5 is a hashing algorithm that takes an input of any length and produces a 128-bit (4 x 32bit values) output or “message digest”[10]. The MD5 algorithm is an extension of the MD4 message-digest algorithm and is slightly slower but more secure. However, the MD5 algorithm has been exploited and broken, so it is not advised for encryption purposes. It is still suitable for determining the partition for a key in a partitioned database or a checksum, but not for crucial information such as a password or payment details [11]. More information on its complexities and a review of some of these efforts of exploitations can be found in the “Complexity section”.

#### Repository
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
To compile an executable version of the application you will need a compiler and some additional packages. If on Linux, you can install GCC (GNU Compiler Collection). Also, you will also need to install libssl-dev, which contains development libraries and header files needed to import OpenSSL [12]. **OpenSSL is only used to compare and test the results of the algorithm when `--test/-t` is run.** 
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
Command parameter that handles string input. To use this command enter `./main --string ‘Sample String`.  ‘-s’ can also be used instead of `--string`. Brackets around the string are only required for string longer than one word. This will read the string you have specified and returned the hash result to the user. ‘Sample String’ is the string that will be hashed. This string is required and will display an error if not present. 

### Additional Parameters (Optional)
#### --version/-v
This command can be added to the end of any input, and can be run on its own with `./main --version` or `./main -v`. It displays the current version of the application along with information about how to contact the developer.
#### --help/-h
This command can be added to the end of any input, and can be run on its own with `./main --help` or `./main -h`. It displays useful information about how to run the application.
#### --print/-p
This command parameter must be added along with the `--file/-f` or `--string/-s`. It allows the user to print the hash result returned to a file for later use. Presented is a menu with options 1 or 2. (1 = Yes and 2 = No). If yes is selected the user is given the option to enter a file name. This must include the file extension such as `.txt`. This file will be written to the current directory if just the file name is supplied. However, if `Test/Test.txt` is included it will be written to the folder `Test` in the current directory.
#### --running/-r
This command parameter must be added along with the `--file/-f` or `--string/-s`. It displays the running time of the hashing algorithm on a given string or file.
#### --test/-t
This command can be added to the end of any input, and can be run on its own with `./main --test` or `./main -t`. If it is with other parameters tests are run on the result to ensure it is correct, by using the OpenSSL MD5 standard import [12]. If it is present on its own tests are run against predefined results from the MD5 documentation. More information on how testing is implemented can be found below in the “Test” section. 

### Run with UI
To run the full program with a UI, enter “./main” and a menu will be presented with options 1, 2, 3 or 0 which are described below. This menu will loop until 0 (Exit) is entered.
* 1 – Allows the user to enter a string to hash. A prompt will be displayed to input a string. Once entered the program will hash the string and return the hash to the user.
* 2 – Allows the user to enter a file to hash. A prompt will be displayed to input a file path to a chosen file E.g “TestCode/test.txt”. Once entered and the file is found the program will hash the file and return the result to the user.
* 3 – Allows the user to run a series of predefined tests and compare the results using the OpenSSL standard [12]. The same tests are run when entering `./main --test`.
* 0 – Exit the program.
The menu UI contains all the customisable parameters described above automatically after each hash result is returned. Information such as printing to file, running tests on the hash result, and displaying the running time are automatically displayed.

### Samples
Below are some sample images of the application running and the results returned. The first image is running the application through the command line. The empty string “” is hashed, it is tested with the OpenSSL standard [12] and the clock time is displayed. The second image shows the UI where a file is hashed, and the result is printed to a file. The t

![MD5 Example 1](https://i.imgur.com/ukhAdGT.jpg)

![MD5 Example 2](https://i.imgur.com/q2RqyHX.jpg)

## Test
I lot of testing went into to the development process, as described in the developer diary section of the README. After every new feature or change I made I would run several hashing tests on both files and strings. I would then compare the results with the samples supplied in the MD5 standard. Once I had full testing suites implemented, I would run my results with the testing method I created which sped up the testing process.
In the application I have implemented testing for the user to compare their result with the OpenSSL standard [12]. This can be run two different ways. 
* If `--test/-t` is added to the command line with either `--file/-f` or `--string/-s` the result is compared to the result from the official OpenSSL implementation. As the OpenSSL package can only work with character arrays (strings) I have added code to open a file and read it into a buffer. However, it can only read text files (.txt). 
* If `--test/-t` is present on its own (`./main --test`) tests are run against predefined results from the MD5 standard and displayed to the user, with verification from the OpenSSL standard [12]. These tests are laid out below.
1. ("") = d41d8cd98f00b204e9800998ecf8427e
2. ("a") = 0cc175b9c0f1b6a831c399e269772661
3. ("abc") = 900150983cd24fb0d6963f7d28e17f72
4. ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
5. ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
6. ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") = d174ab98d277d9f5a5611c2c9f419d9f

The below image shows the predefined being run using `./main --test`. `--test` can be also run on specific files or strings as mentioned above. 

![MD5 Example 3](https://i.imgur.com/tfiezo1.jpg)

## Algorithm
As outlined in the MD5 standard documentation there is five steps to perform the algorithm [10]. We will first look at these five steps and then step through the implementation of this algorithm in this repository.

### MD5 Standard Algorithm
#### Step 1: Append Padding Bits
Padding is completed for each message block so that it is congruent to 448 bits, modulo 512 as defined in the MD5 standard [10]. The message is extended to be 64 bits less than 512 bits. Padding is always performed even if the message is 448 bits, a full block of padding will be added after if this occurs. Padding is done by adding a “1” bit followed by any number of “0” bits until the padded message becomes 448 bits. 

#### Step 2: Append Padding Bits
64 bits are then added to complete the message from step 1. These 64 bits are the length of the message before padding bits were added. However, if this length is greater than 2^64, then only the low-order 64 bits are used. In this case the bits are added as two 32-bit words (low-order). The message is now 512 bits, which can be broken down into 16 32-bit words.

#### Step 3: Initialize MD Buffer
Before the hashing takes place an initial four-word buffer must be initialised (A, B, C and D) with the values below (low-order bytes first). These values will be updated and produce the final output.

* Word A: 01 23 45 67
* Word B: 89 ab cd ef
* Word C: fe dc ba 98
* Word D: 76 54 32 10

#### Step 4: Process Message in 16-Word Blocks
This is the most extensive step and contains the actual hashing. Initially four auxiliary functions must be defined which are described below [10]. They are used to modify the bits accordingly and take in three 32-bit words and produce one 32-bit word.
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

### Implementation
We will now step through the implementation in this repository and how the steps above were implemented.
#### Padding and appending bits (Steps 1 & 2)
Initially the message (file or string) in bytes is passed into the padding function. This is run in a while loop until the message has been fully padded (status returns FINISH). On each iteration the status is checked using a switch statement. The code for the padding was initially developed from the SHA256 algorithm provided by our lecturer but it was modified heavily.
* If the status is DEFAULT first get the length of the initial message which will be appended at the end. The next step is to check if the bytes are less than 56, if so then the message can be padded in one block. A ‘1’ bit is added then a string of ‘0’ bits up till 56 bits. The 64-bit value is then added to complete the padding. This 64-bit value is the length of initial message. If the bytes read is between 56 and 64 then a new block of padding is needed, so it will pad with zeros. Again, add a ‘1’ bit to the start, pad till the end (64 bits) and set status to PAD0 for next iteration. This will add another block of padding after.
* If the status is PAD0 then pad a full block with zeros and append the 64-bit message length to finish the padding and set status to FINISH. 
* If the status is FINISH, then the padding is complete which will return 0 and complete the loop.

#### Initialize MD Buffer (Step 3)
The buffer is initialised at the start of each call of the `startMD5` method, using the values supplied in the documentation. The hexadecimal value ‘0x’ is added also.
```
void initialiseHash(WORD *H) {
  H[0] = 0x67452301;
  H[1] = 0xefcdab89;
  H[2] = 0x98badcfe;
  H[3] = 0x10325476;
}
```

#### Hashing the message (Step 4)
The loop outlined below hashes and pads the message. On each iteration the message is padded to be 512 bits which is passed into the hashBlock mehod. M.thirtytwo is the memory address of the message and H is the hash values to be updated (A, B, C, and D).
```
while (padBlock(&M, infile, str, &nobits, &status, userOption)) {
    // Calculate the next hash value.
    hashBlock(M.thirtytwo, H);
 }
```
Inside the hashBlock method and number of steps are undertaken. 
1. Firstly, the message is copied to a new 32 bit array represented as `W[]`. 
2. The initial hash values or values from previous hash are copied to variable a, b, c, and d.
3. Undertake 4 rounds of 16 transforms, 64 in total using the TRANSFORM method. I initially used one line for each transform, but I modified it to be completed in one loop to make the solution easier to understand. This took a lot of trial and error and testing to achieve due to the amount of values being changed and passed around. On each iteration of the inner loop the round number is set along with the message value to pass into the TRANSFORM. The maths to compute the messageIndex was adapted from MD5 Pseudocode []. If `i <16` then it is round 1, if  `i < 32` then it is round 2, and so on.
``` 
if (i < 16) {
      messageIndex = i;
      round = 1;
}
```
This round number is then passed into the TRANSFORM function which is shown below. I have developed one function that performs all round transform in one simple to understand inline function. The specific auxiliary function is used for each round and the result is calculated. The bits are also shifted left `s` number of positions using the `ROTL` function.
```
// a, b, c, d – initial hash values.
// m – message.
// s – number of positions to shift left by.
// t – 1 of 64 hash values defined in standard.
// r = round number (1-4).
// F(b,c,d) - 1 of 4 auxiliary functions.
#define TRANSFORM(a, b, c, d, m, s, t, r) \
{                                       			\
   if (r == 1)                           		\
      a += F(b, c, d) + m + t;            		\
   else if (r == 2)                      		\
      a += G(b, c, d) + m + t;            		\
   else if (r == 3)                      		\
      a += H(b, c, d) + m + t;           		\
   else if (r == 4)                      		\
      a += I(b, c, d) + m + t;           	 	\
   a = b + ROTL(a, s);                   		\
}
```
5. Once all transforms are applied append initial hash copies onto H[].

#### Output
When the message is hashed it is in big endian byte order, an initial check is done to check the architecture of the system. If it is a little-endian machine the results are converted. If the machine is big endian the result is just printed as the MD5 algorithm is completed using a big-endian byte order.

## Complexity
The MD5 hashing algorithm or message digest is a complex and efficient solution however it is not without its downsides especially regarding security. We will first have a look at what the MD5 algorithm is, the complexities of this algorithm, its uses and then some of its flaws.

#### What is a message digest or hashing algorithm?
A message digest or hashing algorithm is a one-way function [10]. The state of the previous message is lost as part of a transform, and the output is drastically different from the input. The transform involves several steps defined by the algorithm and which usually includes bit shifting and other bit operations.
Cryptographic hashing algorithms are used for number of reasons such as securely encrypting passwords, files, and personal details. They are used to encrypt personal data so they cannot be accessed by hackers or unauthorised users. Because of this it is a necessity that they are unbreakable. I.e. impossible to compute two messages that hash to the same value [7]. 

#### MD5 history
The MD5 algorithm was designed and developed by Ron Rivest in 1991, and it was released and outlined during April 1992 in RFC 1321 [10]. The MD5 algorithm was an improvement upon the MD4 algorithm, improvements included adding a fourth round and updating the auxiliary functions, so they were less symmetrical. It came at the cost of slightly slower running time, but it was more secure. In 1993, 2004, 2006 and 2012 [1][2][3][4][5] successful attempts were made however to exploit its weaknesses and produce a collision. Because of these findings it was deemed an unsecure algorithm for security purposes [11], and it was recommended to use SHA-1 instead at that current time [13]. In recent years unbreakable algorithms like the SHA-256 are recommended for encryption.

#### The complexities of the MD5 algorithm
##### Transforms
This MD5 algorithm is highly complex in several ways. Firstly, it involves a multitude of steps and transforms which can be seen in the algorithms section. These four rounds which include 64 transforms in total are applied to each 512-bit message block and change the message drastically [10]. One transform, bit shift or bit operation performed can change the whole message. Also, in the transform a property called the “avalanche effect” is used [8]. This property changes the output significantly from one small change. For example, if one bit is flipped, half the bits could be flipped. This adds significant efficiency and security to algorithms and is a desirable trait.
##### Padding
Integrity is upheld using padding that each message regardless of the input size will be 512 bits. This allows for efficient implementations as all messages will be the same no matter the input. 
##### Output 
The algorithm produces a 128-bit output or 4 x 32bits. This provides 2^128 possible different hashes [10], which equates to 340,282,366,920,938,463,463,374,607,431,768,211,456 possible outcomes. Even though two messages could randomly hash to the same value it is very unlikely. However even with its complexities unfortunately for the MD5 algorithm there have been number of successful attempts to engineer this scenario. We will look at this in detail along with some other methods of breaking hashes.
##### Big O
The Big O time complexity of the algorithm is O(N) and runs a total of 8\*n/512 times, with 'n' being the number of bytes in the message. If a message were 1000 bytes, it would run 16 times, as the last block would be padded to complete the 512-bit message. The running time is directly proportional to the input size. There are also no inner loops, just 64 predefined transforms on each iteration. 
##### Running Time
The running time of the MD5 algorithm is considerably fast due to its low number of transforms in comparison to other algorithms [13]. In my tests of the algorithm, it could be seen to take an average of 9.1 seconds to hash a file 1GB in size. This file was generated using `fallocate -l 1G test.img`. However, as the speed of this algorithm is largely dependent on the computer hardware used this could vary between different machines. For these tests it was run on a Linux Debian 10 (buster) Google Cloud Virtual Machine. Below is an outline of the tests mentioned above.

| Attempt | Running time (s) |
| ------- | ---------------- |
| 1       | 9.178970         |
| 2       | 9.135272         |
| 3       | 9.110160         |
| 4       | 9.151310         |
| 5       | 9.120555         |

#### How can the MD5 algorithm be reversed?
Essentially a message digest is irreversible due to its nature. A hash algorithm is a one-way function and the initial state is lost and is transformed into a final output as mentioned above. A simple analogy for this is if you have a cow, then you convert it into a steak, would you be able to make it into a cow again? The answer is no, and hashing algorithms work in the same way.  However, hashing functions can be broken, or collisions can be found which we will now look at [7].
##### Collisions
A collision is referred to as two different messages that hash to the same value. E.g. `hash(m1) == hash(m2)` [7]. Finding a reproducible collision does not mean that a hash can be reversed, but it does allow attackers to be able to control or insert a malicious code if they have control over both files. The first of these files is the original and the second is the fake file containing malicious intent. This fake file hashes to the same value as the real file to trick the system or user [6]. This will be the focus as there has been several successful attempts at creating two different inputs that output to the same hash value using the MD5 algorithm.
##### Brute Force/Pre-image attack
A way to break a hashing algorithm is by brute force or a pre-image attack [7]. This involves trying every possible option until the same hash is found. If trying to break a password (strings), the number of iterations and time required can depend on the input size E.g the password or file size. For example, a 10-character password of just numbers is a lot easier to break compared to a 32-character password containing alphanumeric values. For other items such as large files it can take considerably more time, as the MD5 produces a 128-bit output message so essentially it would require 2^128 iterations to break [10]. This is an extremely large number as described in the complexities section. However, a point to note is with the laws of probability it could take half that time as you could find the hash value early. At the time Sha-1 was recommended to be used instead, despite it being slower than MD5. The SHA-1 takes 2^160 iterations to break with brute force [13]. This algorithm paved the way for improvements which have been implemented in the likes of the SHA-256 and SHA-512 algorithms which are currently unbreakable. The computing power to break a 2^256 number is physically impossible in today's world and would take years to break.

##### Other methods
There are various other ways of, however they do not constitute reversing the algorithm but instead exploit data already compiled and compare it to find the same hashing output. One example of this is using a simple lookup table [7]. This is a collection of precompiled hashes of the most common passwords and words, that can be used to compare against. As majority of users use a very simple of common password a password hash can be broken in seconds if it not salted. A salt is an additional hash value appending the start or end of the password to increase its security.

#### Attempts at breaking MD5 using collisions.
Since the MD5 algorithm was published in 1992 there has been several successful attempts to produce a collision between two messages. The first attempted occurred in 1993 by Bert den Boerand A. Bosselaers [1]. Their attempt was not a full attack on the MD5 but a pseudo collision. A pseudo collision is when the four-word buffer is initialised with two different values, which are only different in the most significant bit (MSB) for each word [1]. With two different messages the same output will be produced. An example of this can be seen below which is outlined in [1]. As you can see the two input buffers are only different by the MSB but hash to the same value.

* **Message 1:** 5FFBB485 B73256D8 19DF08E4 11054166 22COOE98 450A05C4 5F53A940 9DDCICF8
* **Message2:** DADABBDB 8A43597A 4CA51993 E7DBi2E5 lFlC0317 9A3BAAD6 B275B7BB OP09CFD5
* **Input Buffer 1:** 399349134 87609442 F7DFE793 83D49001
* **Input Buffer 2:** B99E49D4 07669442 77DFE793 03D49001
* **Output:** P80668D5 P8AB5C93 C93998F5 D007A636

The most fruitful and impactful attempt was in 2004 by Xiaoyun Wang and Hongbo Yu [2]. They used a differential attack that uses modular integer subtraction as a measure (−1, 0 or +1). Their method consists of two 512-bit message blocks. The first block could be found within an average of 15 minutes to 1 hour with a time complexity of 2^39. The second block could be found within 15 seconds to 5 minutes with a complexity of 2^32. These results were computed using an IBM P690 computer, however with today’s technology the times mentioned above would be mere seconds [2]. 

Outlined in the document is several conditions for the characteristics of the algorithm to hold. These are denoted as zero and non-zero conditions. Also, two modifications techniques are specified which are used to fix some of the message words prior to the steps for the conditions to hold. These are described as Single-message (SM) and Multi-message (MM) Modification [2]. Lastly, outlined is a basic description of the algorithm and how it works [2].

1. Repeat the following steps until a first block is found.
* (a) Select a random message M0.
* (b) Modify M0 by the message modification techniques (SM & MM).
* (c) Then, M0 and M = M0 + ∆M0 to produce the first iteration differential. (∆ is the bit difference produced).
* (d) Test if all the characteristics really hold by applying the compression function on M0 and M.
2. Repeat the following steps until a collision is found
* (a) Select a random message M1.
* (b) Modify M1 by the message modification techniques (SM & MM).
* (c) Then, M1 and M1 + ∆M1 generate the second iteration differential.
* (d) Test if this pair of messages lead to a collision.

With this attack two messages M and M0 can hash to the same value with only a difference in two blocks. This same attack can also be used to find collisions in HAVAL-128, MD4, RIPEMD, and SHA-0 efficiently [2]. A year later the same authors released another paper which attempted a very similar method to break the SHA-1 algorithm. This was the recommend hashing algorithm at the time [13].

Over the next couple of years there were several attempts to improve the speed to find a collision. For example, an attempt in 2016 by Vlastimil Klima could produce a collision in one minute on a standard notebook PC [3]. This algorithm used tunnelling. Conditions are placed on the initial values much like the example seen in [2]. Tunnels are transformations on the message that does not change these conditions [3]. Another fast attempt occurred in 2006 by Marc Stevens [4]. The algorithm instead worked by controlling rotations in the first of four rounds. Again, similar to Klima’s algorithm it can be completed within an average of one minute with a time complexity of 2^32. Marc Stevens later again in 2012 implemented an attack on a single 512-bit message block in response to a competition [5]. Other collision attempts as mention above used multiple blocks [2][3][4]. 

#### Practical collision situation
Collisions do not make a hashing algorithm reversible as it is still very hard to find the initial state of a file if the original file is unknown. The only way this can be done is using a preimage attack as outlined above. However, collisions do deem the MD5 algorithm unsafe and we will now look at a practical application of this. In March 2005 Xiaoyun Wang, Arjen Lenstra, and Benne de Weger outlined a successful proof of concept to issue a fake digital certificate [6]. This would allow them to impersonate any website using HTTPS protocol with MD5’s weaknesses.

#### Complexity Conclusion
To conclude from my deep research of the algorithm itself MD5 is a complex and very efficient algorithm. However due to its weaknesses seen in the multiple attempts to break the algorithm [1][2][3][4][5], ultimately it has caused the death of said algorithm for cryptographic purposes [11]. There is some light however as it still can be used for tasks that do not involve personal information.

## Conclusion
Overall, I am very happy with how the project turned out, and it has been an extremely good learning experience. It was interesting working on a lower level than usual, which is something that will help me in my career. I have also learned a lot more about C, the compiler, little/big endian, bytes/bits and the MD5 hashing algorithm amongst others.

## References
Below is a collection of references used to write and research this document and why I chose them. Other references used in the development process of the project can be found in references section of the README.

This is one of the first attempts at finding a collision in the MD5 algorithm. I have included this as it gave me valuable insight into how this pseudo collision can occur.
* **1. Den Boer, B. and Bosselaers, A., 1993, May. Collisions for the compression function of MD5. In Workshop on the Theory and Application of Cryptographic Techniques (pp. 293-304). Springer, Berlin, Heidelberg.**

This is the earliest and one of the most successful attempts at finding a collision for the MD5 algorithm and others. I have included it as it deemed the MD5 algorithm unsafe for collision related hashing or security purpose. I have also described how this algorithm is implemented in the complexity section. It also led to faster collisions been found in later algorithms.
* **2. Wang, X. and Yu, H., 2005, May. How to break MD5 and other hash functions. In Annual international conference on the theory and applications of cryptographic techniques (pp. 19-35). Springer, Berlin, Heidelberg.**

Another very fast attempt to find a collision, which could be found within one minute on a standard PC. This algorithm using tunnelling which was interesting to learn about.
* **3. Klima, V., 2006. Tunnels in Hash Functions: MD5 Collisions Within a Minute. IACR Cryptology ePrint Archive, 2006, p.105.**

One of the fastest attempts with a time complexity of 2^32 to find a collision. This attempt worked by controlling rotations in the first round. It was interesting to learn about all the possible implementations.
* **4. Stevens, M., 2006. Fast Collision Attack on MD5. IACR Cryptology ePrint Archive, 2006, p.104.**

One of the more recent attempts at finding a collision, instead however using one single 512bit block to achieve it compared to two blocks used in other solutions.
* **5. Stevens, M., 2012. Single-block collision attack on MD5. IACR Cryptology ePrint Archive, 2012, p.40.**

A practical implementation of how collisions could be used for malicious intent. This really helped me understand the effects and dangers of the algorithm.
* **6. Lenstra, A.K., Wang, X. and de Weger, B.M.M., 2005. Colliding X. 509 certificates (No. REP_WORK).**

I have included this paper as it gave me a better understanding of a collision and pre-image attack on a hashing algorithm.
* **7. Andreeva, E. and Stam, M., 2011, December. The symbiosis between collision and preimage resistance. In IMA International Conference on Cryptography and Coding (pp. 152-171). Springer, Berlin, Heidelberg.**

A description of the avalanche effect by Horst Feistel. I have included this as its one of the properties used in the MD5 algorithm and was one of its weakness regarding the most significant bit.
* **8. https://www.apprendre-en-ligne.net/crypto/bibliotheque/feistel/index.html**

Wikipedia page for the MD5 algorithm. I did not use any information from this to generate my sources, but it was a good base to start my research into other areas looked at in this document.
* **9. https://en.wikipedia.org/wiki/MD5**

Original RFC 1321 released in April 1992 which outlines the MD5 algorithm and a sample solution. I have included this reference as it was the main research point for development my own implementation of the algorithm and finding out more information about how it works. 
* **10. https://tools.ietf.org/html/rfc1321**

Updated security considerations for RFC 1321, released in March 2011. I have included this as it is an official statement of the acknowledgements of the successful collision attacks performed
* **11. https://tools.ietf.org/html/rfc6151**

The OpenSSL standard, which provides a tested implementation of the MD5 algorithm. This has solely been added for the testing section of the module. It is used to compare the users hash against if –test/-t is applied.
* **12. https://www.openssl.org/source/**

Original RFC for the SHA-1 algorithm, I have included this as it was used as a comparison algorithm to MD5 and was recommended instead of MD5 at the time.
* **13. https://tools.ietf.org/html/rfc3174**

