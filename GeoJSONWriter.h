#pragma once

#include "CoreFeature.h"

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>


class GeoJSONWriter
{
public:
  GeoJSONWriter();

  void write(const std::string& geoJSONFile);

  void addLineStringFeature(const std::vector<Point2D>& points);

  void addPointFeature(const Point2D& point, const std::map<std::string, std::string>& properties = {});

private:
  nlohmann::json _root;
};