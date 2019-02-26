/*
 * File name: section_5.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

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
