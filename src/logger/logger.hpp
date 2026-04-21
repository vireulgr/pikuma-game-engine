#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <vector>
#include <string>

enum EntryType {
  Info,
  Warning,
  Error,
  Fatal
};

struct LogEntry {
  std::string message;
  EntryType type;
};

struct Logger {
  static std::vector<LogEntry> engineLog;

  static void Log(std::string const & a);
  static void Warning(std::string const & a);
  static void Error(std::string const &a);
  static void Fatal(std::string const &a);
};

#endif
