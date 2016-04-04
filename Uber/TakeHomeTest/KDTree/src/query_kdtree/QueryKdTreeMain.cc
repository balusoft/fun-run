#include <query_kdtree/QueryKdTree.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "usage: " << argv[0] << " <query-data-file-path> "
                                         "<tree-file-path> "
                                         "<query-result-file-path>\n";
    return 255;
  }
  std::string queryDataFilePath(argv[1]);
  std::string treeFilePath(argv[2]);
  std::string queryResultPath(argv[3]);
  int rc = uber::QueryKdTree::query(queryDataFilePath, treeFilePath,
                                    queryResultPath);
  if (0 != rc) {
    std::cerr << "Command failed.... TODO: add detailed errors\n";
  }
  return rc;
}

