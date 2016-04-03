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
/**
 Assume elements are comma separated
 no white spaces for reducing complexity
 1) get string line
 2) first line must be [ and endline must be]
 3) convert comma to space and [] to space
 4) ignore spaces front and rear
 5) pushback string by string to vector
*/
template <typename T>
std::istream& operator>>(std::istream& istr, std::vector<T>& v) {
  auto beg = istr.tellg();
  char c;
  istr >> c;
  if (c != '[') {
    istr.seekg(beg, istr.beg);
    return istr;
  }
  auto beg2 = istr.tellg();
  if (istr >> c) {
    if (c == ']') {
      return istr;
    } else {
      istr.seekg(beg2, istr.beg);
    }
  }
  while(true) {
    T t;
    if (istr >> t) {
      v.push_back(t);
      istr >> c;
      if(c == ',') {
        continue;
      } else if (c == ']') {
        break;
      } else {
        istr.seekg(beg, istr.beg);
        return istr;
      }
    } else {
      istr >> c;
      if (c == ']') {
        break;
      } else {
        istr.seekg(beg, istr.beg);
        return istr;
      }
    }
  }
  return istr;
}
// Define KdTreeNodePtr
template <typename ElemType>
class KdTreeNode;
template <typename ElemType>
using KdTreeNodePtr = std::shared_ptr<KdTreeNode<ElemType>>;
struct NonCopyable {
  NonCopyable &operator=(const NonCopyable &) = delete;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable() = default;
};

template <typename ElemType>
class ArithmeticTemplate : NonCopyable {
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
  inline void setPoints(const std::vector<Point<ElemType>> &points) {
    points_ = points;
  }
  inline std::vector<Point<ElemType>> &points() { return points_; }
  inline void setLeaf(const bool isLeaf) { leaf_ = isLeaf; }
  inline bool isLeaf() const { return leaf_; }
  inline void setInited(const bool inited) { inited_ = inited; }
  inline bool isInited() const { return inited_; };

private:
  std::vector<Point<ElemType>> points_;
  size_t dimension_;
  ElemType slicePoint_;
  bool leaf_;
  bool inited_;
  KdTreeNodePtr<ElemType> left_; // values < slicePoint
  KdTreeNodePtr<ElemType> right_; // values >= slicePoint
};

template <typename ElemType> class MedianPartition {
public:
  std::tuple<size_t, size_t, ElemType>
  operator()(std::vector<Point<ElemType>> &points, const size_t startIdx,
             const size_t endIdx);

private:
  size_t getDimension(std::vector<Point<ElemType>> &points, const size_t startIdx,
                    const size_t endIdx);
};

/*
 Format is {slicePoint,isLeaf,Dim,Points,leftSubTree,rightSubTree}
 */
template <typename ElemType>
std::ostream &operator<<(std::ostream &ostr,
                         const KdTreeNodePtr<ElemType> &node) {
  if (!node) {
    ostr << "{}";
    return ostr;
  }
  ostr << "{";
  ostr << node->slicePoint() << ",";
  ostr << node->dimension() << ",";
  ostr << node->isLeaf() << ",";
  ostr << node->points() << ",";
  ostr << node->left() << ",";
  ostr << node->right();
  ostr << "}";
  return ostr;
}
/*
 Format is {slicePoint,isLeaf,Dim,Points,leftSubTree,rightSubTree}
 */
