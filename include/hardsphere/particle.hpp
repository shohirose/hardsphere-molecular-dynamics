#ifndef HARDSPHERE_PARTICLE_HPP
#define HARDSPHERE_PARTICLE_HPP

#include "hardsphere/vector2d.hpp"

namespace hardsphere {

struct Particle {
  Vector2d position;
  Vector2d velocity;
  double radius;
  double mass;
  double time;
};

std::istream& operator>>(std::istream& is, Particle& p);

std::ostream& operator<<(std::ostream& os, const Particle& p);

}  // namespace hardsphere

#endif  // HARDSPHERE_PARTICLE_HPP