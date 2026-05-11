#pragma once


struct Edge
{
  long long to;
  double weight; // Distance in meters
};


struct Point2D
{
  double lat = 0.0;
  double lon = 0.0;
};