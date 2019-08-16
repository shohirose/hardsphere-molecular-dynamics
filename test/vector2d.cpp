#include "hardsphere/vector2d.hpp"
#include <catch2/catch.hpp>

namespace hs = hardsphere;

TEST_CASE("vector calculus unit tests", "[vector2d]") {
  using hs::vector2d;
  SECTION("constructs from two floating point values") {
    vector2d v(1.0, 2.0);
    REQUIRE(v.x() == Approx(1.0));
    REQUIRE(v.y() == Approx(2.0));
  }

  SECTION("constructs from zero vector") {
    const auto v = vector2d::zero();
    REQUIRE(v.x() == Approx(0.0));
    REQUIRE(v.y() == Approx(0.0));
  }

  SECTION("constructs from one vector") {
    const auto v = vector2d::one();
    REQUIRE(v.x() == Approx(1.0));
    REQUIRE(v.y() == Approx(1.0));
  }

  SECTION("constructs from constant vector") {
    const auto v = vector2d::constant(3.0);
    REQUIRE(v.x() == Approx(3.0));
    REQUIRE(v.y() == Approx(3.0));
  }

  SECTION("vector norms") {
    vector2d v(1.0, 2.0);
    REQUIRE(v.norm() == Approx(std::sqrt(5.0)));
    REQUIRE(v.squared_norm() == Approx(5.0));
  }

  SECTION("vector calculus") {
    vector2d v1(1.0, 2.0);
    vector2d v2(2.0, 5.0);

    SECTION("addition") {
      const auto v3 = v1 + v2;
      REQUIRE(v3.x() == Approx(3.0));
      REQUIRE(v3.y() == Approx(7.0));
    }

    SECTION("subtraction") {
      const auto v3 = v1 - v2;
      REQUIRE(v3.x() == Approx(-1.0));
      REQUIRE(v3.y() == Approx(-3.0));
    }

    SECTION("multiplication") {
      const auto v3 = v1 * 2.0;
      REQUIRE(v3.x() == Approx(2.0));
      REQUIRE(v3.y() == Approx(4.0));

      const auto v4 = 2.0 * v1;
      REQUIRE(v4.x() == Approx(2.0));
      REQUIRE(v4.y() == Approx(4.0));
    }

    SECTION("division") {
      const auto v3 = v1 / 2.0;
      REQUIRE(v3.x() == Approx(0.5));
      REQUIRE(v3.y() == Approx(1.0));
    }
  }
}