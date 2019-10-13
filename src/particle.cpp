#include "hardsphere/particle.hpp"

namespace hardsphere {

std::istream& operator>>(std::istream& is, Particle& p) {
  return is >> p.position >> p.velocity >> p.radius >> p.mass >> p.time;
}

std::ostream& operator<<(std::ostream& os, const Particle& p) {
  return os << p.position << ' ' << p.velocity << ' ' << p.radius << ' '
            << p.mass << ' ' << p.time;
}

}  // namespace hardsphere