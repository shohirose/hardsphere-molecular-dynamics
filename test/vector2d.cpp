#include "hardsphere/vector2d.hpp"
#include <catch2/catch.hpp>

namespace hs = hardsphere;

TEST_CASE("vector calculus unit tests", "[Vector2d]") {
  using hs::Vector2d;
  SECTION("constructs from two floating point values") {
    Vector2d v{1.0, 2.0};
    CHECK(v.x() == Approx(1.0));
    CHECK(v.y() == Approx(2.0));
  }

  SECTION("constructs from zero vector") {
    const auto v = Vector2d::zero();
    CHECK(v.x() == Approx(0.0));
    CHECK(v.y() == Approx(0.0));
  }

  SECTION("constructs from one vector") {
    const auto v = Vector2d::one();
    CHECK(v.x() == Approx(1.0));
    CHECK(v.y() == Approx(1.0));
  }

  SECTION("constructs from constant vector") {
    const auto v = Vector2d::constant(3.0);
    CHECK(v.x() == Approx(3.0));
    CHECK(v.y() == Approx(3.0));
  }

  SECTION("vector norms") {
    Vector2d v{1.0, 2.0};
    CHECK(v.norm() == Approx(std::sqrt(5.0)));
    CHECK(v.squaredNorm() == Approx(5.0));
  }

  SECTION("vector normalization") {
    Vector2d v1{1.0, 2.0};
    const auto v2 = v1.normalized();
    v1.normalize();
    CHECK(v1.x() == Approx(1.0 / std::sqrt(5.0)));
    CHECK(v1.y() == Approx(2.0 / std::sqrt(5.0)));
    CHECK(v2.x() == Approx(1.0 / std::sqrt(5.0)));
    CHECK(v2.y() == Approx(2.0 / std::sqrt(5.0)));
  }

  SECTION("vector calculus") {
    Vector2d v1{1.0, 2.0};
    Vector2d v2{2.0, 5.0};

    SECTION("dot product") {
      const auto d = v1.dot(v2);
      CHECK(d == Approx(12.0));
    }

    SECTION("addition") {
      auto v3 = v1 + v2;
      CHECK(v3.x() == Approx(3.0));
      CHECK(v3.y() == Approx(7.0));
      v3 += v1;
      CHECK(v3.x() == Approx(4.0));
      CHECK(v3.y() == Approx(9.0));
    }

    SECTION("subtraction") {
      auto v3 = v1 - v2;
      CHECK(v3.x() == Approx(-1.0));
      CHECK(v3.y() == Approx(-3.0));
      v3 -= v1;
      CHECK(v3.x() == Approx(-2.0));
      CHECK(v3.y() == Approx(-5.0));
    }

    SECTION("multiplication") {
      auto v3 = v1 * 2.0;
      CHECK(v3.x() == Approx(2.0));
      CHECK(v3.y() == Approx(4.0));
      v3 *= 2.0;
      CHECK(v3.x() == Approx(4.0));
      CHECK(v3.y() == Approx(8.0));

      auto v4 = 2.0 * v1;
      CHECK(v4.x() == Approx(2.0));
      CHECK(v4.y() == Approx(4.0));
      v4 *= 2.0;
      CHECK(v3.x() == Approx(4.0));
      CHECK(v3.y() == Approx(8.0));
    }

    SECTION("division") {
      auto v3 = v1 / 2.0;
      CHECK(v3.x() == Approx(0.5));
      CHECK(v3.y() == Approx(1.0));
      v3 /= 2.0;
      CHECK(v3.x() == Approx(0.25));
      CHECK(v3.y() == Approx(0.5));
    }
  }
}