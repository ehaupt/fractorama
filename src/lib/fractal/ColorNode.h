#ifndef _COLOR_NODE_H_
#   define _COLOR_NODE_H_

#include <iostream>

using std::ostream;

class ColorTable;

class ColorNode
{
   public:
      virtual ~ColorNode();

   public:
      virtual ostream &print(ostream &out) const = 0;
      virtual void process(ColorTable &theTable) const = 0;
};

ostream &operator<<(ostream &out, const ColorNode &theNode);

#endif
