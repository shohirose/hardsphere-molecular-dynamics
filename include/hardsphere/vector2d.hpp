#ifndef HARDSPHERE_VECTOR2D_HPP
#define HARDSPHERE_VECTOR2D_HPP

#include <array>
#include <cmath>
#include <iostream>

namespace hardsphere {

/// @brief 2D vector
class Vector2d {
 public:
  /// @name Static Functions
  /// @{
  /// @brief Returns zero vector
  static Vector2d zero() noexcept;

  /// @brief Returns a vector filled with one
  static Vector2d one() noexcept;

  /// @brief Returns a vector filled with a given constant
  static Vector2d constant(double c) noexcept;
  /// @}

  /// @name Constructors
  /// @{
  Vector2d() = default;
  Vector2d(double x, double y) : v_{x, y} {}
  Vector2d(const Vector2d&) = default;
  Vector2d(Vector2d&&) = default;
  /// @}

  auto x() const noexcept { return v_[0]; }
  auto y() const noexcept { return v_[1]; }
  auto& x() noexcept { return v_[0]; }
  auto& y() noexcept { return v_[1]; }

  Vector2d& operator=(const Vector2d&) = default;
  Vector2d& operator=(Vector2d&&) = default;
  Vector2d& operator+=(const Vector2d& other) {
    v_[0] += other.x();
    v_[1] += other.y();
    return *this;
  }
  Vector2d& operator-=(const Vector2d& other) {
    v_[0] -= other.x();
    v_[1] -= other.y();
    return *this;
  }
  Vector2d& operator*=(double a) {
    v_[0] *= a;
    v_[1] *= a;
    return *this;
  }
  Vector2d& operator/=(double a) {
    v_[0] /= a;
    v_[1] /= a;
    return *this;
  }

  /// @brief Returns squared norm
  auto squaredNorm() const noexcept { return v_[0] * v_[0] + v_[1] * v_[1]; }

  /// @brief Returns norm
  auto norm() const noexcept { return std::sqrt(this->squaredNorm()); }

  /// @brief Returns dot product
  auto dot(const Vector2d& other) const noexcept {
    return v_[0] * other.x() + v_[1] * other.y();
  }

  /// @brief Normalize this vector
  Vector2d& normalize() noexcept {
    const auto mag = this->norm();
    v_[0] /= mag;
    v_[1] /= mag;
    return *this;
  }

  /// @brief Returns normalized vector
  auto normalized() const noexcept {
    Vector2d v(*this);
    v.normalize();
    return v;
  }

  auto data() const noexcept { return v_.data(); }
  auto data() noexcept { return v_.data(); }

 private:
  std::array<double, 2> v_;
};

inline Vector2d operator+(const Vector2d& v1, const Vector2d& v2) {
  return {v1.x() + v2.x(), v1.y() + v2.y()};
}

inline Vector2d operator-(const Vector2d& v1, const Vector2d& v2) {
  return {v1.x() - v2.x(), v1.y() - v2.y()};
}

inline Vector2d operator*(const Vector2d& v, double a) {
  return {v.x() * a, v.y() * a};
}

inline Vector2d operator*(double a, const Vector2d& v) {
  return {v.x() * a, v.y() * a};
}

inline Vector2d operator/(const Vector2d& v, double a) {
  return {v.x() / a, v.y() / a};
}

std::istream& operator>>(std::istream& is, Vector2d& v);

std::ostream& operator<<(std::ostream& os, const Vector2d& v);

}  // namespace hardsphere

#endif  // HARDSPHERE_VECTOR2D_HPP