// Unit test for KdTree
#include <KDTree.hpp>
#include <cxxtest/TestSuite.h>
#include <string>
using namespace uber;
class KdTree__TestSuite : public CxxTest::TestSuite {
public:
  void test_constructor() {
    KdTree<int> tree;
    std::vector<Point<int>> points = {{1, 90, 2}, {3, 4, 2}, {54, 2, 22}};
    tree.insert(points);
    TS_ASSERT_EQUALS(tree.size(), points.size());
    TS_ASSERT_EQUALS(tree.sliceNodesCount(), points.size());
  }
  void test_empty_constructor() {
    KdTree<int> tree;
    std::vector<Point<int>> points = {};
    tree.insert(points);
    TS_ASSERT_EQUALS(tree.size(), points.size());
    TS_ASSERT_EQUALS(tree.sliceNodesCount(), points.size());
  }
  void test_constructor_double_serach() {
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
    // search elements
    const Point<double> nearPoint1{3.0, 4.0};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({3.1, 4.0}), nearPoint1);
    const Point<double> nearPoint2{0.1, 0.3};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({1.0, 2.0}), nearPoint2);
    const Point<double> nearPoint3{0.0, 10.2};
    TS_ASSERT_EQUALS(tree.findNearestNighbor({0.0, 10.2}), nearPoint3);
  }
  void test_constructor_double_serialize() {
    KdTreePtr<double> tree=std::make_shared<KdTree<double>>();
    std::vector<Point<double>> points = {
        {1.0, 90.0},
        {3.0, 4.0},
        {54.0, 2.0}
    };
    tree->insert(points);
    TS_ASSERT_EQUALS(tree->size(), points.size());
    TS_ASSERT_EQUALS(tree->sliceNodesCount(), points.size());
    std::cout << "kdTree: " << tree << "\n";
    std::ostringstream ostr;
    ostr << tree;
    std::string sKdTree = "{3,3,{4,1,0,[],{54,0,0,[],{0,0,1,[[54,2],[3,4]],{},{"
                          "}},{}},{1,0,0,[],{0,0,1,[[1,90]],{},{}},{}}}}";
    TS_ASSERT_EQUALS(ostr.str(), sKdTree);
    std::istringstream istr(sKdTree);
    KdTreePtr<double> resTree=std::make_shared<KdTree<double>>();
    istr >> resTree;
    std::ostringstream ostr2;
    std::cout << "resTree: " << resTree << "\n";
    ostr2 << resTree;
    TS_ASSERT_EQUALS(ostr2.str(), sKdTree);
    // Serialize
  }
  void test_constructor_string() {
    //should cause compilation error
    //KdTree<std::string> tree2;
  }
  void test_vector_io() {
    std::string vStr = "[[1,2,3],[4,5,6]]";
    std::vector<Point<int>> points{{1, 2, 3}, {4, 5, 6}};
    std::vector<Point<int>> ioRes;
    std::istringstream istr(vStr);
    istr >> ioRes;
    TS_ASSERT_EQUALS(ioRes, points);
    //std::cout << "ioRes:" << ioRes << "\n";
    std::ostringstream ostr;
    ostr << ioRes;
    TS_ASSERT_EQUALS(ostr.str(), vStr);
    bool res = false;
    std::string bStr("1");
    std::istringstream bIstr(bStr);
    bIstr >> res;
    TS_ASSERT_EQUALS(res, true);
  }
};

