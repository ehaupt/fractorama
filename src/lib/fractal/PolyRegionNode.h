#ifndef _POLY_REGION_NODE_H_
#   define _POLY_REGION_NODE_H_

#include "RegionNode.h"

class PolyRegionNode : public RegionNode
{
   public:
      PolyRegionNode(const ComplexNode **points, int count);

      virtual ~PolyRegionNode();

      virtual int contains(
         const ComplexNode *point
      ) const;

      virtual ostream &print(ostream &out) const;

   private:
      PolyRegionNode(const PolyRegionNode &);
      PolyRegionNode& operator=(const PolyRegionNode &);

      const ComplexNode **mPoints;
      int mCount;
      double *mX;
      double *mY;
};

#endif
