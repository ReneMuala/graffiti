#pragma once

#include <blend2d/gradient.h>
#include <blend2d/rgba.h>
#include <deque>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

class Gradient {
public:
  enum Type { Linear, Radial };

private:
  Type type;
  std::deque<std::pair<double, BLRgba32>> steps;
  std::vector<double> values;
  std::function<double(double)> valueResolver;

public:
  Gradient(std::vector<double> values,
           std::function<double(double)> valueResolver)
      : values(values), valueResolver(valueResolver) {
    if (values.size() == 4) {
      type = Linear;
    } else if (values.size() == 5) {
      type = Radial;
    } else {
      throw std::runtime_error("Unexpected side of values for gradient");
    }
  }

  void step(double pct, int color) {
    steps.push_back(std::make_pair(pct, BLRgba32(color)));
  }

  BLGradient build() {
    BLGradient gradient =
        type == Linear
            ? BLGradient(BLLinearGradientValues(
                  valueResolver(values[0]), valueResolver(values[1]),
                  valueResolver(values[2]), valueResolver(values[3])))
            : BLGradient(BLRadialGradientValues(
                  valueResolver(values[0]), valueResolver(values[1]),
                  valueResolver(values[2]), valueResolver(values[3]),
                  valueResolver(values[4])));
    for(auto & [pct, value] : steps){
        gradient.addStop(pct,value);
    }
    return gradient;
  }
};