#include <iostream>
#include "superstring.hpp"

using namespace std;

int main() {
    SuperString str("Hello, World!");

    cout << str.length() << ' ' << str[-1] << endl;

    for (unsigned int i = 0; i < str.length(); cout << str[i++]);
    cout << endl;
    for (unsigned int i = 0; i < str.length(); cout << str[-i++]);
    cout << endl;

    return 0;
}
