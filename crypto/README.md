# **Blockchain - Crypto**

## **Learning Objectives**

<i>At the end of this project, you are expected to be able to explain to anyone, without the help of Google:</i>

- How a Blockchain is considered “unbreakable”
- What is a hash algorithm
- What SHA stands for
- How hash algorithms apply to Blockchains
- What is asymmetric cryptography
- How asymmetric cryptography applies to cryptocurrencies
- What ECC stands for
- What ECDSA stands for
- What a digital signature is
- How digital signatures apply to cryptocurrencies

## **General requirements**

- Forbidden editors: vi, vim, emacs
- Allowed ones: Visual Studio Code
- All your files will be compiled on Ubuntu 14.04 LTS (:worried:)
- Your C programs and functions will be compiled with gcc 4.8.4 using the flags **-Wall -Werror -Wextra, -pedantic** and the **linker flags -lssl and -lcrypto**
- All your files should end with a new line
- A README.md file, at the root of the folder of the project, is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- The prototypes of all your functions should be included in your header file called **crypto/hblk_crypto.h**
- All your header files should be include guarded

## **Dependencies**

For this project , the OpenSSL library need to be installed.

## **Additional Informations**

- Unless specified otherwise, open-bar on the C standard library
- You are free to use any data structure that suits you as long as their purpose is well defined
- You are free to print any information on stderr, this stream will be discarded during correction. Since you are going to use these utility functions in your Blockchain project, you are free to manage errors as you wish.
- At the end of this project, the structure of your repository should look like this (you may have additional files):

```
holbertonschool-blockchain
├── crypto
│   ├── ec_create.c
│   ├── ec_from_pub.c
│   ├── ec_load.c
│   ├── ec_save.c
│   ├── ec_sign.c
│   ├── ec_to_pub.c
│   ├── ec_verify.c
│   ├── hblk_crypto.h
│   ├── libhblk_crypto.a
│   ├── Makefile
│   ├── provided
│   │   └── _print_hex_buffer.c
│   ├── sha256.c
│   └── test
│       ├── ec_create-main.c
│       ├── ec_from_pub-main.c
│       ├── ec_load-main.c
│       ├── ec_save-main.c
│       ├── ec_sign-main.c
│       ├── ec_to_pub-main.c
│       ├── ec_verify-main.c
│       └── sha256-main.c
└── README.md
```
