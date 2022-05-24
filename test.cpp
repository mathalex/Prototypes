#include <iostream>

#include "exp1_smooth.h"
#include "exp2_smooth.h"
#include "sma.h"
#include "shock_detector.h"
#include "predictor.h"
#include "exp3_smooth.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    { /// Test simple exponential smoothing
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

    { /// Try to predict linear trends
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

    { /// Try to predict parabolic trends
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

    { /// Just test SMA with unequal number of points in window
    cerr << "-----04-----\n";
    SMA test(7.);
    for (int i = 0; i < 10; ++i) {
        test.add({i * i - 3 * i + 3., i + 0.});
        cerr << test.get(test.get_time() + (i % 7)) << '\n';
    }
    // far moment
    cerr << test.get(test.get_time() + 100) << '\n';
    }

    { /// Find shocks, using different predictors. Here we have two blatant shocks: time 3 and 6
    cerr << "-----05-----\n";
    SMA sma(5.);
    vector<Data> points = {{1, 1}, {2, 2}, {3, 6}, {4, 6}, {5, 6}, {6, 1}, {7, 1}, {8, 0}, {9, 0}};
    auto cur = get_shocks(points, 5, &sma, 1);
    for (size_t i = 0; i < points.size(); ++i) {
        cerr << "Time " << points[i].time << " Value " << points[i].value << " is " << (cur[i] ? "OK" : "shock") << '\n';
    }
    cerr << '\n';
    auto exp2 = Exp2Smooth(1., 2.);
    cur = get_shocks(points, 5, &exp2, 0.5);
    for (size_t i = 0; i < points.size(); ++i) {
        cerr << "Time " << points[i].time << " Value " << points[i].value << " is " << (cur[i] ? "OK" : "shock") << '\n';
    }
    }

    { /// Testing predictions: we should see trend prediction (approximately 4, 5, 6, 9 on gaps)
    cerr << "-----06-----\n";
    auto exp2 = Exp2Smooth(2.5, 2.);
    vector<NullableData> points = {{1, 1}, {2, 2}, {3, 3}, {4, {}}, {5, {}}, {6, {}}, {7, 7}, {8, 8}, {9, {}}};
    fill_predict(points, &exp2);
    for (size_t i = 0; i < points.size(); ++i) {
        cerr << "Time " << points[i].time << " Value " << *points[i].value << '\n';
    }
    }

    { /// Testing Holt Winters: we should see seasonal prediction (approximately 1, 2, 3 on the last three points)
    cerr << "-----07-----\n";
    auto exp3 = Exp3Smooth(0.1, 0.2, 3., 3);
    vector<NullableData> points = {{1, 1}, {2, 2}, {3, 3}, {4, 1}, {5, 2}, {6, 3}, {7, {}}, {8, {}}, {9, {}}};
    fill_predict(points, &exp3);
    for (size_t i = 0; i < points.size(); ++i) {
        cerr << "Time " << points[i].time << " Value " << *points[i].value << '\n';
    }
    }
    return 0;
}
