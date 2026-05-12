#pragma once

#include "BoostDefine.h"
#include "CoreFeature.h"

#include <unordered_map>

class BoostRTree
{
public:
  void bulkInsert(const std::unordered_map<long long, Point2D>& nodeMap);

  long long findNearestNode(const Point2D& inputPoint);

private:
  typedef std::pair<boost_point_xy, long long> value;  // Because boost geometry use the first value as geometry feature
  bgi::rtree<value, bgi::quadratic<16>> _rtree;
};