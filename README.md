# Image_LSB_steganography

Description:

This project implements Image Steganography using the Least Significant Bit (LSB) mechanism in C language. It allows users to hide secret text messages within a BMP image by altering the least significant bits of pixel data. The hidden information is retrievable only with a secret key shared between the sender and receiver. The project provides an excellent opportunity to understand the low-level working of image files, binary manipulation, and data security using simple steganographic principles.

Technology Used:

Programming Language: C

Key Concepts:
    
    1.Bitwise Operators
    
    2.File I/O
    
    3.Functions & Pointers
    
    4.Command Line Arguments (CLA)

Platform: Console-based (Standard I/O)

Features:

  🔒 Data Hiding in Images: Embeds secret data (e.g., text) into a 24-bit BMP image.

  🔑 Key-Based Access: Both encoding and decoding require a matching secret key.
  
  📁 File I/O Operations: Reads and writes BMP images and text files.
  
  🧠 Bitwise Manipulation: Uses LSB of each byte in pixel data for embedding.
  
  🛠️ Modular Code Design: Clean function-based approach with proper abstraction.
  
  📦 Command Line Interface: Easy-to-use CLI with flags for encoding and decoding.

Process Flow:

Secret data(in text)---->Encoding---->Stego image---->Decoding
                            |                            |
                       original image                Secret data

Compiling multiple files: gcc *.c

Running command for encoding: ./a.out -e beautiful.bmp secret.txt

Running command for decoding: ./a.out -d decode_data.txt stego.bmp

Note:

Flowcharts for both encoding and decoding logic are provided in the repository.

A sample BMP image is also included in repository.

Learning Outcomes:

  File structure and manipulation at binary level.

  Bitwise logic for encoding/decoding.
  
  Function pointer usage in modular programs.
  
  CLI-based file and argument management.
  
  Intro to steganography and digital image manipulation.






