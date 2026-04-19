#include "logger.hpp"
#include <iostream>
#include <time.h>

void Logger::Log(std::string const & a) {
  time_t myTime;
  time(&myTime);
  struct tm * tmPtr = new struct tm;
  errno_t e = gmtime_s(tmPtr, &myTime);
  if (e) {
    std::cerr << "error " << e << std::endl;
  }

  std::cout << "[I] " << a << std::endl;
}
void Logger::Error(std::string const & a) {
  std::cerr << a << std::endl;
}
