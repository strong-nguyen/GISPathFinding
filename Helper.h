#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace helper
{
  void trimLeft(std::string& str);

  void trimRight(std::string& str);

  void trim(std::string& str);

  std::vector<std::string> splitString(const std::string& str, const std::string& delimeter);


  class Stopwatch
  {
  public:
    Stopwatch();

    void start();

    void stop();

    template <typename T>
    long long elapsedTime() const
    {
      return std::chrono::duration_cast<T>(_elapsedTime).count();
    }

  private:
    std::chrono::steady_clock::time_point _startTime;
    std::chrono::steady_clock::duration _elapsedTime;
    bool _isStart = false;
  };
}
