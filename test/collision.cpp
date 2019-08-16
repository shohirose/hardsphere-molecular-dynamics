#include "hardsphere/collision.hpp"
#include <catch2/catch.hpp>

TEST_CASE("collisions of hardsphere particles", "[collision_time]") {
  using hardsphere::collision_time;
  using hardsphere::vector2d;

  SECTION("two particles collide") {
    vector2d x1(-1.0, 0.0);
    vector2d v1(1.0, 0.0);

    vector2d x2(1.0, 0.0);
    vector2d v2(-1.0, 0.0);

    double a1 = 0.01;
    double a2 = 0.01;

    const auto t = collision_time(x1, v1, a1, x2, v2, a2);
    REQUIRE(t.has_value());
    REQUIRE(*t == Approx(0.99));
  }

  SECTION("two particles do not collide") {
    vector2d x1(-1.0, 0.0);
    vector2d v1(0.0, 1.0);

    vector2d x2(1.0, 0.0);
    vector2d v2(0.0, -1.0);

    double a1 = 0.01;
    double a2 = 0.01;

    const auto t = collision_time(x1, v1, a1, x2, v2, a2);
    REQUIRE(!t.has_value());
  }
}