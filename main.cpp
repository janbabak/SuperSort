#ifndef __PROGTEST__
#include "flib.h"
#endif //__PROGTEST__

//Max heap - with heap sort implemented
class MaxHeap {
private:
    int32_t * data;  //MaxHeap is stored in array
    int32_t size;
    int32_t allocatedSize;

public:

    /** constructor - make MaxHeap from array
     * @param arr 
     * @param arrSize 
     * @source https://www.educative.io/edpresso/how-to-build-a-MaxHeap-from-an-array
     */
    MaxHeap(int32_t * arr, int32_t arrSize, int32_t allocSize)
        : size (arrSize), allocatedSize (allocSize)  {
        data = arr;
         
        for (int32_t i = size; i >= 0; --i) {
            heapify(data, size, i); 
        }
    }

    void heapify(int32_t * arr, int32_t arrSize, int32_t parent) {

        int32_t biggest = parent;
        int32_t leftChild = 2 * parent + 1;
        int32_t rightChild = 2 * parent + 2;

        if (leftChild < arrSize && arr[leftChild] > arr[biggest]) 
            biggest = leftChild; 

        if (rightChild < arrSize && arr[rightChild] > arr[biggest]) 
            biggest = rightChild; 

        //parent is not biggest => swap arr[smallest] and arr[parent]
        if (biggest != parent) { 
            int32_t tmp = arr[biggest];
            arr[biggest] = arr[parent];
            arr[parent] = tmp;

            // Recursively MaxHeapify the affected subtree 
            heapify(arr, arrSize, biggest); 
        }
    }

    //data getter
    int32_t * getData() {
        return data;
    }

    //MaxHeap sort - make sorted array from MaxHeap
    void heapSort() {    
        int32_t i = 1;
        while (i  < size) {
            //swap root and last unsorted element
            int32_t tmp = data[0];
            data[0] = data[size - i];
            data[size - i] = tmp;

            //MaxHeapify only unsorted part of array
            heapify(data, size - i, 0);

            i++;
        }
    }
};

//merge two files into one
void mergeFiles(int32_t inFile1, int32_t inFile2, int32_t outFile, int32_t memory) {
    //init memory
    int32_t arrSize = memory / 3;
    int32_t * arr1 = new int32_t [arrSize]; //array will be filled from inFile1
    int32_t * arr2 = new int32_t [arrSize]; //array will be filled from inFile2
    int32_t * arr3 = new int32_t [arrSize]; //arr1 and arr2 will be merged into arr3

    flib_open(inFile1, READ);
    flib_open(inFile2, READ);
    flib_open(outFile, WRITE);

    int32_t readFrom1 = 0; //count of numbers readed from file 1
    int32_t readFrom2 = 0; //count of numbers readed from file 2
    int32_t ptr1 = 0; //point to element which should be readed in arr1
    int32_t ptr2 = 0; //point to element which should be readed in arr2
    int32_t ptr3 = 0; //point to place where should be written next element in arr3
    //read from files while data left
    while(true) {
        if (ptr1 == readFrom1) {
            readFrom1 = flib_read(inFile1, arr1, arrSize);
            ptr1 = 0;
        }
        if (ptr2 == readFrom2) {
            readFrom2 = flib_read(inFile2, arr2, arrSize);
            ptr2 = 0;
        }
        if (readFrom1 == 0 || readFrom2 == 0)
            break;
        //merge arrays while in arr1 and arr2 left numbers to merge
        while(ptr1 < readFrom1 && ptr2 < readFrom2) {
            //arr3 is full => need to be saved in out file
            if (ptr3 == arrSize) {
                flib_write(outFile, arr3, arrSize);
                ptr3 = 0;
            }
            if (arr1[ptr1] < arr2[ptr2]) {
                arr3[ptr3] = arr1[ptr1];
                ptr1++;
            } else {
                arr3[ptr3] = arr2[ptr2];
                ptr2++;
            }
            ptr3++;
        }
        
    }
    //write rest of arr3
    if (ptr3 != 0 ) {
        flib_write(outFile, arr3, ptr3);
        ptr3 = 0;
    }
    //if one file is not read entirely => read it and write it to out file
    if (readFrom1 > 0) {
        flib_write(outFile, arr1 + ptr1, readFrom1 - ptr1); //write rest of arr1 to out file
        //write rest of inFile1
        while (readFrom1 > 0) {
            readFrom1 = flib_read(inFile1, arr1, arrSize);
            flib_write(outFile, arr1, readFrom1);
        }
    } else if (readFrom2 > 0) {
        flib_write(outFile, arr2 + ptr2, readFrom2 - ptr2); //write rest of arr2 to out file
        //write rest of inFile2
        while (readFrom2 > 0) {
            readFrom2 = flib_read(inFile2, arr2, arrSize);
            flib_write(outFile, arr2, readFrom2);
        }
    }

    //free memory
    flib_close(inFile1);
    flib_close(inFile2);
    flib_close(outFile);

    flib_remove(inFile1);
    flib_remove(inFile2);

    delete [] arr1;
    delete [] arr2;
    delete [] arr3;

}

