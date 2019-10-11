#ifndef _FRACTAL_H_
#   define _FRACTAL_H_

// Forward Declarations

class BooleanNode;
class Statement;
class InfiniteLoopCallback;

#include "ColorEnvironment.h"
#include "ComplexVariables.h"
#include "DoubleVariables.h"
#include "ColorTable.h"
#include "rowsupplier.h"


class Fractal : public ColorEnvironment, public RowSupplier
{
   public:
      Fractal();
      virtual ~Fractal();

      // Methods related to the 'mapping' section

      void setComplexCoordinates(
         double xStart, double yStart, double xEnd, double yEnd
      );

      double getXStart() const;
      double getYStart() const;
      double getXEnd() const;
      double getYEnd() const;

      void setDimensions(
         int width, int height
      );

      int getWidth() const;
      int getHeight() const;

      // Fulfill our role as 'ColorEnvironment'

      ColorTable &getColorTable();
      void foundInvalidColor();
      void setRGB(int red, int green, int blue);
      int getRGB(int index, int *red, int *green, int *blue);

      // Variable related methods

      ComplexVariables &getComplexVariables();
      DoubleVariables  &getDoubleVariables();

      // Methods to set our statement variables

      void setBeforeStatement(const Statement *s);
      void setStatement(const Statement *s);
      void setAfterStatement(const Statement *s);

      // Method to set our boolean stopping condition

      void setCondition(const BooleanNode *theCondition);

      // Methods for processing our formula row by row

      void begin();
      int hasMoreRows() const;

      // This method fulfills our role as 'RowSupplier'

      unsigned char *nextRow(InfiniteLoopCallback *callback);

      // Were there any invalid colors

      int getInvalidColorCount() const;

      friend ostream &operator<<(ostream &out, const Fractal &theFractal);

   private:
      Fractal(const Fractal &other);
      Fractal &operator=(const Fractal &other);

      static const char *CURRENT;
      static const char *COUNT;
      static const char *MAPPING_X_START;
      static const char *MAPPING_Y_START;
      static const char *MAPPING_X_END;
      static const char *MAPPING_Y_END;
      static const char *MAPPING_X_PIXELS;
      static const char *MAPPING_Y_PIXELS;
      static const char *_M_E;
      static const char *_M_LOG2E;
      static const char *_M_LOG10E;
      static const char *_M_LN2;
      static const char *_M_LN10;
      static const char *_M_PI;
      static const char *_M_PI_2;
      static const char *_M_PI_4;
      static const char *_M_1_PI;
      static const char *_M_2_PI;
      static const char *_M_2_SQRTPI;
      static const char *_M_SQRT2;
      static const char *_M_SQRT1_2;
      static const char *CURRENT_ROW;
      static const char *CURRENT_COLUMN;

      // Mapping related variables

      double mXStart, mYStart, mXEnd, mYEnd;
      int mWidth, mHeight;

      // Color Table

      ColorTable mColorTable;

      // Variables related to our set of complex and double variables

      ComplexVariables mComplexVariables;
      DoubleVariables  mDoubleVariables;

      // Statements

      const Statement *mBeforeStatement;
      const Statement *mStatement;
      const Statement *mAfterStatement;

      // boolean stopping condition

      const BooleanNode *mCondition;

      double mY;
      int mRowNumber;
      unsigned char *mRow;
      double mXDelta;
      double mYDelta;
      int mInvalidColorCount;
      int mRed, mGreen, mBlue;
      dcomplex *mCurrentPtr;
      double *mCountPtr;
      double *mMappingXStartPtr;
      double *mMappingYStartPtr;
      double *mMappingXEndPtr;
      double *mMappingYEndPtr;
      double *mMappingXPixelsPtr;
      double *mMappingYPixelsPtr;
      double *mM_EPtr;
      double *mM_LOG2EPtr;
      double *mM_LOG10EPtr;
      double *mM_LN2Ptr;
      double *mM_LN10Ptr;
      double *mM_PIPtr;
      double *mM_PI_2Ptr;
      double *mM_PI_4Ptr;
      double *mM_1_PIPtr;
      double *mM_2_PIPtr;
      double *mM_2_SQRTPIPtr;
      double *mM_SQRT2Ptr;
      double *mM_SQRT1_2Ptr;
      double *mCurrentRowPtr;
      double *mCurrentColumnPtr;
};

#endif
