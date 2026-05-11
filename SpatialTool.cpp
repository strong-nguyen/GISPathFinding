#include "SpatialTool.h"


double gis::calculateDistance(const Point2D& p1, const Point2D& p2)
{
  boost_point boost_p1(p1.lon, p1.lat);
  boost_point boost_p2(p2.lon, p2.lat);

  return bg::distance(boost_p1, boost_p2);
}
