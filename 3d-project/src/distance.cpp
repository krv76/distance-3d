#include <distance.h>

#include <constants.h>
#include <point_3d.h>
#include <vector_3d.h>
#include <segment_3d.h>

#include <algorithm>
#include <cmath>

namespace geo {
double distance(const Point3d& a, const Point3d& b)
{
    return abs(b - a);
}

double distance(const Point3d& p, const Segment3d& s)
{
    if (dot_product(s.a - p, s.a - s.b) > 0 && dot_product(s.b - p, s.b - s.a) > 0)
    {
        const double triangle_height = abs(cross_product(s.a - p, s.b - p)) / distance(s.a, s.b);
        return triangle_height;
    }
    // std::cout << dot_product(s.a - p, s.a - s.b) << "\n";
    // std::cout << dot_product(s.b - p, s.b - s.a) << "\n";
    const double bounds_dist = std::min(distance(p, s.a), distance(p, s.b));
    return bounds_dist;
}

namespace {
double min_distance_end_to_segment(const Segment3d& s1, const Segment3d& s2)
{
    const double r1 = distance(s1.a, s2);
    const double r2 = distance(s1.b, s2);
    const double r3 = distance(s2.a, s1);
    const double r4 = distance(s2.b, s1);
    // std::cout << r1 << " " << r2 << " " << r3 << " " << r4 << " " << "\n";
    return std::min(r1, std::min(r2, std::min(r3, r4)));
}

Vector3d double_oriented_triangle_area(const Segment3d& s, const Point3d& p)
{
    return cross_product(p - s.a, s.b - s.a);
}

double sqr(double a) {
    return a * a;
}
}

double distance(const Segment3d& s1, const Segment3d& s2)
{
    const auto normal = cross_product(s1.b - s1.a, s2.b - s2.a);
    if (abs(normal) < default_tolerance) {
        return min_distance_end_to_segment(s1, s2);
    }
    /* неколлинеарный случай
        Найдем вектор ортогональный обоим отрезкам vn
        сдвинем s2 на него
        проверим отрезки на пересечение
        если отрезки пересеаются - расстояние между ними теперь ноль, вернем vn
        иначе найдем минимум из расстояний от конца отрезка до другого отрезка
        по т. Пифагора найдем результат
    */
    const Vector3d shift = dot_product(s1.a - s2.a, normal) / dot_product(normal, normal) * normal;
    const Segment3d shifted_s2{s2.a + shift, s2.b + shift};
    
    const Vector3d double_oriented_triangle_from_s1_a = double_oriented_triangle_area(shifted_s2, s1.a);
    const Vector3d double_oriented_triangle_from_s1_b = double_oriented_triangle_area(shifted_s2, s1.b);
    const Vector3d double_oriented_triangle_from_s2_a = double_oriented_triangle_area(s1, shifted_s2.a);
    const Vector3d double_oriented_triangle_from_s2_b = double_oriented_triangle_area(s1, shifted_s2.b);
    if (dot_product(double_oriented_triangle_from_s1_a, double_oriented_triangle_from_s1_b) < 0
        && dot_product(double_oriented_triangle_from_s2_a, double_oriented_triangle_from_s2_b) < 0)
    {
        return abs(shift);
    }
    return std::sqrt(sqr(min_distance_end_to_segment(s1, shifted_s2)) + abs_squared(shift));
}

}