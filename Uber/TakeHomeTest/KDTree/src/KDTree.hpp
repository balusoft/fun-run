/*
*/

#include <vector>
#include <type_traits>
#include <memory>

namespace uber {
template <typename ElemType>
using Point = std::vector<ElemType>;
template <typename ElemType>
class KdTreeNode {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
  KdTreeNode(const size_t dimension);
  void setRight(std::shared_ptr<KdTreeNode>& right) { right_ = right; }
  std::shared_ptr<KdTreeNode> right() { return right_; }
  void setLeft(std::shared_ptr<KdTreeNode>& left) { left_ = left; }
  std::shared_ptr<KdTreeNode> left() { return left_; }
private:
  size_t dimensions_;
  Point<ElemType> point_;
  std::shared_ptr<KdTreeNode> right_;
  std::shared_ptr<KdTreeNode> left_;
};

template <typename ElemType>
class KdTree {
public:
  static_assert(std::is_arithmetic<ElemType>::value,
                "Required to be integer or floating point primitive types");
  KdTree();
  KdTree(const std::string &filepath);

  void insert(const Point<ElemType>& point);
  Point<ElemType> findNearestNighbor(const Point<ElemType>& point);
  int save();
private:
  std::shared_ptr<KdTreeNode<ElemType>> root_;
};
};

template <typename ElemType>
uber::KdTreeNode<ElemType>::KdTreeNode(size_t dimension)
    : dimensions_(dimension), point_(dimension, 0), right_(), left_() {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree() {}

template <typename ElemType>
uber::KdTree<ElemType>::KdTree(const std::string &filepath) {}

template <typename ElemType>
void uber::KdTree<ElemType>::insert(const Point<ElemType>& point) {}

template <typename ElemType>
uber::Point<ElemType>
uber::KdTree<ElemType>::findNearestNighbor(const Point<ElemType> &point) {
  return point;
}

template <typename ElemType>
int uber::KdTree<ElemType>::save() {
  return 0;
}
