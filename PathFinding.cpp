#include "PathFinding.h"
#include "SpatialTool.h"

#include <queue>

AStar::AStar(const std::unordered_map<long long, Point2D>* nodeMap, const std::unordered_map<long long, std::vector<Edge>>* graph)
  :
  _nodeMap(nodeMap),
  _graph(graph)
{
}

std::vector<long long> AStar::findPath(long long start, long long goal)
{
  // Priority queue to store nodes to explore
  std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;

  // track the best gScore found so far for each node
  std::unordered_map<long long, double> gScore;

  // track where we came from to reconstruct the path later
  std::unordered_map<long long, long long> cameFrom;

  // Initialize
  gScore[start] = 0;
  openSet.push({ start, gis::calculateDistance(_nodeMap->at(start), _nodeMap->at(goal)) });

  while (!openSet.empty())
  {
    long long current = openSet.top().id;
    openSet.pop();

    // Check if we reached the goal
    if (current == goal) {
      return reconstructPath(cameFrom, current);
    }

    // Explorer neighbor
    for (const auto& edge : _graph->at(current))
    {
      double tentative_gScore = gScore[current] + edge.weight;
      if (gScore.find(edge.to) == gScore.end() || tentative_gScore < gScore[edge.to]) {
        cameFrom[edge.to] = current;
        gScore[edge.to] = tentative_gScore;
        double fScore = tentative_gScore + gis::calculateDistance(_nodeMap->at(edge.to), _nodeMap->at(goal));
        openSet.push({ edge.to, fScore });
      }
    }
  }

  return {}; // No path found
}

std::vector<long long> AStar::reconstructPath(std::unordered_map<long long, long long>& cameFrom, long long current)
{
  std::vector<long long> totalPath = { current };
  while (cameFrom.find(current) != cameFrom.end()) {
    current = cameFrom[current];
    totalPath.push_back(current);
  }
  std::reverse(totalPath.begin(), totalPath.end());
  return totalPath;
}
