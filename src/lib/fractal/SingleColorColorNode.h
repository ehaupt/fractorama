#ifndef _SINGLE_COLOR_COLOR_NODE_H_
#   define _SINGLE_COLOR_COLOR_NODE_H_

#include "ColorNode.h"

class SingleColorColorNode : public ColorNode
{
   public:
      SingleColorColorNode(int red, int green, int blue);
      ~SingleColorColorNode();

   private:
      SingleColorColorNode(const SingleColorColorNode &other);
      SingleColorColorNode &operator=(const SingleColorColorNode &other);

   public:
      ostream &print(ostream &out) const;
      void process(ColorTable &theTable) const;

   private:
      int mRed;
      int mGreen;
      int mBlue;
};

#endif
