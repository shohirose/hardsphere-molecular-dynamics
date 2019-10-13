#include "hardsphere/vector2d.hpp"

namespace hardsphere {

Vector2d Vector2d::zero() noexcept { return {0.0, 0.0}; }

Vector2d Vector2d::one() noexcept { return {1.0, 1.0}; }

Vector2d Vector2d::constant(double c) noexcept { return {c, c}; }

std::istream& operator>>(std::istream& is, Vector2d& v) {
  return is >> v.x() >> v.y();
}

std::ostream& operator<<(std::ostream& os, const Vector2d& v) {
  return os << v.x() << ' ' << v.y();
}

}  // namespace hardsphere