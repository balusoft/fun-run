#include <lib/RaiiIO.hpp>
#include <lib/KDTree.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "BuildKdTree.hpp"
namespace uber {
namespace BuildKdTree {
int readCSVfile(const std::string &dataFile, std::vector<Point<double>> &points) {
  Istream istr(dataFile);
  std::ifstream &ifs = istr.get();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    Point<double> point;
    double val;
    while (iss >> val) {
      point.push_back(val);
      // ignore commas
      char c;
      iss >> c;
    } // end of line
    points.push_back(point);
  }
  return 0;
}
/*
 Builds KdTree and saves it in given file name.
 It assumes directory path till file name exists.
 @return 0 on success, C style error code on failure
 */
int build(const std::string &dataFile, const std::string &treeFile) {
  std::vector<Point<double>> points;
  int rc = readCSVfile(dataFile, points);
  if (0 != rc) {
    return rc;
  }
  KdTreePtr<double> tree = std::make_shared<KdTree<double>>();
  tree->insert(points);
  //std::cout << "points: " << points << "\n";
  //std::cout << "tree: " << tree << "\n";
  //std::cout << "treeFile: " << treeFile << "\n";
  Ostream ostr(treeFile);
  std::ofstream &ofs = ostr.get();
  ofs << tree;
  return 0;
  // TODO: define proper error codes
}
} // BuildKdTree
} // uber
