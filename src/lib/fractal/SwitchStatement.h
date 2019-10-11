#ifndef _SWITCH_STATEMENT_H_
#   define _SWITCH_STATEMENT_H_

#include "Statement.h"

class DoubleNode;
class CompoundStatement;
class CaseEntry;

class SwitchStatement : public Statement
{
   public:
      SwitchStatement(
         const DoubleNode *node
      );

      ~SwitchStatement();

      void caseBegin();
      void caseAddNode(const DoubleNode *node);
      void caseAddStatements(const CompoundStatement *statement);
      void caseSetBreak();

      int execute(
         InfiniteLoopCallback *callback,
         LoopControl *control
      )  const;

      ostream &print(ostream &out) const;

   private:
      const DoubleNode *mNode;
      CaseEntry **mEntries;
      int mCount;
      int mHasDefault;
};
#endif
