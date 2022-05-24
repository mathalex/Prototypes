#include "forecast.h"
#include <deque>

using std::deque;

/// Simple moving average
class SMA : public Forecast {
public:
    SMA(double frame) : frame(frame) {}

    void add(const Data& data) override {
        points.push_back(data);
        cur_value += data.value;
        cur_time = data.time;
        while (points.front().time < cur_time - frame) {
            cur_value -= points.front().value;
            points.pop_front();
        }
    }

    /// future estimations are slow (the number of iterations is
    /// up to the the number of points in frame) and inaccurate
    double get(double time) override {
        double cur_sum = cur_value;
        int cnt = points.size();
        for (const auto& p : points) {
            if (p.time < time - frame) {
                --cnt;
                cur_sum -= p.value;
            } else {
                break;
            }
        }
        // it is ok even if cnt == 0 (then it will be nan)
        return cur_sum / cnt;
    }

private:
    // how far into the past we should watch from the current moment
    double frame;
    // aggregated sum over all points in frame
    double cur_value = 0;
    // points in frame
    deque<Data> points;
};
