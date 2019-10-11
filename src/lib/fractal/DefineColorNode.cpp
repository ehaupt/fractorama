#include "DefineColorNode.h"
#include "ColorTable.h"
#include "dmemory.h"

DefineColorNode::DefineColorNode(
   int start, ColorNodeStack &theStack, int count
) : mNodes(0), mStart(start), mCount(count)
{
   acquireFromStack(theStack);
}

DefineColorNode::DefineColorNode(
   ColorNodeStack &theStack, int count
) : mNodes(0), mStart(NOT_SPECIFIED), mCount(count)
{
   acquireFromStack(theStack);
}

DefineColorNode::~DefineColorNode()
{
   for(int i = 0; i < mCount; i ++)
      DDELETE(mNodes[i]);

   DADELETE(mNodes);
}

void DefineColorNode::acquireFromStack(ColorNodeStack &theStack)
{
   DNEW(mNodes, const ColorNode *[mCount]);

   for(int i = mCount - 1; i >= 0; i --)
      mNodes[i] = theStack.pop();
}

ostream &DefineColorNode::print(ostream &out) const
{
   out << "define";

   if(mStart != NOT_SPECIFIED)
      out << "(" << mStart << ")";

   out << "{ ";

   for(int i = 0; i < mCount; i ++)
      mNodes[i]->print(out);

   out << " }";

   return(out);
}

void DefineColorNode::process(ColorTable &theTable) const
{
   if(mStart != NOT_SPECIFIED)
      theTable.setCurrentIndex(mStart);

   for(int i = 0; i < mCount; i ++)
      mNodes[i]->process(theTable);
}
