// Author: Tyler Pham
// CECS 325-02
// Prog 4 - Sorting Contest w/ pThreads
// Due 03/28/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;

void bubble(int A[], int size)
{
    int temp{};
    for (size_t i {0}; i < size; ++i)
    {
        for (size_t j {i+1}; j < size; ++j)
            if (A[i] > A[j])
            {
                temp = A[i];
                A[i] = A[j];
                A[j] = temp;
            }
    }
}

struct sortStuff{
    int *start;
    int size;
};

void *bridge(void *ptr)
{
    sortStuff *arg = (sortStuff *)ptr;
    bubble(arg->start, arg->size);
    return NULL;
}

sortStuff merge(sortStuff &sec1, sortStuff &sec2)
{
    int mergeSize = sec1.size + sec2.size;
    int *temp = new int[mergeSize];
    size_t i {0}, j {0}, k {0};
    while (i != sec1.size && j != sec2.size)
    {
        if (sec1.start[i] < sec2.start[j])
            temp[k++] = sec2.start[j++];
        else
            temp[k++] = sec1.start[i++];
    }

    while (i < sec1.size)
        temp[k++] = sec1.start[i++];
    while (j < sec2.size)
        temp[k++] = sec2.start[j++];
    
    sec1.start = temp;
    sec1.size = mergeSize;
    return sec1;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Please enter 2 parameters: \n\tParameter 1: input file. \n\tParameter 2: output file.\n";
        return -1;
    }
    else
    {
        cout << "Starting Array bubble sort with 1000000 items\n";
    }
    ifstream numData {argv[1]};
    int *numbers = new int[1000000]; // dynamic memory
    size_t counter {0};
    string num {};
    while (getline(numData, num, '\n'))
    {
        if (counter < 1000000)
            numbers[counter++] = stoi(num);
        else
        {
            cout << "Max amount of numbers reached. Try again\n";
            return -1;
        }
    }
    numData.close();
    
    
    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;
    pthread_t t[8] = {t0, t1, t2, t3, t4, t5, t6, t7};
    sortStuff ss[8];
    
    for (size_t i {0}; i < 8; i++)
    {
        ss[i].start = &numbers[(counter/8) * i];
        ss[i].size = counter / 8;
    }

    int iret[8];
    for (size_t i {0}; i < 8; i++)
        iret[i] = pthread_create(&t[i], NULL, bridge, (void*) &ss[i]);
    for (size_t i {0}; i < 8; i++)
        pthread_join(t[i], NULL);

    // Merge once, 8 smaller sections into 4 larger sections.
    sortStuff mergedSect0 = merge(ss[0], ss[1]);
    sortStuff mergedSect1 = merge(ss[2], ss[3]);
    sortStuff mergedSect2 = merge(ss[4], ss[5]);
    sortStuff mergedSect3 = merge(ss[6], ss[7]);
    // Merge again, 4 sections into 2 sections.
    sortStuff mergedSect4 = merge(mergedSect0, mergedSect1);
    sortStuff mergedSect5 = merge(mergedSect2, mergedSect3);
    // Merge one last time, this will be the final array.
    sortStuff finalProduct = merge(mergedSect4, mergedSect5);
    ss[0] = finalProduct;

    ofstream outputData {argv[2]};
    for (size_t i {0}; i < counter; ++i)
    {
        numbers[i] = ss[0].start[i];
        outputData << numbers[i] << '\n';
    }
    outputData.close();
    delete[] numbers;
    cout << "Ending bubble sort\n";
    return 0;
}