void tarant_allegra ( int32_t in_file, int32_t out_file, int32_t bytes ){
    
    int64_t numsReaded;
    int32_t numberCount = 3000000;
    int32_t buferSize = bytes / 5 - 10;
    int32_t * bufer = new int32_t [buferSize];
    int16_t tmpFilesCount = (numberCount / buferSize) + 1;  //reserve file

    //read blocks of in_file and save each block sorted in separate tmp file
    flib_open(in_file, READ);
    int16_t i;
    for (i = 2; i <= tmpFilesCount + 1; ++i) {  //i = 0 and i = 1 are reserved for in and out file
        numsReaded = flib_read(in_file, bufer, buferSize);
        if (numsReaded < 1) {  
            break;
        }
        MaxHeap heap(bufer, numsReaded, buferSize);        
        heap.heapSort();
        flib_open(i, WRITE);
        flib_write(i, bufer, numsReaded);
        flib_close(i);
    }
    i--;
    //there are sorted tmp files: 2, 3, 4,...,i - 1, i in this state
    //file max name is i
    flib_close(in_file);

    //there is only 1 tmp file
    if (i == 2) {
        flib_open(2, READ);
        int32_t readed = flib_read(2, bufer, buferSize);
        flib_close(2);
        flib_remove(2);
        flib_open(out_file, WRITE);
        flib_write(out_file, bufer, readed);
        flib_close(out_file);
        delete [] bufer;
    } else {
        delete [] bufer;
        //merge all files
        int32_t f1 = 2;
        int32_t f2 = 3;
        while(f2 != i) {
            i++;
            mergeFiles(f1, f2, i, buferSize);
            f1 += 2;
            f2 += 2;
        }
        mergeFiles(f1, f2, out_file, buferSize);
    }
}
#ifndef __PROGTEST__

#define SUM_MOD 100000007
uint64_t total_sum_mod;
void create_random(int output, int size){
    total_sum_mod=0;
    flib_open(output, WRITE);
    /* srand(time(NULL)); */
#define STEP 100ll
    int val[STEP];
    for(int i=0; i<size; i+=STEP){
        if(i%STEP==0){
            for(int j=0; j<STEP; ++j){
                val[j]=-1000 + (rand()%(2*1000+1));
                total_sum_mod = (total_sum_mod + val[j]) % SUM_MOD;
            }
        }
        flib_write(output, val, (STEP < size-i) ? STEP : size-i);
    }
    flib_close(output);
}

void tarant_allegra ( int in_file, int out_file, int bytes );

void check_result ( int out_file, int SIZE ){
    flib_open(out_file, READ);
    int q[30], loaded, last=-(1<<30), total=0;
    uint64_t current_sum_mod=0;
    while(loaded = flib_read(out_file, q, 30), loaded != 0){
        total += loaded;
        for(int i=0; i<loaded; ++i){
            if(last > q[i]){
                printf("the result file contains numbers %d and %d on position %d in the wrong order!\n", last, q[i], i-1);
                exit(1);
            }
            last=q[i];
            current_sum_mod = (current_sum_mod + q[i]) % SUM_MOD;
        }
    }
    if(total != SIZE){
        printf("the output contains %d but the input had %d numbers\n", total, SIZE); exit(1);
    }
    if(current_sum_mod != total_sum_mod){
        printf("the output numbers are not the same as the input numbers\n");
        exit(1);
    }
    flib_close(out_file);
}

int main(int argc, char **argv){
   const uint16_t MAX_FILES = 65535;
    flib_init_files(MAX_FILES);
    int INPUT = 0;
    int RESULT = 1;
    int SIZE = 1000;

    create_random(INPUT, SIZE);
    tarant_allegra(INPUT, RESULT, 1000);
    check_result(RESULT, SIZE);
    flib_free_files();

    return 0;
}
#endif //__PROGTEST__
