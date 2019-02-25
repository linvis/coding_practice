/*
 * File name: section_3.cpp
 */
#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    string s1 = "hello world";
    cout << s1 << endl;

    string s2(10, 'c');
    cout << s2 << endl;

    string line;
    getline(cin, line);
    cout << line << endl;

    string s5 = "jarvis," + s1;
    cout << s5 << endl;

    for (auto c : s5)
        cout << c << endl;
    for (auto &c : s5) {
        c = toupper(c);
        cout << c << endl;
    }

    vector<int> v1(10, 2);
    // cout << v1 << endl;
    for (auto v : v1)
        cout << v << endl;
    for (auto v = v1.begin(); v < v1.end(); v++)
        cout << *v << endl;

}
