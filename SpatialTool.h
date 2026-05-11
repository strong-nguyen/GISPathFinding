#pragma once

#include "CoreFeature.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>

namespace bg = boost::geometry;
typedef bg::model::point<double, 2, bg::cs::geographic<bg::degree>> boost_point;

namespace gis
{
  double calculateDistance(const Point2D& p1, const Point2D& p2);
}