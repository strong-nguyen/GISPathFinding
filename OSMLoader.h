#pragma once

#include "CoreFeature.h"

#include <string>
#include <unordered_map>
#include <pugixml.hpp>


class OSMLoader
{
public:
  OSMLoader(const std::string& osmFile);

  void buildNodeMap(std::unordered_map<long long, Point2D>& nodeMap);

  void buildAdjacencyList(std::unordered_map<long long, std::vector<Edge>>& graph, const std::unordered_map<long long, Point2D>& nodeMap);

private:
  std::string _osmFile;

  pugi::xml_node _root;
  pugi::xml_document _doc;
};