#include <iostream>
#include <vector>


#include "OSMLoader.h"
#include "PathFinding.h"
#include "GeoJSONWriter.h"


int main(int argc, char** argv)
{
  const std::string osmFile = "data\\export.osm";

  // Build node map
  std::unordered_map<long long, Point2D> nodeMap;
  OSMLoader loader(osmFile);
  loader.buildNodeMap(nodeMap);

  // Build Adjacency List
  std::unordered_map<long long, std::vector<Edge>> graph;
  loader.buildAdjacencyList(graph, nodeMap);

  //findPath();

  AStar pathFinder(&nodeMap, &graph);
  auto paths = pathFinder.findPath(291005814, 366224278);

  std::vector<Point2D> line;
  for (long long id : paths)
  {
    line.push_back(nodeMap[id]);
  }

  GeoJSONWriter writer;
  writer.addLineStringFeature(line);
  writer.write("paths.geojson");
} 