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
