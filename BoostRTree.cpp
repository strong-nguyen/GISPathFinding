#include "BoostRTree.h"
#include "Helper.h"

#include <vector>
#include <format>

void BoostRTree::bulkInsert(const std::unordered_map<long long, Point2D>& nodeMap)
{
  std::vector<value> listNode;
  listNode.reserve(nodeMap.size());
  for (const auto& [id, point] : nodeMap)
  {
    listNode.push_back({ {point.lon, point.lat}, id });
  }

  std::cout << "Start insert node to rtree" << std::endl;
  helper::Stopwatch stopwatch;

  _rtree = bgi::rtree<value, bgi::quadratic<16>>(listNode.begin(), listNode.end());

  stopwatch.stop();
  std::cout << std::format("Insert {} points to rtree completed after {} ms\n\n", listNode.size(), stopwatch.elapsedTime<std::chrono::milliseconds>());
}

long long BoostRTree::findNearestNode(const Point2D& inputPoint)
{
  boost_point_xy queryPoint(inputPoint.lon, inputPoint.lat);
  std::vector<value> results;

  // Find the 1 nearest neighbor
  _rtree.query(bgi::nearest(queryPoint, 1), std::back_inserter(results));

  if (!results.empty()) {
    return results[0].second; // Returns the OSM Node ID
  }

  return -1;
}
