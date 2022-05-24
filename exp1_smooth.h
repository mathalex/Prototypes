#include "forecast.h"
#include <math.h>

class Exp1Smooth : public Forecast {
public:
    Exp1Smooth(double alpha) : alpha(alpha) {}

    void add(const Data& data) override {
        if (cur_time == -1) {
            cur_time = data.time;
            cur_value = data.value;
            return;
        }
        // exp argument will be negative
        double mult = exp(alpha * (cur_time - data.time));
        cur_value = cur_value * mult + data.value * (1 - mult);
        cur_time = data.time;
    }

    double get() override {
        return cur_value;
    }

private:
    // smoothing degree, positive
    double alpha;
    // time of the last point
    double cur_time = -1;
    // aggregated value over all points
    double cur_value;
};
