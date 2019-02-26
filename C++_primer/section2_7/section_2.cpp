/*
 * File name: section_2.cpp
 */

#include <iostream>

using namespace std;

int reused = 10;

int main(void)
{
    cout << ::reused << endl; 

    // reference
    int val = 11;
    int &rval = val;
    cout << rval <<endl;

    // pointer
    int *pval = &val;
    cout << *pval <<endl;

    // reference from pointer
    int *&prval = pval;
    cout << *prval << endl;

    // const pointer
    const double pi = 3.14;
    const double *ppi = &pi;
    cout << *ppi << endl;

    // top-level const and low-level const
    int i = 0;
    int *const p1 = &i;
    const int ci = 42;
    const int *pci = &ci;
    cout << *p1 << endl;
    cout << *pci << endl;

    // constexpr
    constexpr int mf = 20;
    constexpr int limit = mf + 1;
    cout << limit << endl;

    // auto
    int b = 20;
    auto bb = b;
    cout << bb << endl;
    const int c = 21;
    const auto cc = c;
    cout << cc << endl;

    // decltype
    const int d = 1;
    decltype(d) x = 11;
    cout << x << endl;
    decltype((d)) dd = d;
    cout << dd << endl;

}
