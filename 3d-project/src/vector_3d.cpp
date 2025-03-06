#include <vector_3d.h>

#include <cmath>

namespace geo {

    Vector3d::Vector3d(double x, double y, double z) : x(x), y(y), z(z)
    {

    }

    double abs_squared(const Vector3d& v) 
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }
        
    double abs(const Vector3d& v) 
    {
        return std::sqrt(abs_squared(v));
    }

    Vector3d cross_product(const Vector3d& a, const Vector3d& b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }

    double dot_product(const Vector3d& a, const Vector3d& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vector3d operator*(double alpha, const Vector3d& a)
    {
        return {alpha * a.x, alpha * a.y, alpha * a.z};
    }

    std::ostream& operator<<(std::ostream& oss, const Vector3d& v)
    {
        oss << v.x << " " << v.y << " " << v.z << " ";
        return oss;
    }
}