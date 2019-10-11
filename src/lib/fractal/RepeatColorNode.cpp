#include "RepeatColorNode.h"
#include "dmemory.h"

RepeatColorNode::RepeatColorNode(
   int repeat, ColorNodeStack &theStack, int count
)
   : mRepeat(repeat), mCount(count), mNodes(0)
{
   DNEW(mNodes, const ColorNode *[mCount]);

   for(int i = mCount - 1; i >= 0; i --)
      mNodes[i] = theStack.pop();
}

RepeatColorNode::~RepeatColorNode()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mNodes[i]);

   DADELETE(mNodes);
}

ostream &RepeatColorNode::print(ostream &out) const
{
   out << "repeat(" << mRepeat << ") { ";

   for(int i = 0; i < mCount; i ++)
      mNodes[i]->print(out);

   out << " }";

   return(out);
}

void RepeatColorNode::process(ColorTable &theTable) const
{
   for(int i = 0; i < mRepeat; i ++)
   {
      for(int j = 0; j < mCount; j ++)
         mNodes[j]->process(theTable);
   }
}
