#include "forecast.h"
#include <optional>
#include <vector>

using std::optional;
using std::vector;

struct NullableData {
    double time;
    optional<double> value;
};

Data make_normal(const NullableData& nd) {
    return {nd.time, *nd.value};
}

void fill_predict(vector<NullableData>& points, Forecast* forecast) {
    for (auto& pt : points) {
        if (pt.value) {
            forecast->add(make_normal(pt));
        } else {
            pt.value = forecast->get(pt.time);
        }
    }
}
