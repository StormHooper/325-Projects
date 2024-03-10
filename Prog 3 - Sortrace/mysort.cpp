// Author: Tyler Pham
// CECS 325-02
// Prog 3 - Sorting Contest
// Due 03/12/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Please enter 2 parameters: \n\tParameter 1: input file. \n\tParameter 2: output file.\n";
        return -1;
    }
    ifstream numData {argv[1]};
    int numbers[1000000];
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
    bubble(numbers, counter);
    ofstream outputData {argv[2]};
    for (size_t i {0}; i < counter; ++i)
        outputData << numbers[i] << '\n';
    outputData.close();
    return 0;
}