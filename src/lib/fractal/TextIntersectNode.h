#ifndef _TEXT_INTERSECT_NODE_H_
#   define _TEXT_INTERSECT_NODE_H_

#include "DoubleNode.h"

class ComplexNode;
class SegmentList;

class TextIntersectNode : public DoubleNode
{
   public:
      TextIntersectNode(
         const char *text,
         const ComplexNode *originPtr,
         const DoubleNode  *heightPtr,
         const DoubleNode  *thicknessPtr,
         const ComplexNode *pointPtr
      );

      ~TextIntersectNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

   private:
      char *mText;
      SegmentList **mValues;
      int mNumValues;
      const ComplexNode *mOriginPtr;
      const DoubleNode  *mHeightPtr;
      const DoubleNode  *mThicknessPtr;
      const ComplexNode *mPointPtr;
};

#endif
