#include "hardsphere/logging.hpp"
#include <catch2/catch.hpp>

using namespace hardsphere;

TEST_CASE("logging unit tests", "[Logger]") {
  auto logger = std::make_shared<Logger>(LogLevel::debug, "test");
  setLogger(logger);

  HS_LOG_DEBUG("logging test", "fatal msg");

  closeLogger();
}