/*
Uber Take Home Test
*/
#include <algorithm>
#include <cassert>
#include <vector>
#include <type_traits>
#include <memory>

namespace uber {
// Define Point
template <typename ElemType>
using Point = std::vector<ElemType>;
// Define KdTreeNodePtr
template <typename ElemType>
class KdTreeNode;
template <typename ElemType>
using KdTreeNodePtr = std::shared_ptr<KdTreeNode<ElemType>>;

template <typename ElemType>
class KdTreeNode {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
  KdTreeNode();
  void setRight(const std::shared_ptr<KdTreeNode> &right) { right_ = right; }
  std::shared_ptr<KdTreeNode> right() const { return right_; }
  void setLeft(const std::shared_ptr<KdTreeNode> &left) { left_ = left; }
  std::shared_ptr<KdTreeNode> left() const { return left_; }
  void setPoint(const Point<ElemType>& point) { point_ = point; }

private:
  Point<ElemType> point_;
  KdTreeNodePtr<ElemType> right_;
  KdTreeNodePtr<ElemType> left_;
};

template <typename ElemType>
class KdTree {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
  KdTree();
  KdTree(const std::string &filepath);
  void insert(const std::vector<Point<ElemType>>& points);
  Point<ElemType> findNearestNighbor(const Point<ElemType>& point);
  int save();
private:
  void insert(const std::vector<Point<ElemType>> &points, const size_t startIdx,
              const size_t endIdx, const size_t dimension,
              KdTreeNodePtr<ElemType> &curNode);
  std::shared_ptr<KdTreeNode<ElemType>> root_;
  size_t size_;
};
};

template <typename ElemType>
uber::KdTreeNode<ElemType>::KdTreeNode()
    : point_(), right_(), left_() {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree() : size_(0) {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree(const std::string &filepath) {}

template <typename ElemType>
void uber::KdTree<ElemType>::insert(const std::vector<Point<ElemType>>& points) {
  if (points.empty()) {
    return;
  }
  root_ = std::make_shared<KdTreeNode<ElemType>>(new KdTreeNode<ElemType>());
  // Start with full vector and 0th dimension
  insert(points, 0, points.size()-1, 0, root_);
}

/**
  This is recursive method adds all points to the KD tree recursively.
  1) Finds median between start and end
  2) inserts point at curNode
  3) continue populating nodes from startIdx to median-1
  4) continue populating nodes from median+1 to endIdx
 */
template <typename ElemType>
void uber::KdTree<ElemType>::insert(const std::vector<Point<ElemType>> &points,
                                    const size_t startIdx, const size_t endIdx,
                                    const size_t dimension,
                                    KdTreeNodePtr<ElemType> &curNode) {
  assert(startIdx < points.size());
  assert(endIdx < points.size());
  assert(dimension < points[0].size());
  // calculate mediat
  // sort points from startIdx to endIdx
  static const auto cmp =
      [&dimension](const Point<ElemType> &a, const Point<ElemType> &b) {
        a[dimension] < b[dimension];
      };
  // TODO: We could use median-of-median algorithm which could provide O(n)
  //       result
  std::sort(points, points.begin() + startIdx, points.end() + endIdx, cmp);
  size_t median = (startIdx + endIdx) / 2;
  ++size_;
  curNode->setPoint(points[median]);
  // Assuming all points have same dimensions
  size_t nextDimension = (dimension + 1) % points[0].size();
  // If we have elements before median insert them
  if (median > startIdx) {
    KdTreeNodePtr<ElemType> beforeMedian =
        std::make_shared<KdTreeNode<ElemType>>(new KdTreeNode<ElemType>());
    curNode->setLeft(beforeMedian);
    insert(points, startIdx, median - 1, nextDimension, beforeMedian);
  }
  // If we have elements after median insert them
  if (median < endIdx) {
    KdTreeNodePtr<ElemType> afterMedian =
        std::make_shared<KdTreeNode<ElemType>>(new KdTreeNode<ElemType>());
    curNode->setRight(afterMedian);
    insert(points, median + 1, endIdx, afterMedian, afterMedian);
  }
}

template <typename ElemType>
uber::Point<ElemType>
uber::KdTree<ElemType>::findNearestNighbor(const Point<ElemType> &point) {
  return point;
}

template <typename ElemType>
int uber::KdTree<ElemType>::save() {
  return 0;
}
