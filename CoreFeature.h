#pragma once


#include <iostream>

struct Edge
{
  long long to;
  double weight; // Distance in meters
};


struct Point2D
{
  double lat = 0.0;
  double lon = 0.0;

  friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
  {
    out << "[" << point.lon << ", " << point.lat << "]";
    return out;
  }

};