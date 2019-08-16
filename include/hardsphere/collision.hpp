#ifndef HARDSPHERE_COLLISION_HPP
#define HARDSPHERE_COLLISION_HPP

#include <optional>
#include "hardsphere/particle.hpp"

namespace hardsphere {

/// @brief Computes collsion time of two particles
/// @param[in] x1 Position of particle 1
/// @param[in] v1 Velocity of particle 1
/// @param[in] a1 Radius of particle 1
/// @param[in] x2 Position of particle 2
/// @param[in] v2 Velocity of particle 2
/// @param[in] a2 Radius of particle 2
/// @return Collision time
std::optional<double> collision_time(const vector2d& x1, const vector2d& v1,
                                     double a1, const vector2d& x2,
                                     const vector2d& v2, double a2);

/// @brief Computes collision time of two particles
/// @param[in] p1 Particle 1
/// @param[in] p2 Particle 2
/// @return Collision time
inline std::optional<double> collision_time(const particle& p1,
                                            const particle& p2) {
  return collision_time(p1.position, p1.velocity, p1.radius, p2.position,
                        p2.velocity, p2.radius);
}

}  // namespace hardsphere

#endif  // HARDSPHERE_COLLISION_HPP