#include <point_3d.h>
#include <vector_3d.h>

namespace geo {

    Point3d::Point3d(double x, double y, double z) : x(x), y(y), z(z)
    {

    }

    Vector3d operator-(const Point3d&a, const Point3d& b)
    {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }
    
    Point3d operator+(const Point3d& p, const Vector3d& v)
    {
        return {p.x + v.x, p.y + v.y, p.z + v.z};
    }
}