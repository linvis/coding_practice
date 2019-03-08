/*
 * File name: 100m_file_read_write.cpp
 */

// solution 1, one thread

#include <iostream>
#include <thread>
#include <fstream>

using namespace std;

// use command to create 1M random file
// dd if=/dev/urandom of=test.file count=1024 bs=1024

void handler(void)
{
    ifstream rfile; 
    ofstream wfile;
    string line;

    cout << "11111" << endl;

    rfile.open("./test.file");
    wfile.open("./write.file");

    while (!rfile.eof()) {
        getline(rfile, line, '\n');
        wfile << line << flush;
    }

    rfile.close();
    wfile.close();
}

int main(void)
{
    thread t(handler);

    t.join();
}
