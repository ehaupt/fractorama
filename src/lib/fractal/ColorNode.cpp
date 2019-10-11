#include "ColorNode.h"

ColorNode::~ColorNode() {}

ostream &operator<<(ostream &out, const ColorNode &theNode)
{
   return(theNode.print(out));
}
