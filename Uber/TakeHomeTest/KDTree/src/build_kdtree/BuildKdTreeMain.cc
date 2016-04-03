#include <build_kdtree/BuildKdTree.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " <data-file-path> <tree-file-path>\n";
    return 255;
  }
  std::string dataFile(argv[1]);
  std::string treeFile(argv[2]);
  int rc = uber::BuildKdTree::build(dataFile, treeFile);
  if (0 != rc) {
    std::cerr << "Command failed.... TODO: add detailed errors\n";
  }
  return rc;
}

