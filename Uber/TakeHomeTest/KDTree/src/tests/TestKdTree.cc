// Unit test for KdTree
#include <KdTree.hpp>
#include <cxxtest/TestSuite.h>
#include <string>

class KdTree__TestSuite : public CxxTest::TestSuite {
public:
  void test_constructor() {
    uber::KdTree<int> tree;
    //uber::KdTree<std::string> tree2;
  }
};

