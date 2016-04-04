#ifndef _UBER_QUERY_KDTREE_QUERYKDTREE_H_
#define _UBER_QUERY_KDTREE_QUERYKDTREE_H_
#include <string>
namespace uber {
namespace QueryKdTree {
int query(const std::string &queryDataFile, const std::string &treeFile,
          const std::string &queryResultsFile);
} // QueryKdTree
} // uber
#endif //_UBER_QUERY_KDTREE_QUERYKDTREE_H_
