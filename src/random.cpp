#include "hardsphere/random.hpp"
#include <algorithm>
#include <array>
#include <functional>

namespace hardsphere {

namespace {

using SeedArray =
    std::array<std::random_device::result_type, std::mt19937::state_size>;

SeedArray createSeeds() {
  std::random_device rnd;
  SeedArray seeds;
  std::generate(seeds.begin(), seeds.end(), std::ref(rnd));
  return seeds;
}

std::mt19937 createRandomEngine() {
  const auto seeds = createSeeds();
  std::seed_seq seq(seeds.begin(), seeds.end());
  return std::mt19937(seq);
}

}  // anonymous namespace

std::mt19937& getRandomEngine() {
  static thread_local auto engine = createRandomEngine();
  return engine;
}

}  // namespace hardsphere