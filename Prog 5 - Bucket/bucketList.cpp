// Author: Tyler Pham
// CECS 325-02
// Prog 4 - Sorting Contest w/ pThreads
// Due 03/28/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class Bucket{
    private:
        vector<int> v;

    public:
        Bucket();
        void generate(int size, int min, int max); 
        void sort(); // Use the bubble sort from Prog3 and Prog4
        int size();
        int atIndex();
        int merge(Bucket b); // merge b into this
};

int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:"<< bucketCount <<endl;
    cout << "Bucket Size:"<< bucketSize <<endl;
    cout << "Bucket Min Value:"<< bucketMin <<endl;
    cout << "Bucket Max value:"<< bucketMax <<endl;

    vector<Bucket> list; // create empty Bucket vector
    Bucket *bptr;

    for (int i {0}; i < bucketCount; i++)
    {
        bptr = new Bucket; // allocates new Bucket
        bptr -> generate(bucketSize, bucketMin, bucketMax);
        // Bucket::generage(int, int, int, int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it {list.begin()}; it != list.end(); it++)
    {
        it -> sort(); // Bucket::sort
    }
    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // While size of the bucket vector > 0
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in list
    }

    // write all the items in endGame bucket to a file
    fstream out("bucketList.out", ios::out);
    for (int i {0}; i < endGame.size(); i++)
        out << endGame.atIndex(i) << endl;

    cout << "Global Swap Count:" << globalSwapCount << endl;
    cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";
    return 0;
}