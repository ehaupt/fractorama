// Local Headers

#include "RGBSetColorStatement.h"
#include "DoubleNode.h"
#include "ColorEnvironment.h"
#include "dmemory.h"

RGBSetColorStatement::RGBSetColorStatement(
   const DoubleNode *redNode,
   const DoubleNode *greenNode,
   const DoubleNode *blueNode,
   ColorEnvironment &env
) :
   mRed(redNode),
   mGreen(greenNode),
   mBlue(blueNode),
   mEnv(env)
{
}

RGBSetColorStatement::~RGBSetColorStatement()
{
   DDELETE(mRed);
   DDELETE(mGreen);
   DDELETE(mBlue);
}

int RGBSetColorStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *
) const
{
   int red     = (int)(mRed->evaluate());
   int green   = (int)(mGreen->evaluate());
   int blue    = (int)(mBlue->evaluate());

   if(red   < 0 || red   > 255 ||
      green < 0 || green > 255 ||
      blue  < 0 || blue  > 255)
   {
      mEnv.foundInvalidColor();
   }
   else
   {
      mEnv.setRGB(red, green, blue);
   }

   return(TRUE);
}

ostream &RGBSetColorStatement::print(ostream &out) const
{
   out << "set_color(";
   mRed->print(out);
   out << ", ";
   mGreen->print(out);
   out << ", ";
   mBlue->print(out);
   out << ")";
   return(out);
}
