#pragma once

#include <point_3d.h>

namespace geo {

    struct Segment3d {
    public:
        Segment3d(const Point3d& a, const Point3d& b);
        
        Point3d a;
        Point3d b;
    };

}