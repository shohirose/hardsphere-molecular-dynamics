#ifndef HARDSPHERE_VECTOR2D_HPP
#define HARDSPHERE_VECTOR2D_HPP

#include <cmath>
#include <iostream>

namespace hardsphere {

/// @brief 2D vector
struct vector2d {
  /// @name Static Functions
  /// @{
  /// @brief Returns zero vector
  static vector2d zero() noexcept { return {0.0, 0.0}; }

  /// @brief Returns one vector
  static vector2d one() noexcept { return {1.0, 1.0}; }

  /// @brief Returns constant vector
  static vector2d constant(double c) noexcept { return {c, c}; }
  /// @}

  /// @name Constructors
  /// @{
  vector2d() = default;
  vector2d(double x, double y) : x_{x}, y_{y} {}
  vector2d(const vector2d&) = default;
  vector2d(vector2d&&) = default;
  /// @}

  vector2d& operator=(const vector2d&) = default;
  vector2d& operator=(vector2d&&) = default;

  const auto& x() const noexcept { return x_; }
  const auto& y() const noexcept { return y_; }
  auto& x() noexcept { return x_; }
  auto& y() noexcept { return y_; }

  /// @brief Returns squared norm
  auto squared_norm() const noexcept { return x_ * x_ + y_ * y_; }

  /// @brief Returns norm
  auto norm() const noexcept { return std::sqrt(this->squared_norm()); }

  /// @brief Returns dot product
  auto dot(const vector2d& other) const noexcept {
    return x_ * other.x() + y_ * other.y();
  }

 private:
  /// @brief X component
  double x_;
  /// @brief Y component
  double y_;
};

inline vector2d operator+(const vector2d& v1, const vector2d& v2) {
  return {v1.x() + v2.x(), v1.y() + v2.y()};
}

inline vector2d operator-(const vector2d& v1, const vector2d& v2) {
  return {v1.x() - v2.x(), v1.y() - v2.y()};
}

inline vector2d operator*(const vector2d& v, double a) {
  return {v.x() * a, v.y() * a};
}

inline vector2d operator*(double a, const vector2d& v) {
  return {v.x() * a, v.y() * a};
}

inline vector2d operator/(const vector2d& v, double a) {
  return {v.x() / a, v.y() / a};
}

inline std::istream& operator>>(std::istream& is, vector2d& v) {
  return is >> v.x() >> v.y();
}

inline std::ostream& operator<<(std::ostream& os, const vector2d& v) {
  return os << v.x() << ' ' << v.y();
}

}  // namespace hardsphere

#endif  // HARDSPHERE_VECTOR2D_HPP