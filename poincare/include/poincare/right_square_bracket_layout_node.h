#ifndef POINCARE_RIGHT_SQUARE_BRACKET_LAYOUT_NODE_H
#define POINCARE_RIGHT_SQUARE_BRACKET_LAYOUT_NODE_H

#include <poincare/square_bracket_layout_node.h>
#include <poincare/layout_helper.h>
#include <poincare/serialization_helper.h>

namespace Poincare {

class RightSquareBracketLayoutNode : public SquareBracketLayoutNode {
public:
  using SquareBracketLayoutNode::SquareBracketLayoutNode;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override {
    return SerializationHelper::Char(buffer, bufferSize, ']');
  }
  bool isRightBracket() const override { return true; }

  // TreeNode
  static RightSquareBracketLayoutNode * FailedAllocationStaticNode();
  RightSquareBracketLayoutNode * failedAllocationStaticNode() override { return FailedAllocationStaticNode(); }
  size_t size() const override { return sizeof(RightSquareBracketLayoutNode); }
#if POINCARE_TREE_LOG
  virtual void logNodeName(std::ostream & stream) const {
    stream << "RightSquareBracketLayout";
  }
#endif

protected:
  void render(KDContext * ctx, KDPoint p, KDColor expressionColor, KDColor backgroundColor) override;
};

class RightSquareBracketLayoutRef : public LayoutReference {
public:
  RightSquareBracketLayoutRef() : LayoutReference(TreePool::sharedPool()->createTreeNode<RightSquareBracketLayoutNode>()) {}


};

}

#endif
