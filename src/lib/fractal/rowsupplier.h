#ifndef _ROW_SUPPLIER_H_
#   define _ROW_SUPPLIER_H_

class InfiniteLoopCallback;

class RowSupplier
{
   public:
      virtual ~RowSupplier() {}
      virtual unsigned char *nextRow(InfiniteLoopCallback *callback) = 0;
};

#endif
