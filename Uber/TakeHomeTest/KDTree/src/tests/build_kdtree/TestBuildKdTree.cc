#include <lib/KDTree.hpp>
#include <lib/RaiiIO.hpp>
#include <build_kdtree/BuildKdTree.hpp>
#include <cxxtest/TestSuite.h>
#include <unistd.h>
#include <string>
#include <cstdio>
using namespace uber;
class TestBuildKdTree : public CxxTest::TestSuite {
public:
  TestBuildKdTree()
      : cwd_(get_current_dir_name()),
        dataFile_(cwd_ + "/data/kdtree_v5/sample_data.csv"),
        queryFile_(cwd_ + "/data/kdtree_v5/query_data.csv"),
        treeFile_(cwd_ + "/gen/TestBuildKdTree.tree") {
  }
  ~TestBuildKdTree() {
    (void)std::remove(treeFile_.c_str());
  }
  void test_build() {
    BuildKdTree::build(dataFile_, treeFile_);
    KdTreePtr<double> tree = std::make_shared<KdTree<double>>();
    Istream istr(treeFile_);
    std::ifstream &ifs=istr.get();
    ifs >> tree;
    // 1000 is number of points
    TS_ASSERT_EQUALS(tree->size(), 1000);
    TS_ASSERT_EQUALS(tree->sliceNodesCount(), 1000);
    //std::cout << "*****8888 tree " << tree << "\n";
  }
private:
  std::string cwd_;
  std::string dataFile_;
  std::string queryFile_;
  std::string treeFile_;
};
