#pragma once

#include <iostream>


namespace geo {

struct Vector3d;

struct Point3d {
public:
    Point3d(double x = 0, double y = 0, double z = 0);
    double x = 0;
    double y = 0;
    double z = 0;
};

Vector3d operator-(const Point3d&a, const Point3d& b);

Point3d operator+(const Point3d& p, const Vector3d& v);

std::ostream& operator<<(std::ostream&, const Point3d&);

}