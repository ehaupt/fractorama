#ifndef _REGION_NODE_H_
#   define _REGION_NODE_H_

#include <iostream>

using std::ostream;

class ComplexNode;

class RegionNode
{
   public:
      RegionNode();
      virtual ~RegionNode();

      virtual int contains(const ComplexNode *point) const = 0;

      virtual ostream &print(ostream &out) const = 0;

   private:
      RegionNode(const RegionNode &);
      RegionNode& operator=(const RegionNode &);
};

#endif
