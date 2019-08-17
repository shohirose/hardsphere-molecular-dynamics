#include "hardsphere/collision.hpp"
#include <catch2/catch.hpp>

TEST_CASE("collisions of hardsphere particles", "[collision_time]") {
  using hardsphere::collision_time;
  using hardsphere::particle;

  SECTION("two particles collide") {
    particle p1({-1.0, 0.0}, {1.0, 0.0}, 0.01, 1.0);
    particle p2({1.0, 0.0}, {-1.0, 0.0}, 0.01, 1.0);
    const auto t = collision_time(p1, p2);
    REQUIRE(t.has_value());
    CHECK(*t == Approx(0.99));
  }

  SECTION("two particles do not collide") {
    particle p1({-1.0, 0.0}, {0.0, 1.0}, 0.01, 1.0);
    particle p2({1.0, 0.0}, {0.0, -1.0}, 0.01, 1.0);
    const auto t = collision_time(p1, p2);
    CHECK(!t.has_value());
  }

  SECTION("two particles move in parallel") {
    particle p1({-1.0, 0.0}, {0.0, 1.0}, 0.01, 1.0);
    particle p2({1.0, 0.0}, {0.0, 1.0}, 0.01, 1.0);
    const auto t = collision_time(p1, p2);
    CHECK(!t.has_value());
  }

  SECTION("two particles move in opposite direction") {
    particle p1({-1.0, 0.0}, {-1.0, 0.0}, 0.01, 1.0);
    particle p2({1.0, 0.0}, {1.0, 0.0}, 0.01, 1.0);
    const auto t = collision_time(p1, p2);
    CHECK(!t.has_value());
  }

  SECTION("two particles have just collided") {
    particle p1({-0.01, 0.0}, {-1, 0.0}, 0.01, 1.0);
    particle p2({0.01, 0.0}, {1.0, 0.0}, 0.01, 1.0);
    const auto t = collision_time(p1, p2);
    CHECK(!t.has_value());
  }
}

TEST_CASE("update position and velocity of colliding particles", "[collide]") {
  using hardsphere::collide;
  using hardsphere::collision_time;
  using hardsphere::particle;

  particle p1({-1.0, 0.0}, {1.0, 0.0}, 0.01, 1.0);
  particle p2({1.0, 0.0}, {-1.0, 0.0}, 0.01, 1.0);

  const auto t = collision_time(p1, p2);
  REQUIRE(t.has_value());
  CHECK(*t == Approx(0.99));

  collide(p1, p2, *t);

  CHECK(p1.position.x() == Approx(-0.01));
  CHECK(p1.position.y() == Approx(0.0));
  CHECK(p1.velocity.x() == Approx(-1.0));
  CHECK(p1.velocity.y() == Approx(0.0));

  CHECK(p2.position.x() == Approx(0.01));
  CHECK(p2.position.y() == Approx(0.0));
  CHECK(p2.velocity.x() == Approx(1.0));
  CHECK(p2.velocity.y() == Approx(0.0));
}