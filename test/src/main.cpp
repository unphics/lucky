#include <iostream>

using namespace std;

extern "C" int prog();

int main(int argc, char** argv)
{
    cout << "hello world!" << endl;
    prog();
    cout << prog() << endl;
    return 0;
}
