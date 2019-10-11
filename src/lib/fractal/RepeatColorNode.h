#ifndef _REPEAT_COLOR_NODE_H_
#   define _REPEAT_COLOR_NODE_H_

#include "ColorNode.h"
#include "ColorNodeStack.h"

class RepeatColorNode : public ColorNode
{
   public:
      RepeatColorNode(int repeat, ColorNodeStack &theStack, int count);
      ~RepeatColorNode();

   private:
      RepeatColorNode(const RepeatColorNode &other);
      RepeatColorNode &operator=(const RepeatColorNode &other);

   public:
      ostream &print(ostream &out) const;
      void process(ColorTable &theTable) const;

   private:
      int mRepeat;
      int mCount;
      const ColorNode **mNodes;
};

#endif
