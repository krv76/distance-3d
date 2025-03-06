#include <gtest/gtest.h>
#include <constants.h>
#include <point_3d.h>
#include <vector_3d.h>
#include <distance.h>

#include <optional>
#include <random>

using namespace geo;

TEST(DistanceTest, point_to_point_distance) {
    EXPECT_NEAR(distance({0, 0, 0}, {1, 2, 2}), 3, default_tolerance);
    EXPECT_NEAR(distance({0, 0, 0}, {0, 5, 0}), 5, default_tolerance);
}

TEST(DistanceTest, point_to_segment_distance) {
    EXPECT_NEAR(distance({-12, 0, 0}, {{0, 4, 3}, {1, 4, 3}}), 13, default_tolerance);
    EXPECT_NEAR(distance({0, 0, 0}, {{0, 4, 3}, {1, 4, 3}}), 5, default_tolerance);
    EXPECT_NEAR(distance({1, 0, 0}, {{0, 4, 3}, {1, 4, 3}}), 5, default_tolerance);
    EXPECT_NEAR(distance({13, 0, 0}, {{0, 4, 3}, {1, 4, 3}}), 13, default_tolerance);
    EXPECT_NEAR(distance({12, 0, 0}, {{0, 4, 3}, {0, 4, 3}}), 13, default_tolerance);
    EXPECT_NEAR(distance({0, 0, 0}, {{3, -1, 0}, {3, 3, 0}}), 3, default_tolerance);
}

constexpr int grid_size = 10;
void segment_to_segment_test_helper(const Segment3d& s1, const Segment3d& s2, std::optional<double> expected_distance,
    std::optional<double> distance_proximity_multiplier = {})
{
    const double calculated_distance = distance(s1, s2);
    double search_calculated_distance = std::numeric_limits<double>::max();
    for (int i = 0; i <= grid_size; ++i)
    {
        for (int j = 0; j <= grid_size; ++j)
        {
            const Point3d point_on_s1 = s1.a + static_cast<double>(i) / grid_size * (s1.b - s1.a);
            const Point3d point_on_s2 = s2.a + static_cast<double>(j) / grid_size * (s2.b - s2.a);
            search_calculated_distance = std::min(search_calculated_distance, distance(point_on_s1, point_on_s2));
        }
    }
    EXPECT_GE(search_calculated_distance + default_tolerance, calculated_distance);
    if (distance_proximity_multiplier.has_value()) 
    {
        EXPECT_LE(search_calculated_distance, calculated_distance * distance_proximity_multiplier.value());
    }
    if (expected_distance.has_value())
    {
        EXPECT_NEAR(expected_distance.value(), calculated_distance, default_tolerance);
    }
}

TEST(DistanceTest, segment_to_segment_distance) {
    segment_to_segment_test_helper({{0, 0, 0}, {0, 1, 0}}, {{0, 0, 0}, {0, 1, 0}}, 0);
    segment_to_segment_test_helper({{0, 0, 0}, {0, 1, 0}}, {{0, 2, 0}, {0, 3, 0}}, 1);
    segment_to_segment_test_helper({{0, -3, 0}, {0, 3, 0}}, {{0, -2, 0}, {0, 2, 0}}, 0);

    segment_to_segment_test_helper({{0, 0, 0}, {0, 1, 0}}, {{2, 0, 0}, {2, 1, 0}}, 2);
    segment_to_segment_test_helper({{0, 0, 0}, {0, 1, 0}}, {{3, -1, 0}, {3, 3, 0}}, 3);
    segment_to_segment_test_helper({{0, 0, 0}, {0, 5, 0}}, {{2, 2, 0}, {2, 7, 0}}, 2);
    segment_to_segment_test_helper({{0, 4, 0}, {0, 5, 0}}, {{2, 2, 0}, {2, 7, 0}}, 2);
    
    segment_to_segment_test_helper({{0, -2, 0}, {0, 2, 0}}, {{4, -2, 0}, {4, 2, 0}}, 4);
    segment_to_segment_test_helper({{0, -2, 0}, {0, 2, 0}}, {{3, 0, 4}, {7, 0, 4}}, 5);
    segment_to_segment_test_helper({{0, 2, 0}, {0, 5, 0}}, {{2, 0, 1}, {5, 0, 1}}, 3);

}

// Tests if almost always algorithmically calcualted distance is not greater than calculated by search
// better than nothing
TEST(DistanceTest, segment_to_segment_randomized) {
    return;
    GTEST_SKIP();
    std::random_device r;
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(0, 2);
    
    for (size_t i = 0; i < 100000; ++i) 
    {
        const Segment3d s1{
            {normal_dist(e2), normal_dist(e2), normal_dist(e2)},
            {normal_dist(e2), normal_dist(e2), normal_dist(e2)} 
        };
        const Segment3d s2{
            {normal_dist(e2), normal_dist(e2), normal_dist(e2)},
            {normal_dist(e2), normal_dist(e2), normal_dist(e2)} 
        };
        segment_to_segment_test_helper(s1, s2, {});
    }
}
