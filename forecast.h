#pragma once

class Forecast {
public:
    struct Data {
        double time;
        double value;
    };

    /// add new point, time is ascending over additions
    virtual void add(const Data& data) = 0;

    /// try to predict the value at particular time
    virtual double get(double time) = 0;

    double get_time() {
        return cur_time;
    }

protected:
    // time of the last point
    double cur_time = -1;
};
