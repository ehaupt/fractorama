// Local Headers

#include "HSVSetColorStatement.h"
#include "DoubleNode.h"
#include "ColorEnvironment.h"
#include "dmemory.h"

HSVSetColorStatement::HSVSetColorStatement(
   const DoubleNode *hNode,
   const DoubleNode *sNode,
   const DoubleNode *vNode,
   ColorEnvironment &env
) :
   mH(hNode),
   mS(sNode),
   mV(vNode),
   mEnv(env)
{
}

HSVSetColorStatement::~HSVSetColorStatement()
{
   DDELETE(mH);
   DDELETE(mS);
   DDELETE(mV);
}

int HSVSetColorStatement::execute(
   InfiniteLoopCallback *,
   LoopControl *
) const
{
   double r = 0.0;
   double g = 0.0;
   double b = 0.0;

   HSVSetColorStatement::hsv2rgb(
      mH->evaluate(), mS->evaluate(), mV->evaluate(), &r, &g, &b
   );

   int red   = (int)r;
   int green = (int)g;
   int blue  = (int)b;

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

void HSVSetColorStatement::hsv2rgb(
   double h, double s, double v, double *r, double *g, double *b
)
{
   int hValue = (int)h;
   int sValue = (int)s;
   int vValue = (int)v;

   if(hValue < -1 || sValue < 0 || sValue > 255 || vValue < 0 || vValue > 255)
   {
      *r = *g = *b = 0.0;
   }
   else
   {
      *r = *g = *b = vValue;

      if(sValue != 0 && hValue != -1)
      {
         if(hValue >= 360)
            hValue %= 360;

         unsigned int f = hValue % 60;
         hValue        /= 60;

         unsigned int p = (unsigned int)((2*vValue*(255-sValue)+255)/510);

         if(hValue & 1)
         {
            unsigned int q = (2*vValue*(15300-sValue*f)+15300)/30600;

            switch(hValue)
            {
               case 1: *r = q;      *g = vValue; *b = p;      break;
               case 3: *r = p;      *g = q;      *b = vValue; break;
               case 5: *r = vValue; *g = p;      *b = q;      break;
            }
         }
         else
         {
            unsigned int t = (2*vValue*(15300-(sValue*(60-f)))+15300)/30600;

            switch(hValue)
            {
               case 0: *r = vValue; *g = t;      *b = p;      break;
               case 2: *r = p;      *g = vValue; *b = t;      break;
               case 4: *r = t;      *g = p;      *b = vValue; break;
            }
         }
      }
   }
}

ostream &HSVSetColorStatement::print(ostream &out) const
{
   out << "set_color_hsv(";
   mH->print(out);
   out << ", ";
   mS->print(out);
   out << ", ";
   mV->print(out);
   out << ")";
   return(out);
}
