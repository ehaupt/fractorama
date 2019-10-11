#ifndef _GET_ENTRY_DOUBLE_NODE_H_
#   define _GET_ENTRY_DOUBLE_NODE_H_

#include "DoubleNode.h"

class ColorEnvironment;

class GetEntryDoubleNode : public DoubleNode
{
   public:
      typedef enum
      {
         INVALID, GET_RED, GET_GREEN, GET_BLUE
      }  WhichEntry;

      GetEntryDoubleNode(
         char *name,
         WhichEntry which,
         const DoubleNode *nodePtr,
         ColorEnvironment &env
      );

      ~GetEntryDoubleNode();

      double evaluate() const;

      ostream &print(ostream &out) const;

      static WhichEntry lookup(char *name);

  private:
      GetEntryDoubleNode(const GetEntryDoubleNode &);
      GetEntryDoubleNode &operator=(const GetEntryDoubleNode &);

      char *mName; 
      WhichEntry mWhich;
      const DoubleNode *mNodePtr;
      ColorEnvironment &mEnv;
};

#endif
