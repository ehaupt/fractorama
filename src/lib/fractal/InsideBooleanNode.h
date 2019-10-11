#ifndef _INSIDE_BOOLEAN_NODE_H_
#   define _INSIDE_BOOLEAN_NODE_H_

#include "BooleanNode.h"

class ComplexNode;
class RegionNode;

class InsideBooleanNode : public BooleanNode
{
   public:
      InsideBooleanNode(const ComplexNode *point, const RegionNode *region);
      virtual ~InsideBooleanNode();

      virtual int evaluate() const;

      virtual ostream &print(ostream &out) const;

  private:
      InsideBooleanNode(const InsideBooleanNode &);
      InsideBooleanNode &operator=(const InsideBooleanNode &);

      const ComplexNode *mPoint;
      const RegionNode  *mRegion;
};

#endif
