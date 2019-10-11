// Local Headers

#include "IndexedSetColorStatement.h"
#include "DoubleNode.h"
#include "ColorEnvironment.h"
#include "dmemory.h"

IndexedSetColorStatement::IndexedSetColorStatement(
   const DoubleNode *node,
   ColorEnvironment &env
) :
   mNode(node), mEnv(env)
{
}

IndexedSetColorStatement::~IndexedSetColorStatement()
{
   DDELETE(mNode);
}

int IndexedSetColorStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *
) const
{
   int red   = 0;
   int green = 0;
   int blue  = 0;

   if(mEnv.getRGB((int)mNode->evaluate(), &red, &green, &blue))
      mEnv.setRGB(red, green, blue);

   return(TRUE);
}

ostream &IndexedSetColorStatement::print(ostream &out) const
{
   out << "set_color(";
   mNode->print(out);
   out << ")";
   return(out);
}
