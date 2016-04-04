#include <lib/KDTree.hpp>
#include <lib/RaiiIO.hpp>
#include "QueryKdTree.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace uber {
namespace QueryKdTree {
KdTreePtr<double> readTree(const std::string &treeFile) {
  Istream istr(treeFile);
  std::ifstream &ifs = istr.get();
  KdTreePtr<double> tree = std::make_shared<KdTree<double>>();
  assert(ifs >> tree);
  return tree;
}
int query(const std::string &queryDataFile, const std::string &treeFile,
          const std::string &queryResultsFile) {
  const KdTreePtr<double> tree = readTree(treeFile);
  // update results to queryResultsFile
  Ostream ostr(queryResultsFile);
  std::ofstream &ofs = ostr.get();
  // read contents from query data
  Istream istr(queryDataFile);
  std::ifstream &ifs = istr.get();
  std::string line;
  while (std::getline(ifs, line)) {
    // Convert into [a,b,c] format
    std::string line2 = "[";
    line2 += line;
    line2 += "]";
    //std::cout << "line: " << line2 << "\n";
    std::istringstream iss(line2);
    Point<double> point;
    assert(iss >> point);
    ofs << tree->findNearestNighbor(point) << "\n";
  }
  return 0;
}
} // QueryKdTree
} // uber
