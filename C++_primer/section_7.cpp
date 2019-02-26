/*
 * File name: section_7.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{

}

class Demo {
    public:
        Demo() = default;
        Demo(int i, int ii): num(i) {  };
        Demo(int ii): Demo(i, 0) {  };

        int func(int i);
        int func2(Demo&);
        explicit int fun3(Demo&);

        friend int func4(int i) {return i}

        mutable int access_i;

        void access() const { return access_i++; }

        Demo &func4();
        Demo &func4() const;

        static int sta_i;

    private:
        int num;
        int num2 = 10;
}

Demo::func(int i)
{

}

int i = 10;
demo.func2(i);

struct Data {
    int i;
    string s;
}
