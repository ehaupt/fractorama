#ifndef _ELLIPSE_REGION_NODE_H_
#   define _ELLIPSE_REGION_NODE_H_

#include "RegionNode.h"

class DoubleNode;

class EllipseRegionNode : public RegionNode
{
   public:
      EllipseRegionNode(
         const ComplexNode *center,
         const DoubleNode *xradius,
         const DoubleNode *yradius
      );

      virtual ~EllipseRegionNode();

      virtual int contains(const ComplexNode *point) const;

      virtual ostream &print(ostream &out) const;

   private:
      EllipseRegionNode(const EllipseRegionNode &);
      EllipseRegionNode& operator=(const EllipseRegionNode &);

      const ComplexNode *mCenter;
      const DoubleNode  *mXRadius;
      const DoubleNode  *mYRadius;
};

#endif
