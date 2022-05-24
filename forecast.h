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
};
