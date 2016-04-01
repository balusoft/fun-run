/*
Uber Take Home Test
*/
#include <algorithm>
#include <cassert>
#include <vector>
#include <type_traits>
#include <memory>
#include <stack>

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
class ArithmeticTemplate {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
};

template <typename ElemType>
class KdTreeNode : public ArithmeticTemplate<ElemType> {
public:
  KdTreeNode();
  void setRight(const std::shared_ptr<KdTreeNode> &right) { right_ = right; }
  std::shared_ptr<KdTreeNode> right() const { return right_; }
  void setLeft(const std::shared_ptr<KdTreeNode> &left) { left_ = left; }
  std::shared_ptr<KdTreeNode> left() const { return left_; }
  void setSlicePoint(const Point<ElemType>& slice) { slicePoint_ = slice; }
  const Point<ElemType>& slicePoint() const { return slicePoint_; }
  void setDimension(const size_t dimension) { dimension_ = dimension; }
  size_t dimension() const { return dimension_; }
  void addPoint(const Point<ElemType> &point) { points_.push_back(point); }
  std::vector<Point<ElemType>>& points() { return points_; }

private:
  std::vector<Point<ElemType>> points_;
  KdTreeNodePtr<ElemType> left_; // values < slicePoint
  KdTreeNodePtr<ElemType> right_; // values >= slicePoint
  size_t dimension_;
  Point<ElemType> slicePoint_;
};
template <typename ElemType>
using BtTuple = std::tuple<KdTreeNodePtr<ElemType>, bool>;
template <typename ElemType>
using BtStack = std::stack<BtTuple<ElemType>>;
template <typename ElemType>
class KdTree : public ArithmeticTemplate<ElemType> {
public:
  KdTree();
  KdTree(const std::string &filepath);
  void insert(const std::vector<Point<ElemType>>& points);
  const Point<ElemType>& findNearestNighbor(const Point<ElemType>& point);
  int save();
  size_t size() const { return size_; }
  size_t sliceNodesCount() const { return sliceNodesCount_; }

private:
  void buildPartitions(std::vector<Point<ElemType>> &points, const size_t startIdx,
              const size_t endIdx, const size_t dimension,
              KdTreeNodePtr<ElemType> &curNode);
  void insert(const Point<ElemType>& point);
  void insert(std::vector<Point<ElemType>> &points, const size_t startIdx,
              const size_t endIdx, const size_t dimension,
              KdTreeNodePtr<ElemType> &curNode);
  uber::Point<ElemType> &nearPoint(const KdTreeNodePtr<ElemType> &node,
                                   const Point<ElemType> &point);
  ElemType calcDist(const Point<ElemType> &a, const Point<ElemType> &b);
  uber::KdTreeNodePtr<ElemType> &findLeaf(KdTreeNodePtr<ElemType> & node,
                                          const Point<ElemType> &point,
                                          BtStack<ElemType> &btStack);
  std::shared_ptr<KdTreeNode<ElemType>> root_;
  size_t sliceNodesCount_;
  size_t size_;
};
};

