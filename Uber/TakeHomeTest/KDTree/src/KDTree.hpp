/*
Uber Take Home Test
*/
#include <algorithm>
#include <cassert>
#include <vector>
#include <type_traits>
#include <memory>
#include <stack>
#include <set>
#include <iostream>

namespace uber {
// Define Point
template <typename ElemType>
using Point = std::vector<ElemType>;
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const std::vector<T>& point) {
  ostr << "[";
  bool isFirst=true;
  for (auto e : point) {
    if (isFirst) {
      isFirst=false;
    } else {
      ostr << ",";
    }
    ostr << e;
  }
  ostr << "]";
  return ostr;
}
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
  inline void setRight(const std::shared_ptr<KdTreeNode> &right) {
    right_ = right;
  }
  inline std::shared_ptr<KdTreeNode> right() const { return right_; }
  inline void setLeft(const std::shared_ptr<KdTreeNode> &left) { left_ = left; }
  inline std::shared_ptr<KdTreeNode> left() const { return left_; }
  inline void setSlicePoint(const ElemType &slice) {
    slicePoint_ = slice;
  }
  inline const ElemType &slicePoint() const { return slicePoint_; }
  inline void setDimension(const size_t dimension) { dimension_ = dimension; }
  inline size_t dimension() const { return dimension_; }
  inline void addPoint(const Point<ElemType> &point) {
    points_.push_back(point);
  }
  inline std::vector<Point<ElemType>> &points() { return points_; }
  inline void setLeaf(const bool isLeaf) { leaf_ = isLeaf; }
  inline bool isLeaf() const { return leaf_; }

private:
  std::vector<Point<ElemType>> points_;
  KdTreeNodePtr<ElemType> left_; // values < slicePoint
  KdTreeNodePtr<ElemType> right_; // values >= slicePoint
  size_t dimension_;
  ElemType slicePoint_;
  bool leaf_;
};
template <typename ElemType>
std::ostream& operator<<(std::ostream& ostr, const KdTreeNodePtr<ElemType> node) {
  if (!node) {
    ostr << "{null}";
    return ostr;
  }
  ostr << "{";
  ostr << "point=" << node->points() << ";";
  ostr << "slicePoint=" << node->slicePoint() << ";";
  ostr << std::boolalpha << "isleaf= " << node->isLeaf() << ";";
  ostr << "dim=" << node->dimension() << ";";
  ostr << "left" << node->left();
  ostr << "right" << node->right();
  ostr << "}";
  return ostr;
}
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
  KdTreeNodePtr<ElemType> buildPartitions(std::vector<Point<ElemType>> &points,
                                           const size_t startIdx,
                                           const size_t endIdx,
                                           const size_t dimension);
  void insert(const Point<ElemType>& point);
  void insert(std::vector<Point<ElemType>> &points, const size_t startIdx,
              const size_t endIdx, const size_t dimension,
              KdTreeNodePtr<ElemType> &curNode);
  uber::Point<ElemType> &nearPoint(const KdTreeNodePtr<ElemType> &node,
                                   const Point<ElemType> &point);
  ElemType calcDist(const Point<ElemType> &a, const size_t sliceValue,
                    const size_t dim);
  ElemType calcDist(const Point<ElemType> &a, const Point<ElemType> &b);
  uber::KdTreeNodePtr<ElemType> findLeaf(KdTreeNodePtr<ElemType> node,
                                         const Point<ElemType> &point,
                                         BtStack<ElemType> *btStack);
  uber::KdTreeNodePtr<ElemType> findLeafPoint(KdTreeNodePtr<ElemType> node,
                                              const Point<ElemType> &point,
                                              BtStack<ElemType> &btStack);
  std::shared_ptr<KdTreeNode<ElemType>> root_;
  size_t sliceNodesCount_;
  size_t size_;
};
};

template <typename ElemType>
uber::KdTreeNode<ElemType>::KdTreeNode()
    : dimension_(0), slicePoint_(0), leaf_(false) {}

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
  // Start with full vector and 0th dimension
  root_ = buildPartitions(wPoints, 0, wPoints.size()-1, 0);
  std::cout << "BP: " << root_ << "\n\n";
  for (const auto& point : wPoints) {
    insert(point);
  }
  std::cout << "BP3: " << root_ << "\n\n";
}

