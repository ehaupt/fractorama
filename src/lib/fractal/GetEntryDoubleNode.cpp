// C/C++ headers

#include <string.h>

// Local headers

#include "GetEntryDoubleNode.h"
#include "ColorEnvironment.h"
#include "dmemory.h"

GetEntryDoubleNode::GetEntryDoubleNode(
   char *name,
   WhichEntry which,
   const DoubleNode *nodePtr,
   ColorEnvironment &env
)  :
   mName(0), mWhich(which), mNodePtr(nodePtr), mEnv(env)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

GetEntryDoubleNode::~GetEntryDoubleNode()
{
   DADELETE(mName);
   DDELETE(mNodePtr);
}

double GetEntryDoubleNode::evaluate()  const
{
   int red   = 0;
   int green = 0;
   int blue  = 0;

   mEnv.getRGB((int)mNodePtr->evaluate(), &red, &green, &blue);

   double value = 0.0;

   if(mWhich == GET_RED)        value = (double)red;
   else if(mWhich == GET_GREEN) value = (double)green;
   else if(mWhich == GET_BLUE)  value = (double)blue;

   return(value);
}

ostream &GetEntryDoubleNode::print(ostream &out) const
{
   out << mName << "(";
   mNodePtr->print(out);
   out << ")";

   return(out);
}

GetEntryDoubleNode::WhichEntry GetEntryDoubleNode::lookup(char *name)
{
   struct Table
   {
      WhichEntry which;
      char *name;
   };

   static Table t[] =
   {
      { GET_RED,   "get_entry_red"   },
      { GET_GREEN, "get_entry_green" },
      { GET_BLUE,  "get_entry_blue"  }
   };

   static int size = sizeof(t) / sizeof(t[0]);

   for(int i = 0; i < size; i ++)
      if(strcmp(t[i].name, name) == 0)
         return(t[i].which);

   return(INVALID);
}
