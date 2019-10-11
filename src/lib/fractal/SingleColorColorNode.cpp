#include "SingleColorColorNode.h"
#include "ColorTable.h"

SingleColorColorNode::SingleColorColorNode(int red, int green, int blue)
   : mRed(red), mGreen(green), mBlue(blue) {}

SingleColorColorNode::~SingleColorColorNode() {}

ostream &SingleColorColorNode::print(ostream &out) const
{
   out << "[" << mRed << " " << mGreen << " " << mBlue << "]";

   return(out);
}

void SingleColorColorNode::process(ColorTable &theTable) const
{
   theTable.addEntry(mRed, mGreen, mBlue);
}
