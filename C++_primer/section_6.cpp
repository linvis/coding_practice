/*
 * File name: section_6.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

// reference
int func1(int &r)
{
    r = 10;
}

// const
void func2(cont int i)
{

}

// array
void func3(const int *beg, const int* end)
{

}

// reference array
void fun4(int (&arr)[10])
{

}


// change parameter
void func5(initializer_list<string> il)
{

}

// return a vector
void func6(void)
{
    return {1, 2};
}

// override
void func7(int i)
{

}

void func7(const int i)
{

}

// const_cast override
const string &shortstring(const string &s1, const string &s2)
{
    retyurn s1.size() <= s2.size() ? s1 : s2;
}

string &shortstring(string &s1, string &s2)
{
    auto &r = shortstring(const_cast<const string&>s1,
            const_cast<const string&>s2);
    reutrn const_cast<string&>(r);
}

void func8(int i = 2, int j)
{

}

inline void func8(int i)
{

}

constexpr int new_sz() { reutrn 32;}
constexpr int foo = new_sz();


int main(void)
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    try {
        for (auto v : v1)
            cout << v << endl;
    }
    catch (exception) {
        cout << "exception" << endl;
    }
}
