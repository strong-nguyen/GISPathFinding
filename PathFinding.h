#pragma once

#include "CoreFeature.h"

#include <vector>
#include <unordered_map>


struct AStarNode {
  long long id;
  double fScore; // gScore + hScore

  // Priority queue is a max-heap by default, so we flip the comparison 
  // to make it a min-heap (lowest fScore at the top).
  bool operator>(const AStarNode& other) const {
    return fScore > other.fScore;
  }
};


class AStar
{
public:
  AStar(const std::unordered_map<long long, Point2D>* nodeMap, const std::unordered_map<long long, std::vector<Edge>>* graph);
  std::vector<long long> findPath(long long start, long long goal);
  double getShortestDistance() const;

private:
  std::vector<long long> reconstructPath(std::unordered_map<long long, long long>& cameFrom, long long current);
  const std::unordered_map<long long, Point2D>* _nodeMap;
  const std::unordered_map<long long, std::vector<Edge>>* _graph;
  double _shortestDistance = 0.0;
};