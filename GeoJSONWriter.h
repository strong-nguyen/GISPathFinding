#pragma once

#include "CoreFeature.h"

#include <string>
#include <vector>
#include <nlohmann/json.hpp>


class GeoJSONWriter
{
public:
  GeoJSONWriter();

  void write(const std::string& geoJSONFile);

  void addLineStringFeature(const std::vector<Point2D>& points);

private:
  nlohmann::json _root;
};