// Unit test for KdTree
#include <KDTree.hpp>
#include <cxxtest/TestSuite.h>
#include <string>
using namespace uber;
class KdTree__TestSuite : public CxxTest::TestSuite {
public:
  void XXXtest_constructor() {
    KdTree<int> tree;
    std::vector<Point<int>> points = {{1, 90, 2}, {3, 4, 2}, {54, 2, 22}};
    tree.insert(points);
    TS_ASSERT_EQUALS(tree.size(), points.size());
    TS_ASSERT_EQUALS(tree.sliceNodesCount(), points.size());
  }
  void XXXtest_empty_constructor() {
    KdTree<int> tree;
    std::vector<Point<int>> points = {};
    tree.insert(points);
    TS_ASSERT_EQUALS(tree.size(), points.size());
    TS_ASSERT_EQUALS(tree.sliceNodesCount(), points.size());
  }
  void test_constructor_double() {
    KdTree<double> tree;
    std::vector<Point<double>> points = {
        {1.0, 90.0},
        {3.0, 4.0},
        {54.0, 2.0},
        {4.0, 1.1},
        {0.1, 0.3},
        {0.0, 10.2},
        {20.0, 30.0},
        {0.0, 0.0},
    };
    tree.insert(points);
    TS_ASSERT_EQUALS(tree.size(), points.size());
    TS_ASSERT_EQUALS(tree.sliceNodesCount(), points.size());
    const Point<double> nearPoint1{3.0, 4.0};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({3.1, 4.0}), nearPoint1);
    const Point<double> nearPoint2{0.1, 0.3};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({1.0, 2.0}), nearPoint2);
    const Point<double> nearPoint3{0.0, 10.2};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({0.0, 10.2}), nearPoint3);
  }
  void test_constructor_string() {
    //should cause compilation error
    //KdTree<std::string> tree2;
  }
};