template <typename ElemType>
std::istream &operator>>(std::istream &istr, KdTreeNodePtr<ElemType> &curNode) {
  if (!curNode) {
    return istr;
  }
  auto beg = istr.tellg();
  char c;
  if (!(istr >> c) || (c != '{')) {
    istr.seekg(beg, istr.beg);
    return istr;
  }

  auto beg2 = istr.tellg();
  if (istr >> c) {
    if (c == '}') {
      return istr;
    } else {
      istr.seekg(beg2, istr.beg);
    }
  }
  bool fail = true;
  while (true) {
    // slicePoint
    size_t slicePoint = 0;
    if (istr >> slicePoint) {
      curNode->setSlicePoint(slicePoint);
    } else {
      break;
    }
    // comma
    char comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // Dim
    size_t dim = 0;
    if (istr >> dim) {
      curNode->setDimension(dim);
    } else {
      break;
    }
    // comma
    comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // isLeaf
    bool isLeaf = false;
    if (istr >> isLeaf) {
      curNode->setLeaf(isLeaf);
    } else {
      break;
    }
    // comma
    comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // Points
    std::vector<Point<ElemType>> points;
    if (istr >> points) {
      curNode->setPoints(points);
    } else {
      break;
    }
    // comma
    comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // Left node
    auto leftNode = std::make_shared<KdTreeNode<ElemType>>();
    if (istr >> leftNode) {
      if (leftNode->isInited()) {
        curNode->setLeft(leftNode);
      }
    } else {
      break;
    }
    // comma
    comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // Right node
    auto rightNode = std::make_shared<KdTreeNode<ElemType>>();
    if (istr >> rightNode) {
      if (rightNode->isInited()) {
        curNode->setRight(rightNode);
      }
    } else {
      break;
    }
    // end }
    if (!(istr >> c) || (c != '}')) {
      istr.seekg(beg, istr.beg);
      return istr;
    }
    // last
    fail = false;
    curNode->setInited(true);
    break;
  }
  if (fail) {
    istr.seekg(beg, istr.beg);
    return istr;
  }
  return istr;
}

template <typename ElemType>
using BtTuple = std::tuple<KdTreeNodePtr<ElemType>, bool>;
template <typename ElemType>
using BtStack = std::stack<BtTuple<ElemType>>;

template <typename ElemType, typename Partition = MedianPartition<ElemType>>
class KdTree : public ArithmeticTemplate<ElemType> {
public:
  KdTree();
  void insert(const std::vector<Point<ElemType>>& points);
  const Point<ElemType>& findNearestNighbor(const Point<ElemType>& point);

  inline KdTreeNodePtr<ElemType> root() { return root_; }
  inline void setRoot(KdTreeNodePtr<ElemType> root) { root_ = root; }
  inline size_t size() const { return size_; }
  inline void setSize(const size_t size) { size_ = size; }
  inline size_t sliceNodesCount() const { return sliceNodesCount_; }
  inline void setSliceNodesCount(const size_t sliceNodesCount) {
    sliceNodesCount_ = sliceNodesCount;
  }

private:
  KdTreeNodePtr<ElemType> buildPartitions(std::vector<Point<ElemType>> &points,
                                          const size_t startIdx,
                                          const size_t endIdx);
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
  Partition partition;
};

template <typename ElemType, typename Partition = MedianPartition<ElemType>>
using KdTreePtr = std::shared_ptr<KdTree<ElemType, Partition>>;

/*
 format: {sliceNodesCount,size,rootNode}
 */
template <typename ElemType, typename Partition>
std::ostream &operator<<(std::ostream &ostr,
                         const KdTreePtr<ElemType, Partition> &tree) {
  if (!tree) {
    ostr << "{}";
    return ostr;
  }
  ostr << "{";
  ostr << tree->sliceNodesCount() << ",";
  ostr << tree->size() << ",";
  ostr << tree->root();
  ostr << "}";
  return ostr;
}
/*
 format: {sliceNodesCount,size,rootNode}
 */
