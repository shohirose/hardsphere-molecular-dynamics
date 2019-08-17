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
std::optional<double> collision_time(                   //
    const vector2d& x1, const vector2d& v1, double a1,  //
    const vector2d& x2, const vector2d& v2, double a2);

/// @brief Computes collision time of two particles
/// @param[in] p1 Particle 1
/// @param[in] p2 Particle 2
/// @return Collision time
inline std::optional<double> collision_time(const particle& p1,
                                            const particle& p2) {
  return collision_time(p1.position, p1.velocity, p1.radius,  //
                        p2.position, p2.velocity, p2.radius);
}

/// @brief Computes new particle position
/// @param[in] x Particle position
/// @param[in] v Particle velocity
/// @param[in] t Time to proceed
/// @return New particle position
inline vector2d new_position(const vector2d& x, const vector2d& v, double t) {
  return x + v * t;
}

/// @brief Update the position and velocity of two colliding particles by
/// assuming elastic collision
/// @param[in] x1 Position of particle 1
/// @param[in] v1 Velocity of particle 1
/// @param[in] m1 Mass of particle 1
/// @param[in] x2 Position of particle 2
/// @param[in] v2 Velocity of particle 2
/// @param[in] m2 Mass of particle 2
/// @param[in] tc Collision time
void collide(vector2d& x1, vector2d& v1, double m1,  //
             vector2d& x2, vector2d& v2, double m2,  //
             double tc);

/// @brief Update the position and velocity of two colliding particles
/// @param[in] p1 Particle 1
/// @param[in] p2 Particle 2
/// @param[in] tc Collision time
inline void collide(particle& p1, particle& p2, double tc) {
  collide(p1.position, p1.velocity, p1.mass,  //
          p2.position, p2.velocity, p2.mass,  //
          tc);
}

}  // namespace hardsphere

#endif  // HARDSPHERE_COLLISION_HPP