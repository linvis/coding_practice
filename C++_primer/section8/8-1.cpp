/*
 * File name: 8-1.cpp
 */
#include <iostream>

using namespace std;

istream& read_file(istream &io)
{
    string s;

    io.tie(&cout);

    while (io >> s)
        cout << s;

    return io;
}

int main(void)
{
    istream &io = cin;
    auto old_state = io.rdstate();

    io.clear();
    read_file(io);

    cout << "byebye" << endl;

    io.setstate(old_state);

    return 0;
}

