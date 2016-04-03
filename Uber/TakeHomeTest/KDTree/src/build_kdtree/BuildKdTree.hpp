#ifndef _UBER_BUILD_KDTREE_H_
#define _UBER_BUILD_KDTREE_H_
#include <string>
namespace uber {
namespace BuildKdTree {
/*
 Builds KdTree and saves it in given file name.
 It assumes directory path till file name exists.
 @return 0 on success, C style error code on failure
 */
int build(const std::string &dataFile, const std::string &treeFile);
}
}
#endif
