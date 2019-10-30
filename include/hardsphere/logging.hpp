#ifndef HARDSPHERE_LOGGING_HPP
#define HARDSPHERE_LOGGING_HPP

#include <fstream>
#include <memory>
#include <string>

namespace hardsphere {

enum class LogLevel : int { off, fatal, error, warn, info, debug, trace };

/// @brief Returns log level name in CAPITALS.
std::string getLogLevelName(LogLevel level);

class Logger {
 public:
  /// @brief Construct a logger
  /// @param[in] level Log level
  /// @param[in] filenamePrefix File name prefix
  ///
  /// A log file whose name is "<filenamePrefix>.log" will be created.
  Logger(LogLevel level, const std::string& filenamePrefix);

  Logger(LogLevel level, const std::shared_ptr<std::ofstream>& logFile);

  auto level() const noexcept { return level_; }

  void log(LogLevel level, const char* tag, const char* msg);
  void log(LogLevel level, const char* tag, const std::ostringstream& msg);

 private:
  LogLevel level_;
  std::shared_ptr<std::ofstream> logFile_;
};

/// @brief Returns local time in a specified format.
/// @param[in] fmt Format
///
/// The format specifiers can be found in <a
/// href="https://ja.cppreference.com/w/cpp/io/manip/put_time">cppreference.com:
/// std::put_time</a>
std::string getFormattedLocalTime(const char* fmt);

void setLogger(const std::shared_ptr<Logger>& logger);

void closeLogger();

Logger* getLogger();

#ifdef HS_DISABLE_LOG

#define HS_LOG(level, tag, msg)
#define HS_LOG_FATAL(level, tag, msg)
#define HS_LOG_ERROR(level, tag, msg)
#define HS_LOG_WARN(level, tag, msg)
#define HS_LOG_INFO(level, tag, msg)
#define HS_LOG_DEBUG(level, tag, msg)
#define HS_LOG_TRACE(level, tag, msg)

#else

#define HS_LOG(tLevel, tag, msg)               \
  {                                            \
    auto logger = getLogger();                 \
    if (logger && logger->level() >= tLevel) { \
      logger->log(tLevel, tag, msg)            \
    }                                          \
  }

#define HS_LOG_FATAL(tag, msg)                          \
  {                                                     \
    auto logger = getLogger();                          \
    if (logger && logger->level() >= LogLevel::fatal) { \
      logger->log(LogLevel::fatal, tag, msg)            \
    }                                                   \
  }

#define HS_LOG_ERROR(tag, msg)                          \
  {                                                     \
    auto logger = getLogger();                          \
    if (logger && logger->level() >= LogLevel::error) { \
      logger->log(LogLevel::error, tag, msg);           \
    }                                                   \
  }

#define HS_LOG_WARN(tag, msg)                          \
  {                                                    \
    auto logger = getLogger();                         \
    if (logger && logger->level() >= LogLevel::warn) { \
      logger->log(LogLevel::warn, tag, msg);           \
    }                                                  \
  }

#define HS_LOG_INFO(tag, msg)                          \
  {                                                    \
    auto logger = getLogger();                         \
    if (logger && logger->level() >= LogLevel::info) { \
      logger->log(LogLevel::info, tag, msg);           \
    }                                                  \
  }

#define HS_LOG_DEBUG(tag, msg)                          \
  {                                                     \
    auto logger = getLogger();                          \
    if (logger && logger->level() >= LogLevel::debug) { \
      logger->log(LogLevel::debug, tag, msg);           \
    }                                                   \
  }

#define HS_LOG_TRACE(tag, msg)                          \
  {                                                     \
    auto logger = getLogger();                          \
    if (logger && logger->level() >= LogLevel::trace) { \
      logger->log(LogLevel::trace, tag, msg);           \
      ;                                                 \
    }                                                   \
  }

#endif  // HS_DISABLE_LOG

}  // namespace hardsphere

#endif  // HARDSPHERE_LOGGING_HPP