template <typename ElemType, typename Partition>
std::istream &operator>>(std::istream &istr,
                         KdTreePtr<ElemType, Partition> &tree) {
  if (!tree) {
    return istr;
  }
  auto beg = istr.tellg();
  char c;
  istr >> c;
  if (c != '{') {
    istr.seekg(beg, istr.beg);
    return istr;
  }
  auto beg2 = istr.tellg();
  if (istr >> c) {
    if (c == '}') {
      return istr;
    } else {
      istr.seekg(beg2, istr.beg);
    }
  }
  bool fail = true;
  while (true) {
    // sliceNodesCount
    size_t sliceNodesCount = 0;
    if (istr >> sliceNodesCount) {
      tree->setSliceNodesCount(sliceNodesCount);
    } else {
      break;
    }
    // comma
    char comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // size
    size_t size = 0;
    if (istr >> size) {
      tree->setSize(size);
    } else {
      break;
    }
    // comma
    comma = 0;
    if (!(istr >> comma) || (',' != comma)) {
      break;
    }
    // root
    auto rootNode = std::make_shared<KdTreeNode<ElemType>>();
    if (istr >> rootNode) {
      if (rootNode->isInited()) {
        tree->setRoot(rootNode);
      }
    } else {
      break;
    }
    // end }
    if (!(istr >> c) || (c != '}')) {
      istr.seekg(beg, istr.beg);
      return istr;
    }
    // last
    fail = false;
    break;
  }
  if (fail) {
    istr.seekg(beg, istr.beg);
    return istr;
  }
  return istr;
}

}//namespace uber
template <typename ElemType>
uber::KdTreeNode<ElemType>::KdTreeNode()
    : dimension_(0), slicePoint_(),
      leaf_(false),inited_(false) {}

template <typename ElemType>
size_t uber::MedianPartition<ElemType>::
getDimension(std::vector<Point<ElemType>> &points, const size_t startIdx,
           const size_t endIdx) {
  // Build range vector
  std::vector<ElemType> rangeV(points[0].size());
  for (size_t dim = 0; dim < rangeV.size(); ++dim) {
    const auto cmp =
        [&dim](const Point<ElemType> &a, const Point<ElemType> &b) {
          return a[dim] < b[dim];
        };
    std::nth_element(points.begin() + startIdx, points.begin() + startIdx,
                     points.begin() + endIdx + 1, cmp);
    const ElemType min=points[startIdx][dim];
    std::nth_element(points.begin() + startIdx, points.begin() + endIdx,
                     points.begin() + endIdx + 1, cmp);
    const ElemType max=points[endIdx][dim];
    assert(max>=min);
    rangeV[dim]=max-min;
  }
  auto maxPos = std::max_element(rangeV.begin(), rangeV.end());
  return std::distance(rangeV.begin(), maxPos);
}

template <typename ElemType>
std::tuple<size_t, size_t, ElemType> uber::MedianPartition<ElemType>::
operator()(std::vector<Point<ElemType>> &points, const size_t startIdx,
           const size_t endIdx) {
  assert(startIdx <= endIdx);
  // calculate mediat
  // sort points from startIdx to endIdx
  size_t dim=getDimension(points, startIdx, endIdx);
  const auto cmp =
      [&dim](const Point<ElemType> &a, const Point<ElemType> &b) {
        return a[dim] < b[dim];
      };
  // INFO: you could use sort but it is costly
  // std::sort(points.begin() + startIdx, points.begin() + endIdx + 1, cmp);
  size_t partitionIdx = (startIdx + endIdx) / 2;
  std::nth_element(points.begin() + startIdx, points.begin() + partitionIdx,
                   points.begin() + endIdx + 1, cmp);
  ElemType sliceValue = points[partitionIdx][dim];
  if ((endIdx - startIdx + 1) % 2 == 0) {
    std::nth_element(points.begin() + startIdx, points.begin() + partitionIdx + 1,
                     points.begin() + endIdx + 1, cmp);
    sliceValue = (sliceValue + points[partitionIdx+1][dim])/2;
  }
  return std::make_tuple(dim, partitionIdx, sliceValue);
}

template <typename ElemType, typename Partition>
uber::KdTree<ElemType, Partition>::KdTree()
    : sliceNodesCount_(0), size_(0), partition() {}

