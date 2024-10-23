#include <iostream>
#include "pystring.hpp"

using namespace std;

int main() {
    PYString str("Hello, World!");

    cout << str[-1] << endl;

    return 0;
}
