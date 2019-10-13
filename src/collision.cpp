#include "hardsphere/collision.hpp"

namespace hardsphere {

std::optional<double> calcCollisionTime(const Particle& p1,
                                        const Particle& p2) noexcept {
  const auto t0 = (p1.time > p2.time) ? p1.time : p2.time;

  // Position at time t0
  const auto x1 = p1.position + p1.velocity * (t0 - p1.time);
  const auto x2 = p2.position + p2.velocity * (t0 - p2.time);

  const auto dx = x1 - x2;
  const auto dv = p1.velocity - p2.velocity;
  const auto b = dx.dot(dv);
  const auto rsqr = dx.squaredNorm();
  const auto vsqr = dv.squaredNorm();
  const auto asum = p1.radius + p2.radius;
  const auto asqr = asum * asum;
  const auto k = b * b - vsqr * (rsqr - asqr);

  if (k < 0) return std::nullopt;

  const auto dt = -(b + std::sqrt(k)) / vsqr;

  // If two particles move in parallel, vsqr becomes zero, and t becomes NaN.
  // If t is negative, two particles have already collided, and will not
  // collide.
  if (std::isnan(dt) || dt <= 0)
    return std::nullopt;
  else
    return t0 + dt;
}

void collide(Particle& p1, Particle& p2, double tc) noexcept {
  p1.position += p1.velocity * (tc - p1.time);
  p1.time = tc;

  p2.position += p2.velocity * (tc - p2.time);
  p2.time = tc;

  const auto dx = p1.position - p2.position;
  const auto dv = p1.velocity - p2.velocity;
  const auto b = dx.dot(dv);
  const auto rsqr = dx.squaredNorm();

  const auto m1 = p1.mass;
  const auto m2 = p2.mass;
  p1.velocity -= 2 * b / rsqr * (m2 / (m1 + m2)) * dx;
  p2.velocity += 2 * b / rsqr * (m1 / (m1 + m2)) * dx;
}

}  // namespace hardsphere
