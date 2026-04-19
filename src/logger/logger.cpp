#include "logger.hpp"
#include <iostream>
#include <time.h>

// Source - https://stackoverflow.com/a/54062826
// Posted by Mehdi Mohammadpour, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-19, License - CC BY-SA 4.0

char const RESET[] = "\033[0m";
char const RED_TEXT[] = "\x1B[31m";
char const GREEN_TEXT[] = "\x1B[32m";

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

void Logger::Log(std::string const & a) {
  time_t myTime;
  time(&myTime);
  struct tm timeStruct;
  int const bufSize = 40;
  char buf[bufSize] = {};
  gmtime_s(&timeStruct, &myTime);
  strftime(buf, bufSize, "%d.%m.%y %H:%M:%S ", &timeStruct);
  std::cout << GREEN_TEXT << "[I] " << buf << a << RESET << std::endl;
}

void Logger::Error(std::string const & a) {
  time_t myTime;
  time(&myTime);
  struct tm timeStruct;
  int const bufSize = 40;
  char buf[bufSize] = {};
  gmtime_s(&timeStruct, &myTime);
  strftime(buf, bufSize, "%d.%m.%y %H:%M:%S ", &timeStruct);
  std::cerr << RED_TEXT << "[E] " << buf << a << RESET << std::endl;
}
