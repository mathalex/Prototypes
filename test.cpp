#include <iostream>

#include "exp1_smooth.h"
#include "exp2_smooth.h"
#include "sma.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    {
    cerr << "-----01-----\n";
    Exp1Smooth test(0.5);
    test.add({1, 1});
    cerr << test.get() << '\n';
    for (int i = 0; i < 10; ++i) {
        /// check, that we are approaching to 2
        test.add({i + 2., 2});
        cerr << test.get() << '\n';
    }
    }

    {
    cerr << "-----02-----\n";
    Exp2Smooth test(0.5, 1.5);
    for (int i = 0; i < 10; ++i) {
        /// Add line v = 3t + 2
        test.add({i + 0., i * 3 + 2.});
    }
    for (int i = 0; i < 10; ++i) {
        /// Pretty accurate estimation
        double t = test.get_time() + i;
        cerr << "Time: " << t << "; Value: " << test.get(t) << "; Absolute error: " << abs(test.get(t) - (3 * t + 2)) << '\n';
    }
    }

    {
    cerr << "-----03-----\n";
    Exp2Smooth test(0.5, 1.5);
    for (int i = 0; i < 10; ++i) {
        /// Add line v = t^2 + 3t + 2
        test.add({i + 0., i * i + 3 * i + 2.});
    }
    for (int i = 0; i < 10; ++i) {
        /// Parabola is not so good
        double t = test.get_time() + i;
        cerr << "Time: " << t << "; Value: " << test.get(t) << "; Absolute error: " << abs(test.get(t) - (t * t + 3 * t + 2)) << '\n';
    }
    }

    {
    cerr << "-----04-----\n";
    SMA test(7.);
    for (int i = 0; i < 10; ++i) {
        test.add({i * i - 3 * i + 3., i + 0.});
        cerr << test.get(test.get_time() + (i % 7)) << '\n';
    }
    // far moment
    cerr << test.get(test.get_time() + 100) << '\n';
    }
    return 0;
}
