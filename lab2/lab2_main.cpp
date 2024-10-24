#include <iostream>
#include "superstring.hpp"

using namespace std;

int main() {
    SuperString str("Hello, World!");

    cout << str.length() << ' ' << str[-1] << endl;

    str += "123";

    cout << (str == "Hello, World!123") << endl;

    return 0;
}
