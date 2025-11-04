#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    cout << "Welcome to the Codacy C++ Project!" << endl;
    int x = 10, y = 5;
    cout << "Sum: " << add(x, y) << endl;
    return 0;
}