template <typename ElemType>
void uber::KdTree<ElemType>::insert(const Point<ElemType> &point) {
  KdTreeNodePtr<ElemType> itr = findLeaf(root_, point, nullptr);
  //std::cout << "BP2: " << root_ << "\n\n";
  //std::cout << "Leaf: " << itr << "\n\n";
  if (!itr->isLeaf()) {
    size_t dim = itr->dimension();
    auto node =  std::make_shared<KdTreeNode<ElemType>>();
    node->setLeaf(true);
    if (point[dim] <= itr->slicePoint()) {
      itr->setLeft(node);
    } else {
      itr->setRight(node);
    }
    itr = node;
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
uber::KdTreeNodePtr<ElemType> uber::KdTree<ElemType>::buildPartitions(
    std::vector<Point<ElemType>> &points, const size_t startIdx,
    const size_t endIdx, const size_t dimension) {
  std::cout << "\nstart: " << startIdx << ", end: " << endIdx << ", dim:" << dimension;
  if (startIdx > points.size() || endIdx > points.size() || startIdx > endIdx) {
    return KdTreeNodePtr<ElemType>();
  }
  assert(dimension < points[0].size());
  // calculate mediat
  // sort points from startIdx to endIdx
  static const auto cmp =
      [&dimension](const Point<ElemType> &a, const Point<ElemType> &b) {
        return a[dimension] < b[dimension];
      };
  // INFO: you could use sort but it is costly
  //std::sort(points.begin() + startIdx, points.begin() + endIdx + 1, cmp);
  size_t median = (startIdx + endIdx) / 2;
  std::nth_element(points.begin() + startIdx, points.begin() + median,
                   points.begin() + endIdx + 1, cmp);
  std::cout << ", median:" << median << ", value: " << points[median][dimension] << ", Point:" << points<< "\n";
  ++sliceNodesCount_;
  KdTreeNodePtr<ElemType> curNode = std::make_shared<KdTreeNode<ElemType>>();
  curNode->setSlicePoint(points[median][dimension]);
  curNode->setDimension(dimension);
  // Assuming all points have same dimensions
  size_t nextDimension = (dimension + 1) % points[0].size();
  KdTreeNodePtr<ElemType> beforeMedian = buildPartitions(
      points, startIdx, median - 1, nextDimension);
  curNode->setLeft(beforeMedian);

  KdTreeNodePtr<ElemType> afterMedian =
      buildPartitions(points, median + 1, endIdx, nextDimension);
  curNode->setRight(afterMedian);
  return curNode;
}

template <typename ElemType>
uber::KdTreeNodePtr<ElemType>
uber::KdTree<ElemType>::findLeaf(KdTreeNodePtr<ElemType> node,
                                 const Point<ElemType> &point,
                                 BtStack<ElemType> *btStack) {
  while(node) {
    if (node->isLeaf()) {
      break;
    }
    size_t dimension = node->dimension();
    if (point[dimension] <= node->slicePoint()) {
      if (btStack) {
        btStack->push(std::make_tuple(node, true));
      }
      if (node->left()) {
        node = node->left();
      } else {
        break;
      }
    } else {
      if (btStack) {
        btStack->push(std::make_tuple(node, false));
      }
      if (node->right()) {
        node = node->right();
      } else {
        break;
      }
    }
  }
  if (btStack) {
    if (btStack->empty()) {
      std::cout << "\n\nstack empty\n";
    } else {
      auto &tp = btStack->top();
      std::cout << "\n\nstack top: node: " << std::get<0>(tp)
                << ", lr: " << std::get<1>(tp) << "\n";
    }
  }
  return node;
}

template <typename ElemType>
uber::KdTreeNodePtr<ElemType>
uber::KdTree<ElemType>::findLeafPoint(KdTreeNodePtr<ElemType> node,
                                 const Point<ElemType> &point,
                                 BtStack<ElemType> &btStack) {
  auto leaf = findLeaf(node, point, &btStack);
  while (true) {
    if (leaf->isLeaf()) {
      return leaf;
    } else if (leaf->left()) {
      btStack.pop();
      btStack.push(std::make_tuple(leaf, true));
      auto &tp = btStack.top();
      std::cout << "\n\n2node: " << leaf << "\n";
      std::cout << "stack top2: leaf: " << std::get<0>(tp)
                << ", lr: " << std::get<1>(tp) << "\n\n";
      return findLeafPoint(leaf->left(), point, btStack);
    } else if (leaf->right()) {
      btStack.pop();
      btStack.push(std::make_tuple(leaf, false));
      auto &tp = btStack.top();
      std::cout << "\n\n2node: " << leaf << "\n";
      std::cout << "\n\nstack top2: node: " << std::get<0>(tp)
                << ", lr: " << std::get<1>(tp) << "\n";
      return findLeafPoint(leaf->right(), point, btStack);
    } else {
      assert(0);
      auto &tp = btStack.top();
      leaf = std::get<0>(tp);
      bool lr = std::get<1>(tp);
      // if stack is not empty
      // if top of stack previously traversed left and it does not have right
      // subtree
      // if top or stack previously traversed right and it does not have left
      // subtree
      while (!btStack.empty() &&
             ((lr && !leaf->right()) || (!lr && !leaf->left()))) {
        btStack.pop();
        tp = btStack.top();
      }
      assert(!btStack.empty());
      tp = btStack.top();
      leaf = std::get<0>(tp);
      lr = std::get<1>(tp);
    }
  }
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
// This provides distance between planes.
template <typename ElemType>
ElemType uber::KdTree<ElemType>::calcDist(const Point<ElemType> &a,
                                          const size_t sliceValue,
                                          const size_t dim) {
  return fabs(a[dim] - sliceValue);
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
  std::set<KdTreeNodePtr<ElemType>> visited;
  std::cout << "ROOT>>>: " << root_ << "\n" << "\n";
  KdTreeNodePtr<ElemType> leaf = findLeafPoint(root_, point, btStack);
  std::cout << "leaf1: " << leaf << "\n";
  Point<ElemType> &curNearPoint = nearPoint(leaf, point);
  std::cout << "NP: " << curNearPoint << "\n";
  ElemType curDist = calcDist(point, curNearPoint);
  while (!btStack.empty()) {
    // true means previous selection was left, false means right
    // hence we need to visit right in case of true otherwise left
    auto& tp = btStack.top();
    size_t dim = std::get<0>(tp)->dimension();
    std::cout << "\n\nstack top: node: " << std::get<0>(tp)
              << ", lr: " << std::get<1>(tp) << "\n";
    std::cout << "CBP: " << curNearPoint << "\n";
    std::cout << "curDist: " << curDist << "\n";
    visited.insert(std::get<0>(tp));
    btStack.pop();
    KdTreeNodePtr<ElemType> tmpNodePtr;
    std::cout << "tp1: " << std::get<1>(tp) << "\n";
    if (std::get<1>(tp)) {
      std::cout << "choosing right\n";
      tmpNodePtr = std::get<0>(tp)->right();
    } else {
      std::cout << "choosing left\n";
      tmpNodePtr = std::get<0>(tp)->left();
    }
    if (!tmpNodePtr) {
      continue;
    }
    if (visited.find(tmpNodePtr) != visited.end()) {
      continue;
    }
    std::cout << "tmpNode: " << tmpNodePtr << "\n";
    ElemType tmpDist =
        calcDist(point, tmpNodePtr->slicePoint(), dim);
    std::cout << "tmpDist: " << tmpDist << "\n";
    ElemType curBestDist =
        calcDist(curNearPoint, tmpNodePtr->slicePoint(), dim);
    std::cout << "curBestDist2: " << curBestDist << "\n";
    if (tmpDist < curBestDist) {
      leaf = findLeafPoint(tmpNodePtr, point, btStack);
      std::cout << "\n\n\nleaf2:: " << leaf << "\n";
      auto &tmpCurNearPoint = nearPoint(leaf, point);
      std::cout << "tCNP: " << tmpCurNearPoint << "\n";
      auto tmpCurDist = calcDist(point, tmpCurNearPoint);
      std::cout << "tmpCurDist: " << tmpCurDist << "\n";
      if (tmpCurDist < curDist) {
        curNearPoint = tmpCurNearPoint;
        curDist = tmpCurDist;
        std::cout << "up curNearPoint: " <<  curNearPoint << "\n";
        std::cout << "up curDist: " << curDist << "\n";
      }
    }
  }
  return curNearPoint;
}

template <typename ElemType>
int uber::KdTree<ElemType>::save() {
  return 0;
}
