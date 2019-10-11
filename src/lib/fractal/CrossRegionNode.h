#ifndef _CROSS_REGION_NODE_H_
#   define _CROSS_REGION_NODE_H_

#include "RegionNode.h"

class DoubleNode;

class CrossRegionNode : public RegionNode
{
   public:
      CrossRegionNode(
         const ComplexNode *p1,
         const ComplexNode *p2,
         const DoubleNode  *barWidth,
         const DoubleNode  *barHeight
      );

      virtual ~CrossRegionNode();

      virtual int contains(
         const ComplexNode *point
      ) const;

      virtual ostream &print(ostream &out) const;


   private:
      CrossRegionNode(const CrossRegionNode &);
      CrossRegionNode& operator=(const CrossRegionNode &);

      const ComplexNode *mP1;
      const ComplexNode *mP2;
      const DoubleNode  *mBarWidth;
      const DoubleNode  *mBarHeight;
};

#endif
