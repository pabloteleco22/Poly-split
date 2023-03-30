#include <iostream>
#include "lib/poly/line.h"
#include "lib/poly/vector.h"

using namespace std;

int main() {
    Vector vec1{1.0, 2.0, 3.0};
    Vector vec2{4.0, 5.0, 6.0};
    Line lin1;
    Line lin2{vec1, vec2};
    Line lin3{-3.0, 3.0, -3.0};

    cout << lin1 << endl;
    cout << lin2 << endl;
    cout << lin3 << endl;

    return 0;
}