template <typename ElemType>
uber::KdTreeNode<ElemType>::KdTreeNode()
    : dimension_(0), slicePoint_(0) {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree()
    : sliceNodesCount_(0), size_(0) {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree(const std::string &filepath) {}

template <typename ElemType>
void uber::KdTree<ElemType>::insert(
    const std::vector<Point<ElemType>> &points) {
  if (points.empty()) {
    return;
  }
  //Make copy so that we can sort them
  std::vector<Point<ElemType>> wPoints(points);
  root_ = std::make_shared<KdTreeNode<ElemType>>();
  // Start with full vector and 0th dimension
  buildPartitions(wPoints, 0, wPoints.size()-1, 0, root_);
  for (const auto& point : wPoints) {
    insert(point);
  }
}

template <typename ElemType>
void uber::KdTree<ElemType>::insert(const Point<ElemType> &point) {
  KdTreeNodePtr<ElemType> itr = root_;
  // SlicePoints will be having both children unless they are leaves
  while (itr->right() || itr->left()) {
    size_t dimension=itr->dimension();
    if (point[dimension] < (itr->slicePoint()[dimension])) {
      itr = itr->left();
    } else {
      itr = itr->right();
    }
  }
  itr->addPoint(point);
  ++size_;
}

/**
  This is recursive method adds all points to the KD tree recursively.
  1) Finds median between start and end
  2) set slice point as median value
  3) continue populating nodes from startIdx to median-1
  4) continue populating nodes from median+1 to endIdx
 */
template <typename ElemType>
void uber::KdTree<ElemType>::buildPartitions(
    std::vector<Point<ElemType>> &points, const size_t startIdx,
    const size_t endIdx, const size_t dimension,
    KdTreeNodePtr<ElemType> &curNode) {
  assert(startIdx < points.size());
  assert(endIdx < points.size());
  assert(dimension < points[0].size());
  // calculate mediat
  // sort points from startIdx to endIdx
  static const auto cmp =
      [&dimension](const Point<ElemType> &a, const Point<ElemType> &b) {
        return a[dimension] < b[dimension];
      };
  // INFO: you could use sort but it is costly
  //std::sort(points.begin() + startIdx, points.begin() + endIdx, cmp);
  size_t median = (startIdx + endIdx) / 2;
  std::nth_element(points.begin() + startIdx, points.begin() + median,
                   points.begin() + endIdx, cmp);
  ++sliceNodesCount_;
  curNode->setSlicePoint(points[median]);
  curNode->setDimension(dimension);
  // Assuming all points have same dimensions
  size_t nextDimension = (dimension + 1) % points[0].size();
  KdTreeNodePtr<ElemType> beforeMedian =
      std::make_shared<KdTreeNode<ElemType>>();
  curNode->setLeft(beforeMedian);
  // If we have elements before median insert them
  if (median > startIdx) {
    buildPartitions(points, startIdx, median - 1, nextDimension, beforeMedian);
  }
  KdTreeNodePtr<ElemType> afterMedian =
      std::make_shared<KdTreeNode<ElemType>>();
  curNode->setRight(afterMedian);
  // If we have elements after median insert them
  if (median < endIdx) {
    buildPartitions(points, median + 1, endIdx, nextDimension, afterMedian);
  }
}

template <typename ElemType>
uber::KdTreeNodePtr<ElemType> &
uber::KdTree<ElemType>::findLeaf(KdTreeNodePtr<ElemType> &node,
                                 const Point<ElemType> &point,
                                 BtStack<ElemType> &btStack) {
  while(node->right() || node->left()) {
    size_t dimension = node->dimension();
    if (point[dimension] <= node->slicePoint()[dimension]) {
      btStack.push(std::make_tuple(node, true));
      node = node->left();
    } else {
      btStack.push(std::make_tuple(node, false));
      node = node->right();
    }
  }
  return node;
}

// Using geometry formula between two numbers
// dist^2 = (deltaX)^2 + (deltaY)^2
template <typename ElemType>
ElemType uber::KdTree<ElemType>::calcDist(const Point<ElemType> &a,
                                          const Point<ElemType> &b) {
  assert(a.size() == b.size());
  ElemType dist=0;
  for (size_t i=0; i<a.size(); ++i) {
    ElemType tmp = a[i] - b[i];
    dist += (tmp*tmp);
  }
  return dist;
}

template <typename ElemType>
uber::Point<ElemType> &
uber::KdTree<ElemType>::nearPoint(const KdTreeNodePtr<ElemType> &node,
                                  const Point<ElemType> &point) {
  auto cmp =
      [this, &point, &node](const Point<ElemType> &a, const Point<ElemType> &b) {
        return this->calcDist(a, point) < this->calcDist(b, point);
      };
  return *std::min_element(node->points().begin(), node->points().end(), cmp);
}

template <typename ElemType>
const uber::Point<ElemType>&
uber::KdTree<ElemType>::findNearestNighbor(const Point<ElemType> &point) {
  //step1: find leaf node
  //step2: maintain stack of nodes for backtracking
  BtStack<ElemType> btStack;
  KdTreeNodePtr<ElemType> &leaf = findLeaf(root_, point, btStack);
  Point<ElemType> &curNearPoint = nearPoint(leaf, point);
  ElemType curDist = calcDist(point, curNearPoint);
  while (!btStack.empty()) {
    // true means previous selection was left, false means right
    // hence we need to visit right in case of true otherwise left
    auto& tp = btStack.top();
    btStack.pop();
    auto tmpNodePtr =
        std::get<1>(tp) ? std::get<0>(tp)->right() : std::get<0>(tp)->left();
    ElemType tmpDist = calcDist(point, tmpNodePtr->slicePoint());
    if (tmpDist < curDist) {
      leaf = findLeaf(tmpNodePtr, point, btStack);
      curNearPoint = nearPoint(leaf, point);
      curDist = calcDist(point, curNearPoint);
    }
  }
  return curNearPoint;
}

template <typename ElemType>
int uber::KdTree<ElemType>::save() {
  return 0;
}
