// Author: Tyler Pham
// CECS 325-02
// Prog 6 - BigInt
// Due 05/09/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

class BigInt
{
private:
    vector<char> v;
    BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1)
    {
        if (n < 4)
            return 0;
        return a + b + fiboHelper(n-1, b, a+b);
    }

public:
    BigInt() { v.push_back('0'); }

    BigInt(int num)
    {
        for (char digit : to_string(num))
            v.push_back(digit);
        reverse(v.begin(), v.end());
    }

    BigInt(string str)
    {
        for (char digit : str)
            v.push_back(digit);
        reverse(v.begin(), v.end());
    }

    BigInt operator+ (BigInt n) 
    {
        vector<char> result {};
        int carry {0}, num {0};
        for (size_t i {0}; i < max(size(), n.size()); ++i)
        {
            if (i < min(size(), n.size()))
            {
                num = static_cast<int>(v[i])-static_cast<int>('0') + static_cast<int>(n.v[i])-static_cast<int>('0') + carry;
            }
            else
            {
                num = ((size() == max(size(), n.size())) ? static_cast<int>(v[i]) : static_cast<int>(n.v[i]))-static_cast<int>('0') + carry;
            }
            if (num > 9)
            {
                carry = 1;
                result.push_back(to_string(num)[1]);
            }
            else
            {
                carry = 0;
                result.push_back(to_string(num)[0]);
            }
        }
        if (carry)
            result.push_back('1');
        return BigInt({result.rbegin(), result.rend()});
    }

    BigInt operator- (BigInt n)
    {
        vector<char> result {};
        vector<int> vt {};
        for (char digit : v)
            vt.push_back(static_cast<int>(digit)-static_cast<int>('0'));
        for (int i {0}; i < size(); ++i)
        {
            if (vt[i] < 0 || i < n.size() && v[i] < n.v[i])
            {
                vt[i+1] -= 1;
                vt[i] += 10;
            }
            if (i < n.size())
                vt[i] = vt[i] - (static_cast<int>(n.v[i]) - static_cast<int>('0'));
            result.push_back(vt[i]+ '0');
        }
        while (result[result.size()-1] == '0')
            result.pop_back();
        return BigInt({result.rbegin(), result.rend()});
    }

    // BigInt operator- (int);
    
    BigInt operator* (BigInt n)
    {
        BigInt result {0};
        for (BigInt i {0}; i < ((*this < n) ? *this : n); ++i)
            result = (*this < n) ? n + result : *this + result;
        return result;
    }

    BigInt operator/ (BigInt n)
    {
        BigInt divs {0};
        BigInt dividend (*this);
        while (n < dividend)
        {
            dividend = dividend - n;
            ++divs;
        }
        return divs;
    }

    BigInt operator% (BigInt n) { return BigInt(*this - (*this / n * n)); }

    BigInt operator++(int)
    {
        BigInt temp = *this;
        *this = *this + 1;
        return temp;
    }

    BigInt operator++( )
    {
        *this = *this + 1;
        return *this;
    }

    BigInt operator[](int); // index function

    void print()
    {
        vector<char> vr {v.rbegin(), v.rend()};
        for (char digit : vr)
            cout << digit;
        cout << '\n';
    }

    int size() { return v.size(); }

    BigInt fibo() { return fiboHelper(*this); } // calls fiboHelper

    BigInt fact()
    {
        BigInt counter {1}, result {1};
        while (counter < *this+1)
        {
            result = result * counter;
            ++counter;
        }
        return result;
    }

    friend ostream& operator<<(ostream& out, const BigInt& n);
    friend BigInt operator+ (int i, BigInt n);

    bool operator==(BigInt n) { return v == n.v; }
    bool operator<(BigInt n)
    {
        if (size() != n.size())
            return size() < n.size();
        vector<char> vr {v.rbegin(), v.rend()};
        vector<char> nr {n.v.rbegin(), n.v.rend()};
        for (size_t i {0}; i < size(); ++i) 
        {
            if (vr[i] < nr[i])
                return true;
        }
        return false;
    }

};

ostream& operator<<(ostream& out, const BigInt& n)
{
    vector<char> vr {n.v.rbegin(), n.v.rend()};
    if (n.v.size() <= 12)
    {
        for (char digit : vr)
            out << digit;
    }
    else
    {
        out << vr[0] << '.';
        for (size_t i {1}; i < 7; ++i)
            out << vr[i];
        out << 'e' << n.v.size()-1;
    }
    return out;
}

BigInt operator+(int i, BigInt n) { return static_cast<BigInt>(i) + n; }

void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"<<flush;
    system("whoami");
    system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);

    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");

    // display variables
    cout << "n1(int)    :"<<setw(space)<<n1<<endl; 
    cout << "s1(str)    :"<<setw(space)<<s1<<endl; 
    cout << "n2(int)    :"<<setw(space)<<n2<<endl; 
    cout << "s2(str)    :"<<setw(space)<<s2<<endl;
    cout << "n3(n2)     :"<<setw(space)<<n3<<endl; 
    cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
    cout << "fact(50)   :"<<setw(space)<<fact<<endl;
    cout << "imax       :"<<setw(space)<<imax<<endl;
    cout << "big        :"<<setw(space)<<big<<endl;
    cout << "big.print(): "; big.print(); cout << endl;

    cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
    cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
    cout << "fact("<<fact<<") = "<<fact.fact() << endl;

    cout << "10 + n1 = " << 10+n1 << endl;
    cout << "n1 + 10 = " << n1+10 << endl;

    cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
    cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
    cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;

    cout << "s2 * big = ? --> "<< s2 * big<<endl;
    cout << "big * s2 = ? --> "<< big * s2<<endl;
}

int main() 
{
    testUnit();
    return 0;
}
