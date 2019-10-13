#ifndef HARDSPHERE_RANDOM_HPP
#define HARDSPHERE_RANDOM_HPP

#include <random>

namespace hardsphere {

std::mt19937& getRandomEngine();

}  // namespace hardsphere

#endif  // HARDSPHERE_RANDOM_HPP