/**
 Insert list of points into KD tree
 */
template <typename ElemType, typename Partition>
void uber::KdTree<ElemType, Partition>::insert(
    const std::vector<Point<ElemType>> &points) {
  if (points.empty()) {
    return;
  }
  //Make copy so that we can sort them
  std::vector<Point<ElemType>> wPoints(points);
  // Start with full vector and 0th dimension
  root_ = buildPartitions(wPoints, 0, wPoints.size()-1);
  for (const auto& point : wPoints) {
    insert(point);
  }
}

/**
 insert given point into KD tree
 */
template <typename ElemType, typename Partition>
void uber::KdTree<ElemType, Partition>::insert(const Point<ElemType> &point) {
  KdTreeNodePtr<ElemType> itr = findLeaf(root_, point, nullptr);
  if (!itr->isLeaf()) {
    size_t dim = itr->dimension();
    auto node =  std::make_shared<KdTreeNode<ElemType>>();
    node->setInited(true);
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
  This is recursive method adds all partitions to the KD tree recursively.
  1) Finds median between start and end
  2) set slice point as median value
  3) continue populating nodes from startIdx to median-1
  4) continue populating nodes from median+1 to endIdx
 */
template <typename ElemType, typename Partition>
uber::KdTreeNodePtr<ElemType> uber::KdTree<ElemType, Partition>::buildPartitions(
    std::vector<Point<ElemType>> &points, const size_t startIdx,
    const size_t endIdx) {
  if (startIdx > points.size() || endIdx > points.size() || startIdx > endIdx) {
    return KdTreeNodePtr<ElemType>();
  }
  auto partitionRes = partition(points, startIdx, endIdx);
  size_t dimension = std::get<0>(partitionRes);
  assert(dimension < points[0].size());
  size_t partitionIdx = std::get<1>(partitionRes);
  ElemType sliceValue = std::get<2>(partitionRes);
  ++sliceNodesCount_;
  KdTreeNodePtr<ElemType> curNode = std::make_shared<KdTreeNode<ElemType>>();
  curNode->setInited(true);
  curNode->setSlicePoint(sliceValue);
  curNode->setDimension(dimension);
  // Init recursively left and right subtrees
  KdTreeNodePtr<ElemType> beforeMedian =
      buildPartitions(points, startIdx, partitionIdx - 1);
  curNode->setLeft(beforeMedian);
  KdTreeNodePtr<ElemType> afterMedian =
      buildPartitions(points, partitionIdx + 1, endIdx);
  curNode->setRight(afterMedian);
  return curNode;
}

/**
 find leaf node for given point
 @return return bottom of tree node for given point
 */
template <typename ElemType, typename Partition>
uber::KdTreeNodePtr<ElemType>
uber::KdTree<ElemType, Partition>::findLeaf(KdTreeNodePtr<ElemType> node,
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
  return node;
}

/**
 find leaf node which holds point
 algorithm:
  1) find leaf node (findLeaf)
  2) if it is leaf return
  3) if it is not leaf backtrack search in other branch
 @return Nearest neighbor for given node in greedy way.
 */
