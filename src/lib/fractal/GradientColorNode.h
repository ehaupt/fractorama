#ifndef _GRADIENT_COLOR_NODE_H_
#   define _GRADIENT_COLOR_NODE_H_

#include "ColorNode.h"
#include "ColorStack.h"

#include <string>

using std::string;

class GradientColorNode : public ColorNode
{
   public:
      static GradientColorNode *create(
         int size,
         ColorStack &theStack,
         int count,
         string &errMsg
      );
      ~GradientColorNode();

   protected:
      GradientColorNode(int size, ColorStack &theStack, int count);

   private:
      GradientColorNode(const GradientColorNode &other);
      GradientColorNode &operator=(const GradientColorNode &other);

   public:
      ostream &print(ostream &out) const;
      void process(ColorTable &theTable) const;

   private:
      int mSize;
      int **mTable;
};

#endif
