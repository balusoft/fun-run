/*
Uber Take Home Test
*/
#ifndef _UBER_LIB_KDTREE_HPP_
#define _UBER_LIB_KDTREE_HPP_

#include <lib/Noncopyable.hpp>

#include <algorithm>
#include <cassert>
#include <vector>
#include <type_traits>
#include <memory>
#include <stack>
#include <set>
#include <iostream>

namespace uber {
// Point Definition
template <typename ElemType>
using Point = std::vector<ElemType>;

// Allow only numerical types
template <typename ElemType>
class ArithmeticTemplate : public Noncopyable {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
};

// KdTreeNode forward declaration to define pointer
template <typename ElemType>
class KdTreeNode;

// Define KdTreeNodePtr
template <typename ElemType>
using KdTreeNodePtr = std::shared_ptr<KdTreeNode<ElemType>>;

/**
 This class contains tree node definition which contains
 metadata(slicePoint, node-dimension, isLeaf) and left, right subtrees
*/
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
  inline void setSlicePoint(const double slice) {
    slicePoint_ = slice;
  }
  inline double slicePoint() const { return slicePoint_; }
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
  double slicePoint_;
  bool leaf_;
  bool inited_;
  KdTreeNodePtr<ElemType> left_; // values < slicePoint
  KdTreeNodePtr<ElemType> right_; // values >= slicePoint
};

/**
 This is default partition implementation. Which uses
 chooses dimension based biggest range as defined in problem.
 And, partitions the points based on median.
 */
template <typename ElemType> class MedianPartition {
public:
  /**
    @return (dimension, partiotion index, slice-value)
   */
  std::tuple<size_t, size_t, double>
  operator()(std::vector<Point<ElemType>> &points, const size_t startIdx,
             const size_t endIdx);

private:
  size_t getDimension(std::vector<Point<ElemType>> &points, const size_t startIdx,
                    const size_t endIdx);
};

/**
Useful typedefs to hold backtrack of tree traversal
*/
template <typename ElemType>
using BtTuple = std::tuple<KdTreeNodePtr<ElemType>, bool>;
template <typename ElemType>
using BtStack = std::stack<BtTuple<ElemType>>;

/*
 This provides important interfaces like KdTree, points insertion and finding
 nearest neighbor. By default this class uses MedianPartition<ElemType> to
 choose dimension and to partition points. User can customize Partition 
 */
template <typename ElemType, typename Partition = MedianPartition<ElemType>>
class KdTree : public ArithmeticTemplate<ElemType> {
public:
  KdTree();
  /**
   Inserts all points into KdTree. This happens in two stages
   1) Builds partion tree by using Partition<ElemType>::operator()
   2) Inserts points to leaf nodes
   */
  void insert(const std::vector<Point<ElemType>>& points);

  /**
   @return nearest neighbor for given point and its distance.
   */
  const std::tuple<Point<ElemType>, double>
  findNearestNighbor(const Point<ElemType> &point);

  /* TODO: May be no need to expose thsese, just make operators friends */
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

}//namespace uber


// All template definitions are defined in following header
#define _USE_FOR_KDTREE_HPP_TMPL_IMPL_H_
#include "KDTree-impl.hpp"

#endif //_UBER_LIB_KDTREE_HPP_
