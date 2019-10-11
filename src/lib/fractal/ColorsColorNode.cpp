#include "ColorsColorNode.h"
#include "dmemory.h"

ColorsColorNode::ColorsColorNode(ColorNodeStack &theStack, int count) :
   mCount(count), mNodes(0)
{
   DNEW(mNodes, const ColorNode *[mCount]);

   for(int i = mCount - 1; i >= 0; i --)
      mNodes[i] = theStack.pop();
}

ColorsColorNode::~ColorsColorNode()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mNodes[i]);

   DADELETE(mNodes);
}

ostream &ColorsColorNode::print(ostream &out) const
{
   for(int i = 0; i < mCount; i ++)
      mNodes[i]->print(out);

   return(out);
}

void ColorsColorNode::process(ColorTable &theTable) const
{
   for(int i = 0; i < mCount; i ++)
      mNodes[i]->process(theTable);
}
