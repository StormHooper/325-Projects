// Author: Tyler Pham
// CECS 325-02
// Prog 3 - Sorting Contest
// Due 03/12/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Please enter 3 parameters: \n\tParameter 1: total count of numbers you want. \n\tParameter 2: min value. \n\tParameter 3: max value. \n"
        "Example: $ generate 10000000 100000 999999\n";
        return -1;
    }
    else
    {
        cout << "argv[0]:" << argv[0] << "\nargv[1]:" << argv[1] << "\nargv[2]:" << argv[2] << "\nargv[3]:" << argv[3] << "\n";
    }
    ofstream numData {"numbers.dat"};
    srand(time(0));
    for (size_t i {0}; i < atoi(argv[1]); ++i)
    {
        numData << rand() % abs(atoi(argv[2]) - atoi(argv[3]) - 1) + atoi(argv[2]) << '\n';
    }
    numData.close();
    return 0;
}
