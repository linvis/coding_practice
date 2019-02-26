/*
 * File name: section_4.cpp
 */

#include <iostream>

using namespace std;

int main(void)
{
    int a = 10;
    double b = static_cast<double>(a);

    cout << b << endl;

    const char *p;
    char *pc = const_cast<char*>(p);

    int *pp;
    char *ppc = reinterpret_cast<char*>(pp);
}
