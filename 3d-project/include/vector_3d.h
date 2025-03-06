#pragma once

#include <iostream>

namespace geo {

struct Vector3d {
public:
    Vector3d(double x = 0, double y = 0, double z = 0);

    double x = 0;
    double y = 0;
    double z = 0;
};

double abs(const Vector3d& v);
double abs_squared(const Vector3d& v);

Vector3d cross_product(const Vector3d& a, const Vector3d& b);
double dot_product(const Vector3d& a, const Vector3d& b);
Vector3d operator*(double alpha, const Vector3d& a);

std::ostream& operator<<(std::ostream&, const Vector3d&);
}