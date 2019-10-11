#ifndef _DEFINE_COLOR_NODE_H_
#   define _DEFINE_COLOR_NODE_H_

#include "ColorNode.h"
#include "ColorNodeStack.h"

class DefineColorNode : public ColorNode
{
   public:
      DefineColorNode(int start, ColorNodeStack &theStack, int count);
      DefineColorNode(ColorNodeStack &theStack, int count);
      ~DefineColorNode();

   private:
      DefineColorNode(const DefineColorNode &other);
      DefineColorNode &operator=(const DefineColorNode &other);

   public:
      ostream &print(ostream &out) const;
      void process(ColorTable &theTable) const;

   private:
      void acquireFromStack(ColorNodeStack &theStack);
      const ColorNode **mNodes;
      int mStart;
      int mCount;
      enum { NOT_SPECIFIED = -1 };
};

#endif