template <typename ElemType, typename Partition>
uber::KdTreeNodePtr<ElemType>
uber::KdTree<ElemType, Partition>::findLeafPoint(KdTreeNodePtr<ElemType> node,
                                 const Point<ElemType> &point,
                                 BtStack<ElemType> &btStack) {
  auto leaf = findLeaf(node, point, &btStack);
  //  while (true) {
  if (leaf->isLeaf()) {
    return leaf;
  } else if (leaf->left()) {
    btStack.pop();
    btStack.push(std::make_tuple(leaf, true));
    return findLeafPoint(leaf->left(), point, btStack);
  } else if (leaf->right()) {
    btStack.pop();
    btStack.push(std::make_tuple(leaf, false));
    return findLeafPoint(leaf->right(), point, btStack);
  } else {
    assert(0 == "Should never reach here");
#if 0
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
#endif
    //    }
  }
}
/*
 Using geometry formula between two numbers
 dist^2 = (deltaX)^2 + (deltaY)^2
 @return distance between two points
*/
template <typename ElemType, typename Partition>
ElemType uber::KdTree<ElemType, Partition>::calcDist(const Point<ElemType> &a,
                                          const Point<ElemType> &b) {
  assert(a.size() == b.size());
  ElemType dist=0;
  for (size_t i=0; i<a.size(); ++i) {
    ElemType tmp = a[i] - b[i];
    dist += (tmp*tmp);
  }
  return dist;
}
/**
 @return This provides distance between point plane and given plane(slice) value.
*/
template <typename ElemType, typename Partition>
ElemType uber::KdTree<ElemType, Partition>::calcDist(const Point<ElemType> &a,
                                          const size_t sliceValue,
                                          const size_t dim) {
  return fabs(a[dim] - sliceValue);
}

/**
 @return returns closest point from the leaf node to given point.
 */
template <typename ElemType, typename Partition>
uber::Point<ElemType> &
uber::KdTree<ElemType, Partition>::nearPoint(const KdTreeNodePtr<ElemType> &node,
                                  const Point<ElemType> &point) {
  auto cmp =
      [this, &point, &node](const Point<ElemType> &a, const Point<ElemType> &b) {
        return this->calcDist(a, point) < this->calcDist(b, point);
      };
  return *std::min_element(node->points().begin(), node->points().end(), cmp);
}
/**
 algorithm:
 1) Find leaf node based on search point
 2) mark it as a current best point and current best distance to given point.
 3) backtrack the tree depth to find better point:
    3.1) check whether parent plane is closer than current-best-point
    3.2) if it is closer, check for closer point
    3.3) if you find closer point update it as current best point
 */
template <typename ElemType, typename Partition>
const uber::Point<ElemType>&
uber::KdTree<ElemType, Partition>::findNearestNighbor(const Point<ElemType> &point) {
  // backtrack of nodes
  BtStack<ElemType> btStack;
  std::set<KdTreeNodePtr<ElemType>> visited;
  // find leaf node
  // std::cout << "Root: " << root_ << "\n";
  KdTreeNodePtr<ElemType> leaf = findLeafPoint(root_, point, btStack);
  Point<ElemType> &curNearPoint = nearPoint(leaf, point);
  ElemType curDist = calcDist(point, curNearPoint);
  // Back track for better nodes
  while (!btStack.empty()) {
    auto& tp = btStack.top();
    size_t dim = std::get<0>(tp)->dimension();
    visited.insert(std::get<0>(tp));
    btStack.pop();
    KdTreeNodePtr<ElemType> tmpNodePtr;
    // true means previous selection was left, false means right
    // hence we need to visit right in case of true otherwise left
    tmpNodePtr =
        std::get<1>(tp) ? std::get<0>(tp)->right() : std::get<0>(tp)->left();
    if (!tmpNodePtr) {
      continue;
    }
    if (visited.find(tmpNodePtr) != visited.end()) {
      continue;
    }
    // Check whether plane is closer with respet current best point
    ElemType tmpDist =
        calcDist(point, tmpNodePtr->slicePoint(), dim);
    ElemType curBestDist =
        calcDist(curNearPoint, tmpNodePtr->slicePoint(), dim);
    // if plane is closer check whether is there any better point
    if (tmpDist < curBestDist) {
      leaf = findLeafPoint(tmpNodePtr, point, btStack);
      auto &tmpCurNearPoint = nearPoint(leaf, point);
      auto tmpCurDist = calcDist(point, tmpCurNearPoint);
      // if there is better point update current best point
      if (tmpCurDist < curDist) {
        curNearPoint = tmpCurNearPoint;
        curDist = tmpCurDist;
      }
    }
  }
  return curNearPoint;
}

