#include <query_kdtree/QueryKdTree.hpp>
#include <build_kdtree/BuildKdTree.hpp>
#include <lib/KDTree.hpp>
#include <lib/RaiiIO.hpp>
#include <cxxtest/TestSuite.h>
#include <cstdio>
#include <unistd.h>

using namespace uber;
class TestQueryKdTree : public CxxTest::TestSuite {
public:
  TestQueryKdTree()
      : cwd_(get_current_dir_name()),
        dataFile_(cwd_ + "/data/kdtree_v5/sample_data.csv"),
        queryDataFile_(cwd_ + "/data/kdtree_v5/query_data.csv"),
        queryResultsFile_(cwd_ + "/gen/TestQueryKdTreeQueRes.csv"),
        treeFile_(cwd_ + "/gen/TestQueryKdTree.tree") {}
  ~TestQueryKdTree() {
    (void) std::remove(queryResultsFile_.c_str());
    (void) std::remove(treeFile_.c_str());
  }

  void test_query() {
    int rc = BuildKdTree::build(dataFile_, treeFile_);
    TS_ASSERT_EQUALS(0, rc);
    KdTreePtr<double> tree = std::make_shared<KdTree<double>>();
    Istream istr(treeFile_);
    std::ifstream &ifs=istr.get();
    ifs >> tree;
    // 1000 is number of points
    TS_ASSERT_EQUALS(tree->size(), 1000);
    TS_ASSERT_EQUALS(tree->sliceNodesCount(), 1000);
    //std::cout << "****** tree " << tree << "\n";
    // call Query
    rc=QueryKdTree::query(queryDataFile_, treeFile_, queryResultsFile_);
    TS_ASSERT_EQUALS(0, rc);
    // check file exists
    Istream istr2(queryResultsFile_);
    TS_ASSERT_EQUALS(istr2.get().is_open(), true);
  }
private:
  std::string cwd_;
  std::string dataFile_;
  std::string queryDataFile_;
  std::string queryResultsFile_;
  std::string treeFile_;
};
