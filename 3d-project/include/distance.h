#include "point_3d.h"
#include "segment_3d.h"

namespace geo {

double distance(const Point3d& a, const Point3d& b);
double distance(const Point3d& a, const Segment3d& b);
double distance(const Segment3d& s1, const Segment3d& s2);

}