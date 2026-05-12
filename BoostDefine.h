#pragma once

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
typedef bg::model::point<double, 2, bg::cs::geographic<bg::degree>> boost_point;
typedef bg::model::point<double, 2, bg::cs::cartesian> boost_point_xy;
