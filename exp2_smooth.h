#include "forecast.h"
#include <math.h>

class Exp2Smooth : public Forecast {
public:
    Exp2Smooth(double alpha, double beta) : alpha(alpha), beta(beta) {}

    void add(const Data& data) override {
        if (cur_time == -1) {
            cur_time = data.time;
            cur_data = data.value;
            cur_trend = 0;
            return;
        }

        double mult_alpha = exp(alpha * (cur_time - data.time));
        double mult_beta = exp(beta * (cur_time - data.time));

        double new_data = mult_alpha * (cur_data + cur_trend) + (1 - mult_alpha) * data.value;
        cur_trend = mult_beta * cur_trend + (1 - mult_beta) * (new_data - cur_data);
        cur_data = new_data;
        cur_time = data.time;
    }

    double get(double time) override {
        return cur_data + (time - cur_time) * cur_trend;
    }

private:
    // smoothing degree for data, positive
    double alpha;
    // smoothing degree for trend, positive
    double beta;
    // aggregated value over all points
    double cur_data;
    double cur_trend;
};

