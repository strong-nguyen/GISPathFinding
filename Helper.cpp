#include "Helper.h"

void helper::trimLeft(std::string& str)
{
  if (str.empty())
  {
    return;
  }

  std::size_t i = 0;
  while (str[i] == ' ')
  {
    ++i;
  }

  if (i > 0)
  {
    str.erase(0, i);
  }
}

void helper::trimRight(std::string& str)
{
  if (str.empty())
  {
    return;
  }

  std::size_t i = str.size() - 1;
  while (str[i] == ' ')
  {
    --i;
  }

  if (i < str.size() - 1)
  {
    str.erase(i + 1);
  }
}

void helper::trim(std::string& str)
{
  trimLeft(str);
  trimRight(str);
}

std::vector<std::string> helper::splitString(const std::string& str, const std::string& delimeter)
{
  if (str.empty() || delimeter.empty())
  {
    return {};
  }

  std::vector<std::string> tokens;
  std::size_t start = 0;
  std::size_t found = 0;
  do
  {
    found = str.find(delimeter, start);
    if (found != std::string::npos)
    {
      std::string token = str.substr(start, found - start);
      if (!token.empty())
      {
        tokens.push_back(token);
      }
    }
    else
    {
      break;
    }

    start = found + delimeter.length();
  } while (true);

  if (start < str.size())
  {
    std::string token = str.substr(start);
    if (!token.empty())
    {
      tokens.push_back(token);
    }
  }

  return tokens;
}

helper::Stopwatch::Stopwatch()
{
  start();
  _isStart = true;
}

void helper::Stopwatch::start()
{
  if (!_isStart)
  {
    _startTime = std::chrono::steady_clock::now();
  }
}

void helper::Stopwatch::stop()
{
  _elapsedTime = std::chrono::steady_clock::now() - _startTime;
  _isStart = false;
}
