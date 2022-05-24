#include "forecast.h"
#include <deque>
#include <math.h>
#include <vector>

using std::deque;

class ShockDetector {
public:
    ShockDetector(double frame, Forecast* forecast) : frame(frame), forecast(forecast) {}

    /// Return the deviation degree in number of standard deviation
    double add(const Data& data) {
        points.push_back(data);
        sum += data.value;
        sum_sqr += data.value * data.value;
        while (points.front().time < data.time - frame) {
            sum -= points.front().value;
            sum_sqr -= points.front().value * points.front().value;
            points.pop_front();
        }
        forecast->add(data);
        double sigma = sqrt(sum_sqr / points.size() - sum * sum / points.size() / points.size());
        if (points.size() == 1) {
            return 0.;
        }
        return abs((data.value - forecast->get(forecast->get_time())) / sigma);
    }

private:
    // frame for standard deviation
    double frame;
    // aggregated sum over all point values (and their squares) in frame
    double sum = 0, sum_sqr = 0;
    // points in frame
    deque<Data> points;
    // forecast system
    Forecast* forecast;
};

using std::vector;

/// return vector of same size as points with 'false' (0) representing shocks,
/// st_tol is standard deviation tolerance (which deviation counts as possible for non-shock event)
vector<bool> get_shocks(const vector<Data>& points, double frame, Forecast* forecast, double st_tol) {
    ShockDetector sd(frame, forecast);
    vector<bool> res(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        res[i] = (sd.add(points[i]) <= st_tol);
    }
    return res;
}
