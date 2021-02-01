# Super sort

### task:

- implement **sorting** function _tarant_allegra(H, P, M)_, where H, P, M are numbers
  - **H**
    - id of input file
    - contains numbers, which need to be sorted
    - you can only sequentially read from H
    - can not be deleted
  - **P**
    - id of output file
    - save sorted H into P
    - you can only sequentially write to P
  - **M - size of heap (memory) in bytes, which can be used**
- H and P are _0 and 1_ or _1 and 0_ (quaranteed)
- you can use prepared api for working with files (called flib)
- you can use many temporary files
- all files has id of _int32_t_ - limeted number of files
- size of all files can not exceed 2 \* size of input file
- STL library is not allowed
- every file can be in same time opened only once - for reading only or writting only
- reading or writting begins from the first bit and you can not jump through file
- file can be deleted only if it is not opened
- overy opened file takes 12 bytes on heap

- ### program will be tested on:
  - base tests:
    - input contains 10 <= N <= 1000 numbers of int32_t
    - heap size 2000 bytes
    - stack size 1000 bytes
  - local memory tests:
    - input contains 10 <= N <= 3 000 000 numbers of int32_t
    - heap size 20 000 000 bytes
    - stack size 4000 bytes
  - efficiency tests:
    - input contains 10 <= N <= 3 000 000 numbers of int32_t
    - heap size 2000 bytes
    - stack size 4000 bytes
  - all inputs will be correct!

### Solution:

- My program reads input file by small chunks and save every chunk sorted into temporary file.
- Then I merge temporary files like tree - eg. N files merge into N/2 files, them into N/4 files until N = 1

### How to run on linux:

- required g++ or any other C++ compiler
- compile al files using this command `g++ main.cpp flib.h flib.cpp -o superSort`
- run program using `./superSort`
