#include "forecast.h"
#include <math.h>
#include <vector>

using std::vector;

/// a.k.a. Holt Winters for additive seasonality
class Exp3Smooth : public Forecast {
public:
    Exp3Smooth(double alpha, double beta, double gamma, int period) :
        alpha(alpha), beta(beta), gamma(gamma), period(period), cur_seasonality(period) {}

    void add(const Data& data) override {
        if (cur_time == -1) {
            cur_time = data.time;
            cur_data = data.value;
            cur_trend = 0;
            return;
        }

        double mult_alpha = exp(alpha * (cur_time - data.time));
        double mult_beta = exp(beta * (cur_time - data.time));
        double mult_gamma = exp(gamma * (cur_time - data.time));

        int cur_day = int(data.time) % period;

        double new_data = mult_alpha * (cur_data + cur_trend) + (1 - mult_alpha) * (data.value - cur_seasonality[cur_day]);
        double new_trend = mult_beta * cur_trend + (1 - mult_beta) * (new_data - cur_data);
        cur_seasonality[cur_day] = mult_gamma * cur_seasonality[cur_day] + (1 - mult_gamma) * (data.value - cur_data - cur_trend);
        cur_data = new_data;
        cur_trend = new_trend;
        cur_time = data.time;
    }

    double get(double time) override {
        return cur_data + (time - cur_time) * cur_trend + cur_seasonality[int(time) % period];
    }

private:
    // smoothing degree for data, positive
    double alpha;
    // smoothing degree for trend, positive
    double beta;
    // smoothing degree for seasonality, positive
    double gamma;
    // season length
    int period;
    // aggregated value over all points
    double cur_data;
    double cur_trend;
    vector<double> cur_seasonality;
};


