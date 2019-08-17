#include "hardsphere/collision.hpp"

namespace hardsphere {

std::optional<double> collision_time(                   //
    const vector2d& x1, const vector2d& v1, double a1,  //
    const vector2d& x2, const vector2d& v2, double a2) {
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

void collide(vector2d& x1, vector2d& v1, double m1,  //
             vector2d& x2, vector2d& v2, double m2,  //
             double tc) {
  const auto dx = x1 - x2;
  const auto dv = v1 - v2;
  const auto b = dx.dot(dv);
  const auto rsqr = dx.squared_norm();
  x1 = new_position(x1, v1, tc);
  x2 = new_position(x2, v2, tc);
  v1 -= 2 * b / rsqr * (m2 / (m1 + m2)) * dx;
  v2 += 2 * b / rsqr * (m1 / (m1 + m2)) * dx;
}

}  // namespace hardsphere
