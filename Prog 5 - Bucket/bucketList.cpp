// Author: Tyler Pham
// CECS 325-02
// Prog 5 - Bucket List
// Due 04/23/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

int globalSwapCount {0};
class Bucket{
    private:
        vector<int> v;

    public:
        Bucket() {};

        void generate(int size, int min, int max)
        {
            for (size_t i {0}; i < size; ++i)
                v.push_back(rand() % abs(min) - max - 1 + min);
        }

        void sort() // Use the bubble sort from Prog3 and Prog4
        {
            int temp {};
            for (size_t i {0}; i < size(); ++i)
            {
                for (size_t j {i+1}; j < size(); ++j)
                    if (v[i] > v[j])
                    {
                        temp = v[i];
                        v[i] = v[j];
                        v[j] = temp;
                        ++globalSwapCount;
                    }
            }
        }

        int size()
        {
            return v.size();
        }

        int atIndex(int i)
        {
            return v[i];
        }

        void merge(Bucket b) // merge b into this
        {
            int temp[size() + b.size()];
            size_t i {0}, index1 {0}, index2 {0};

            while (index1 < size() && index2 < b.size()) 
                temp[i++] = (v[index1] < b.v[index2]) ? v[index1++] : b.v[index2++];

            while (index1 < size())
                temp[i++] = v[index1++];
            while (index2 < b.size())
                temp[i++] = b.v[index2++];

            for (size_t i {0}; i < sizeof(temp)/sizeof(temp[i]); ++i)
            {
                if (i < size())
                    v[i] = temp[i];
                else
                    v.push_back(temp[i]);
            }
        }
};

int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:" << bucketCount << endl;
    cout << "Bucket Size:" << bucketSize << endl;
    cout << "Bucket Min Value:" << bucketMin << endl;
    cout << "Bucket Max value:" << bucketMax << endl;

    vector<Bucket> list; // create empty Bucket vector
    Bucket *bptr;

    for (int i {0}; i < bucketCount; i++)
    {
        bptr = new Bucket; // allocates new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);
        // Bucket::generage(int, int, int, int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        it->sort(); // Bucket::sort
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
