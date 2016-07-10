#include "gtest/gtest.h"
#include "../../Physics/Vector3.hpp"

//! NOT FINISHED

TEST(Vector3, ConstructionAndEqualityCheck) {

    // Doubles:
    Vector3<double> vd1(0, 0, 0); Vector3<double> vd2;
    EXPECT_TRUE(vd1 == vd2);
    Vector3<double> vd3(3.1, 0, 0); Vector3<double> vd4(0, -2.5, 0);
    Vector3<double> vd5(0, 0, -0.1);
    EXPECT_TRUE(vd1 != vd3);  EXPECT_TRUE(vd1 != vd4); EXPECT_TRUE(vd1 != vd5);

    // Integers:
    Vector3<int> vi1(0, 0, 0); Vector3<int> vi2;
    EXPECT_TRUE(vi1 == vi2);
    Vector3<int> vi3(3, 0, 0); Vector3<int> vi4(0, -2, 0);
    Vector3<int> vi5(0, 0, -1);
    EXPECT_TRUE(vi1 != vi3);  EXPECT_TRUE(vi1 != vi4); EXPECT_TRUE(vi1 != vi5);
}

class Vector3MathTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        vd1 = Vector3<double>(0.5, 2.0, 4.0);
        vd2 = Vector3<double>(-1.0, 3.0, 0.5);
    }

    Vector3<double> vd1;
    Vector3<double> vd2;
};

TEST_F(Vector3MathTest, selfAddVector3) {
    EXPECT_EQ(Vector3<double>(-0.5, 5.0, 4.5), (vd1 += vd2));
}

TEST_F(Vector3MathTest, selfSubtractVector3) {
    EXPECT_EQ(Vector3<double>(1.5, -1.0, 3.5), (vd1 -= vd2));
}

// *= and /= make no sense from a mathematical point of view.

TEST_F(Vector3MathTest, selfAddScalar) {
    EXPECT_EQ(Vector3<double>(2.5, 4.0, 6.0), (vd1 += 2.0));
}

TEST_F(Vector3MathTest, selfSubtractScalar) {
    EXPECT_EQ(Vector3<double>(-4.0, 0.0, -2.5), vd2 -= 3.0);
}

TEST_F(Vector3MathTest, Vector3AddVector3) {
    EXPECT_EQ(Vector3<double>(-0.5, 5.0, 4.5), (vd1 + vd2));
}

TEST_F(Vector3MathTest, Vector3SubtractVector3) {
    EXPECT_EQ(Vector3<double>(1.5, -1.0, 3.5), (vd1 - vd2));
}

TEST_F(Vector3MathTest, Vector3InnerProduct) {
    EXPECT_EQ(7.5, (vd1 * vd2));
}

TEST_F(Vector3MathTest, Vector3CrossProduct) {
    EXPECT_EQ(Vector3<double>(-11.0, -4.25, 3.5), (vd1%vd2));
}
