#include <iostream>

#include "exp1_smooth.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Exp1Smooth test(0.5);
    test.add({1, 1});
    cerr << test.get() << '\n';
    for (int i = 0; i < 10; ++i) {
        test.add({i + 2., 2});
        cerr << test.get() << '\n';
    }


    return 0;
}
