#include "logger.hpp"
#include <iostream>
#include <ctime>

std::vector<LogEntry> Logger::engineLog;
// static char TIME_BUF[60] = {}; // not thread-safe

// Source - https://stackoverflow.com/a/54062826
// Posted by Mehdi Mohammadpour, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-19, License - CC BY-SA 4.0

char const RESET[] = "\033[0m";
char const RED_TEXT[] = "\x1B[31m";
char const GREEN_TEXT[] = "\x1B[32m";
char const YELLOW_TEXT[] = "\x1B[33m";
char const BRIGHT_RED_TEXT[] = "\x1B[91m";

// Name            FG  BG
// Black           30  40
// Red             31  41
// Green           32  42
// Yellow          33  43
// Blue            34  44
// Magenta         35  45
// Cyan            36  46
// White           37  47
// Bright Black    90  100
// Bright Red      91  101
// Bright Green    92  102
// Bright Yellow   93  103
// Bright Blue     94  104
// Bright Magenta  95  105
// Bright Cyan     96  106
// Bright White    97  107

std::unique_ptr<char[]> makeTimeString() {
  time_t myTime;
  time(&myTime);
  struct tm timeStruct;
  localtime_s(&timeStruct, &myTime);

  int const bufSize = 24;
  std::unique_ptr<char[]> buf = std::make_unique<char[]>(bufSize);
  strftime(buf.get(), bufSize, "%d.%m.%y %H:%M:%S ", &timeStruct);

  return buf;
}

void Logger::Log(std::string const & a) {
  std::unique_ptr<char[]> buf = makeTimeString();

  LogEntry entry;
  entry.message = std::string("[I] ") + std::string(buf.get()) + a;
  entry.type = EntryType::Info;
  engineLog.push_back(entry);

  std::cout << GREEN_TEXT << entry.message << RESET << std::endl;
}

void Logger::Error(std::string const & a) {
  std::unique_ptr<char[]> buf = makeTimeString();

  LogEntry entry;
  entry.message = std::string("[E] ") + std::string(buf.get()) + a;
  entry.type = EntryType::Error;
  engineLog.push_back(entry);

  std::cerr << RED_TEXT << entry.message << RESET << std::endl;
}

void Logger::Warning(std::string const & a) {
  std::unique_ptr<char[]> buf = makeTimeString();

  LogEntry entry;
  entry.message = std::string("[W] ") + std::string(buf.get()) + a;
  entry.type = EntryType::Warning;
  engineLog.push_back(entry);

  std::cout << YELLOW_TEXT << entry.message << RESET << std::endl;
}

void Logger::Fatal(std::string const &a) {
  std::unique_ptr<char[]> buf = makeTimeString();

  LogEntry entry;
  entry.message = std::string("[F] ") + std::string(buf.get()) + a;
  entry.type = EntryType::Fatal;
  engineLog.push_back(entry);

  std::cerr << BRIGHT_RED_TEXT << entry.message << RESET << std::endl;
}
