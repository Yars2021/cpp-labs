#include <iostream>

using namespace std;

void test_func(unsigned long long arg1, float arg2) {
	cout << "Sum" << arg1 + arg2 << "\n";
	cout << "Sub" << arg1 - arg2 << "\n";
	cout << "Mul" << arg1 * arg2 << "\n";
	cout << "Div" << arg1 / arg2 << "\n";
	cout << "Result of (arg1 + arg2) / arg1 * 100:" <<  (arg1 + arg2) / arg1 * 100 << "\n";
	cout << "Result of (arg1 - arg2) / arg2 * 100:" <<  (arg1 - arg2) / arg2 * 100 << "\n";
}

int main() {
	unsigned long long arg1 = 9471209571289, float arg2 = 2323.2222;
	test_func(arg1, arg2);
	return 0;
}
