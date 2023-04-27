# Super sort
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/c/language)

## Task

- To implement the "sorting" function `tarant_allegra(H, P, M)`, follow these guidelines:
  - **H**
    - integer
    - id of input file which contains numbers that need to be sorted
    - you can read from H only sequentially
    - file can not be deleted
  - **P**
    - integer
    - id of output file
    - save sorted H into P
    - you can only sequentially write to P
  - **M**
    - size (in bytes) of heap memory that can be used.
- H and P are _0 and 1_ or _1 and 0_ (guaranteed)
- Use the prepared API called "flib" for working with files.
- You can use many temporary files, but each file has an ID of int32_t, which limits the number of files.
- The total size of all files cannot exceed 2 times the size of the input file.
- Do not use the STL library.
- Each file can only be opened once at the same time, either for reading or writing.
- Reading or writing starts from the first bit, and jumping through the file is not allowed.
- A file can only be deleted if it is not opened.
- Every opened file takes up 12 bytes on the heap.

- ## Program will be tested on:
  - base tests:
    - input contains $10 \le N \le 1000$ numbers of `int32_t`
    - heap size 2000 bytes
    - stack size 1000 bytes
  - local memory tests:
    - input contains $10 \le N \le 3 000 000$ numbers of `int32_t`
    - heap size 20 000 000 bytes
    - stack size 4000 bytes
  - efficiency tests:
    - input contains $10 \le N \le 3 000 000$ numbers of `int32_t`
    - heap size 2000 bytes
    - stack size 4000 bytes
  - all inputs will be correct!

## Solution:
- My program reads an input file in small chunks and saves each chunk sorted into a temporary file.
- Then, I merge the temporary files like a tree - for example, $N$ files merge into $N/2$ files, then into $N/4$ files until $N$ equals $1$.

## Installation

### Software requirements
- g++ compiler

### How to run
- Clone the repository
  ```bash
  git clone https://github.com/janbabak/SuperSort.git
  ```
- Enter the cloned folder
  ```bash
  cd SuperSort
  ```
- Compile the source codes
  ```bash
  g++ main.cpp flib.h flib.cpp -o superSort
  ```
- Run the compiled binary
  ```bash
  ./superSort
  ```
