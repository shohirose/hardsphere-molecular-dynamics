#include "hardsphere/collision.hpp"
#include <catch2/catch.hpp>

TEST_CASE("collisions of hardsphere particles", "[collision_time]") {
  using hardsphere::collision_time;
  using hardsphere::particle;

  SECTION("two particles collide") {
    particle p1({-1.0, 0.0}, {1.0, 0.0}, 0.01);
    particle p2({1.0, 0.0}, {-1.0, 0.0}, 0.01);
    const auto t = collision_time(p1, p2);
    REQUIRE(t.has_value());
    REQUIRE(*t == Approx(0.99));
  }

  SECTION("two particles do not collide") {
    particle p1({-1.0, 0.0}, {0.0, 1.0}, 0.01);
    particle p2({1.0, 0.0}, {0.0, -1.0}, 0.01);
    const auto t = collision_time(p1, p2);
    REQUIRE(!t.has_value());
  }

  SECTION("two particles move in parallel") {
    particle p1({-1.0, 0.0}, {0.0, 1.0}, 0.01);
    particle p2({1.0, 0.0}, {0.0, 1.0}, 0.01);
    const auto t = collision_time(p1, p2);
    REQUIRE(!t.has_value());
  }

  SECTION("two particles move in opposite direction") {
    particle p1({-1.0, 0.0}, {-1.0, 0.0}, 0.01);
    particle p2({1.0, 0.0}, {1.0, 0.0}, 0.01);
    const auto t = collision_time(p1, p2);
    REQUIRE(!t.has_value());
  }
}