#include "hardsphere/collision.hpp"

namespace hardsphere {

std::optional<double> collision_time(const vector2d& x1, const vector2d& v1,
                                     double a1, const vector2d& x2,
                                     const vector2d& v2, double a2) {
  const auto dx = x1 - x2;
  const auto dv = v1 - v2;
  const auto b = dx.dot(dv);
  const auto rsqr = dx.squared_norm();
  const auto vsqr = dv.squared_norm();
  const auto asqr = (a1 + a2) * (a1 + a2);
  const auto k = b * b - vsqr * (rsqr - asqr);

  if (k < 0) {
    return std::nullopt;
  } else {
    const auto t = -(b + std::sqrt(k)) / vsqr;
    // If two particles move in parallel, vsqr becomes zero, and t becomes NaN.
    // If t is negative, two particles have already collided, and will not
    // collide.
    if (std::isnan(t) || t < 0)
      return std::nullopt;
    else
      return t;
  }
}

}  // namespace hardsphere
