#ifndef _COLORS_COLOR_NODE_H_
#   define _COLORS_COLOR_NODE_H_

#include "ColorNode.h"
#include "ColorNodeStack.h"

class ColorsColorNode : public ColorNode
{
   public:
      ColorsColorNode(ColorNodeStack &theStack, int count);
      ~ColorsColorNode();

   private:
      ColorsColorNode(const ColorsColorNode &other);
      ColorsColorNode &operator=(const ColorsColorNode &other);

   public:
      ostream &print(ostream &out) const;
      void process(ColorTable &theTable) const;

   private:
      int mCount;
      const ColorNode **mNodes;
};

#endif
