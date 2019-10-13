#include "hardsphere/logging.hpp"
#include <cassert>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace hardsphere {

namespace {

std::string getFormattedLocalTime(const char* fmt) {
  using std::chrono::system_clock;
  auto t = system_clock::now();
  auto tc = system_clock::to_time_t(t);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&tc), fmt);
  return ss.str();
}

std::string getLogLevelName(LogLevel level) {
  switch (level) {
    case LogLevel::off:
      return "off";
    case LogLevel::fatal:
      return "fatal";
    case LogLevel::error:
      return "error";
    case LogLevel::warn:
      return "warn";
    case LogLevel::info:
      return "info";
    case LogLevel::debug:
      return "debug";
    case LogLevel::trace:
      return "trace";
    default:
      assert(false);
      return "";
  }
}

std::string getLogPrefix(LogLevel level, const char* tag) {
  std::stringstream ss;
  switch (level) {
    case LogLevel::off:
      ss << "[OFF] ";
      break;
    case LogLevel::error:
      ss << "[ERROR] ";
      break;
    case LogLevel::fatal:
      ss << "[FATAL] ";
      break;
    case LogLevel::warn:
      ss << "[WARN] ";
      break;
    case LogLevel::info:
      ss << "[INFO] ";
      break;
    case LogLevel::debug:
      ss << "[DEBUG] ";
      break;
    case LogLevel::trace:
      ss << "[TRACE] ";
      break;
    default:
      ss << "[UNKNOWN] ";
      break;
  }

  ss << getFormattedLocalTime("%Y-%m-%d, %H:%M:%S") << ' ' << tag << ' ';

  return ss.str();
}

std::shared_ptr<std::ofstream> makeDefaultLogFile(
    const std::string& filenamePrefix) {
  std::string filename =
      filenamePrefix + '_' + getFormattedLocalTime("%Y%m%d-%H%M%S") + ".log";
  return std::make_shared<std::ofstream>(filename,
                                         std::ios::out | std::ios::app);
}

std::shared_ptr<Logger>& getHardsphereLogger() {
  static std::shared_ptr<Logger> logger{nullptr};
  return logger;
}

}  // anonymous namespace

Logger::Logger(LogLevel level, const std::string& filenamePrefix)
    : level_{level}, log_file_{makeDefaultLogFile(filenamePrefix)} {}

void Logger::log(LogLevel level, const char* tag, const char* msg) {
  std::stringstream ss;
  ss << getLogPrefix(level, tag) << ' ' << msg;
  (*log_file_) << ss.str() << '\n';
}

void Logger::log(LogLevel level, const char* tag,
                 const std::ostringstream& msg) {
  (*log_file_) << getLogPrefix(level, tag) << ' ' << msg.str() << '\n';
}

void setLogger(const std::shared_ptr<Logger>& logger) {
  getHardsphereLogger() = logger;
}

void closeLogger() { getHardsphereLogger() = nullptr; }

Logger* getLogger() { return getHardsphereLogger().get(); }

}  // namespace hardsphere