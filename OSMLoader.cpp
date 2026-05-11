#include "OSMLoader.h"
#include "SpatialTool.h"

#include <pugixml.hpp>
#include <iostream>

OSMLoader::OSMLoader(const std::string& osmFile)
  :
  _osmFile(osmFile)
{
  _doc.load_file(_osmFile.c_str());
  _root = _doc.child("osm");
}

void OSMLoader::buildNodeMap(std::unordered_map<long long, Point2D>& nodeMap)
{
  for (pugi::xml_node node : _root.children("node"))
  {
    long long id = node.attribute("id").as_llong();
    double lat = node.attribute("lat").as_double();
    double lon = node.attribute("lon").as_double();

    nodeMap[id] = Point2D{ lat, lon };
  }
}

void OSMLoader::buildAdjacencyList(std::unordered_map<long long, std::vector<Edge>>& graph, const std::unordered_map<long long, Point2D>& nodeMap)
{
  for (pugi::xml_node way : _root.children("way"))
  {
    // Collect all node id belong to this way
    std::vector<long long> way_nodes;
    for (pugi::xml_node nd : way.children("nd"))
    {
      way_nodes.push_back(nd.attribute("ref").as_llong());
    }

    // Create edge between consecutive nodes
    for (std::size_t i = 0; i < way_nodes.size() - 1; ++i)
    {
      long long u = way_nodes[i];
      long long v = way_nodes[i + 1];

      // Calculate distance between u and v using Haversine formula
      double dist = gis::calculateDistance(nodeMap.at(u), nodeMap.at(v));

      // Add edge u -> v
      graph[u].push_back({ v, dist });

      // Add edge v -> u (two-way street)
      graph[v].push_back({ u, dist });
    }
  }
}
