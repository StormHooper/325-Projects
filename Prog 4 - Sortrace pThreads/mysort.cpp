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

void merge(int ss[], int start1, int end1, int start2, int end2)
{
    int temp[1000000];
    int i {start1}, j {start2}, k {0};
    while (i <= end1 && j <= end2)
    {
        if (ss[i] < ss[j])
            temp[k++] = ss[i++];
        else
            temp[k++] = ss[j++];
    }

    while (i <= end1)
        temp[k++] = ss[i++];
    while (j <= end2)
        temp[k++] = ss[j++];

    for (i = 0; i < k; ++i)
        ss[start1 + i] = temp[i];
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
    int counter {0};
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

    for (int size = counter / 8; size < counter; size *= 2)
    {
        for (int start = 0; start < counter - size; start += 2 * size)
        {
            int mid = start + size - 1;
            int end = min(start + 2 * size - 1, counter - 1);
            merge(numbers, start, mid, mid + 1, end);
        }
    }

    ofstream outputData {argv[2]};
    for (size_t i {0}; i < counter; ++i)
        outputData << numbers[i] << '\n';
    outputData.close();
    delete[] numbers;
    cout << "Ending bubble sort\n";
    return 0;
}
