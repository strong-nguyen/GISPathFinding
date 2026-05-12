#include <iostream>
#include <vector>
#include <format>


#include "OSMLoader.h"
#include "PathFinding.h"
#include "GeoJSONWriter.h"
#include "BoostRTree.h"
#include "Helper.h"


void parseArgs(char** argv, std::string& osmFile, Point2D& startPoint, Point2D& endPoint)
{
  osmFile = argv[1];

  std::string startPointStr = argv[2];
  std::string endPointStr = argv[3];

  for (int i = 2; i < 4; ++i)
  {
    std::string pointStr = argv[i];
    auto tokens = helper::splitString(pointStr, ",");
    if (tokens.size() != 2)
    {
      continue;
    }

    helper::trim(tokens[0]);
    helper::trim(tokens[1]);
    if (i == 2)
    {
      startPoint = { std::stod(tokens[0]), std::stod(tokens[1]) };
    }
    else if (i == 3)
    {
      endPoint = { std::stod(tokens[0]), std::stod(tokens[1]) };
    }
  }
}

int main(int argc, char** argv)
{
  if (argc < 4)
  {
    std::cout << "Usage: GISPathFinding.exe path-to-osm-data lat1,lon1 lat2,lon2\n";
    return 1;
  }

  std::string osmFile = argv[1];

  Point2D startPoint;
  Point2D endPoint;
  parseArgs(argv, osmFile, startPoint, endPoint);


  // Build node map
  std::unordered_map<long long, Point2D> nodeMap;

  std::cout << "Start loading node coordinates and build graph" << std::endl;
  helper::Stopwatch stopwatch;
  OSMLoader loader(osmFile);
  loader.buildNodeMap(nodeMap);

  // Build Adjacency List
  std::unordered_map<long long, std::vector<Edge>> graph;
  loader.buildAdjacencyList(graph, nodeMap);

  stopwatch.stop();
  std::cout << std::format("Load OSM and build graph completed after {} s\n\n", stopwatch.elapsedTime<std::chrono::seconds>());

  // Find the shortest path with AStart algorithm
  AStar pathFinder(&nodeMap, &graph);

  BoostRTree rtree;
  rtree.bulkInsert(nodeMap);

  long long startId = rtree.findNearestNode(startPoint);
  long long endId = rtree.findNearestNode(endPoint);

  if (startId == -1 || endId == -1)
  {
    std::cerr << std::format("Failed to find nearest point, startId: {}, endId: {}\n", startId, endId);
    return 1;
  }

  std::cout << "start node id: " << startId << ", end node id: " << endId << std::endl;

  std::cout << "Finding shortest path using A* algorithm" << std::endl;
  stopwatch.start();

  auto paths = pathFinder.findPath(startId, endId);

  stopwatch.stop();
  std::cout << std::format("Find shortest path completed after {} ms\n\n", stopwatch.elapsedTime<std::chrono::milliseconds>());

  if (paths.empty())
  {
    std::cout << "Failed to find the shortest path using A* algorithm" << std::endl;
    return 1;
  }

  std::cout << "Shortest distance between start and end point: " << pathFinder.getShortestDistance() << "m\n";

  std::vector<Point2D> line;
  for (long long id : paths)
  {
    line.push_back(nodeMap[id]);
  }

  // Export paths to geojson file to visualize it on the map
  GeoJSONWriter writer;
  writer.addPointFeature(line.front(), { {"pointType", "startPoint"} });
  writer.addPointFeature(line.back(), { {"pointType", "endPoint"} });
  writer.addLineStringFeature(line);
  writer.write("paths.geojson");
  std::cout << "Exported to paths.geojson" << std::endl;
} 