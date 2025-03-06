#include <gtest/gtest.h>
#include <point_3d.h>

using namespace geo;

TEST(Point3dTest, creation) {
    Point3d point;
    EXPECT_EQ(point.x, 0.);
    EXPECT_EQ(point.y, 0.);
    EXPECT_EQ(point.z, 0.);
}
