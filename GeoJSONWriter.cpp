#include "GeoJSONWriter.h"

#include <fstream>
#include <iostream>

GeoJSONWriter::GeoJSONWriter()
{
  _root["type"] = "FeatureCollection";
}

void GeoJSONWriter::write(const std::string& geoJSONFile)
{
  std::ofstream f(geoJSONFile);
  if (!f)
  {
    std::cerr << "Failed to write to " << geoJSONFile << std::endl;
    return;
  }

  f << _root.dump(4);
}

void GeoJSONWriter::addLineStringFeature(const std::vector<Point2D>& points)
{
  nlohmann::json feature;
  feature["type"] = "Feature";

  nlohmann::json geometry;
  geometry["type"] = "LineString";
  for (const auto& point : points)
  {
    nlohmann::json arr;
    arr.push_back(point.lon);
    arr.push_back(point.lat);
    geometry["coordinates"].push_back(arr);
  }
  feature["geometry"] = geometry;
  feature["properties"] = nlohmann::json::object();

  _root["features"].push_back(feature);
}

void GeoJSONWriter::addPointFeature(const Point2D& point, const std::map<std::string, std::string>& properties /* = {}*/)
{
  nlohmann::json feature;
  feature["type"] = "Feature";

  nlohmann::json geometry;
  geometry["type"] = "Point";
  geometry["coordinates"] = nlohmann::json::array();
  geometry["coordinates"].push_back(point.lon);
  geometry["coordinates"].push_back(point.lat);

  feature["geometry"] = geometry;
  feature["properties"] = properties;

  _root["features"].push_back(feature);
}
