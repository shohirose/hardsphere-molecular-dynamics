#include "hardsphere/logging.hpp"
#include <cassert>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace hardsphere {

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
      return "OFF";
    case LogLevel::fatal:
      return "FATAL";
    case LogLevel::error:
      return "ERROR";
    case LogLevel::warn:
      return "WARN";
    case LogLevel::info:
      return "INFO";
    case LogLevel::debug:
      return "DEBUG";
    case LogLevel::trace:
      return "TRACE";
    default:
      return "NONE";
  }
}

namespace {

std::string getLogPrefix(LogLevel level, const char* tag) {
  std::stringstream ss;
  ss << '[' << getLogLevelName(level) << "] ["
     << getFormattedLocalTime("%Y-%m-%d %H:%M:%S") << "] [" << tag << ']';
  return ss.str();
}

std::shared_ptr<Logger>& getHardsphereLogger() {
  static std::shared_ptr<Logger> logger;
  return logger;
}

std::shared_ptr<std::ofstream> makeLogFile(const std::string& filenamePrefix) {
  const std::string filename = filenamePrefix + ".log";
  return std::make_shared<std::ofstream>(filename,
                                         std::ios::out | std::ios::app);
}

}  // anonymous namespace

Logger::Logger(LogLevel level, const std::string& filenamePrefix)
    : level_{level}, logFile_{makeLogFile(filenamePrefix)} {}

Logger::Logger(LogLevel level, const std::shared_ptr<std::ofstream>& logFile)
    : level_{level}, logFile_{logFile} {}

void Logger::log(LogLevel level, const char* tag, const char* msg) {
  std::stringstream ss;
  ss << getLogPrefix(level, tag) << ' ' << msg;
  (*logFile_) << ss.str() << '\n';
}

void Logger::log(LogLevel level, const char* tag,
                 const std::ostringstream& msg) {
  (*logFile_) << getLogPrefix(level, tag) << ' ' << msg.str() << '\n';
}

void setLogger(const std::shared_ptr<Logger>& logger) {
  getHardsphereLogger() = logger;
}

void closeLogger() { getHardsphereLogger() = nullptr; }

Logger* getLogger() { return getHardsphereLogger().get(); }

}  // namespace hardsphere