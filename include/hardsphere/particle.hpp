#ifndef HARDSPHERE_PARTICLE_HPP
#define HARDSPHERE_PARTICLE_HPP

#include "hardsphere/vector2d.hpp"

namespace hardsphere {

struct particle {
  vector2d position;
  vector2d velocity;
  double radius;
  double mass;

  particle() = default;
  particle(const vector2d& t_position, const vector2d& t_velocity,
           double t_radius, double t_mass)
      : position{t_position},
        velocity{t_velocity},
        radius{t_radius},
        mass{t_mass} {}
  particle(const particle&) = default;
  particle(particle&&) = default;

  particle& operator=(const particle&) = default;
  particle& operator=(particle&&) = default;
};

inline std::istream& operator>>(std::istream& is, particle& p) {
  return is >> p.position >> p.velocity >> p.radius >> p.mass;
}

inline std::ostream& operator<<(std::ostream& os, const particle& p) {
  return os << p.position << ' ' << p.velocity << ' ' << p.radius << ' '
            << p.mass;
}

}  // namespace hardsphere

#endif  // HARDSPHERE_PARTICLE_HPP