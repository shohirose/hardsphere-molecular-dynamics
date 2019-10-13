#ifndef HARDSPHERE_COLLISION_HPP
#define HARDSPHERE_COLLISION_HPP

#include <optional>
#include "hardsphere/particle.hpp"

namespace hardsphere {

/// Computes collision time of two particles
std::optional<double> calcCollisionTime(const Particle& p1,
                                        const Particle& p2) noexcept;

/// Collides two particles to modify their position, velocity, and intrinsic
/// time.
void collide(Particle& p1, Particle& p2, double tc) noexcept;

}  // namespace hardsphere

#endif  // HARDSPHERE_COLLISION_HPP