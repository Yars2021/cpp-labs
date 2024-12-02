#include <iostream>
#include <vector>
#include "superstring.hpp"

using namespace std;

void simple_demo() {
    SuperString str("Hello, World!");

    cout << str.length() << ' ' << str[-1] << endl;

    for (unsigned int i = 0; i < str.length(); cout << str[i++]);
    cout << endl;
    for (unsigned int i = 0; i < str.length(); cout << str[-i++]);
    cout << endl;
}

SuperString pass(SuperString in) {
    return SuperString(in);;
}

int main() {
    simple_demo();

    SuperString static_array[5];
    SuperString *dynamic = new SuperString;

    delete(dynamic);

    pass(SuperString("ABCDEF"));

    std::vector<SuperString> test;

    for (int i = 0; i < 5; i++) {
        test.push_back(SuperString("AAA"));
    }

    return 0;
}
