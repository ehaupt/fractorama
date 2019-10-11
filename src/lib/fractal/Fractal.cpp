// C/C++ Headers

#include <iostream>

using std::ostream;
using std::endl;

// Local Headers

#include "Fractal.h"
#include "InfiniteLoopCallback.h"
#include "Statement.h"
#include "BooleanNode.h"
#include "dmemory.h"

/*****************************************************************************
 * Initialize class-level variables for 'Fractal'
 *****************************************************************************/

const char *Fractal::CURRENT          = "current";
const char *Fractal::COUNT            = "count";
const char *Fractal::MAPPING_X_START  = "mapping_x_start";
const char *Fractal::MAPPING_Y_START  = "mapping_y_start";
const char *Fractal::MAPPING_X_END    = "mapping_x_end";
const char *Fractal::MAPPING_Y_END    = "mapping_y_end";
const char *Fractal::MAPPING_X_PIXELS = "mapping_x_pixels";
const char *Fractal::MAPPING_Y_PIXELS = "mapping_y_pixels";
const char *Fractal::_M_E             = "m_e";
const char *Fractal::_M_LOG2E         = "m_log2e";
const char *Fractal::_M_LOG10E        = "m_log10e";
const char *Fractal::_M_LN2           = "m_ln2";
const char *Fractal::_M_LN10          = "m_ln10";
const char *Fractal::_M_PI            = "m_pi";
const char *Fractal::_M_PI_2          = "m_pi_2";
const char *Fractal::_M_PI_4          = "m_pi_4";
const char *Fractal::_M_1_PI          = "m_1_pi";
const char *Fractal::_M_2_PI          = "m_2_pi";
const char *Fractal::_M_2_SQRTPI      = "m_2_sqrtpi";
const char *Fractal::_M_SQRT2         = "m_sqrt2";
const char *Fractal::_M_SQRT1_2       = "m_sqrt1_2";
const char *Fractal::CURRENT_ROW      = "current_row";
const char *Fractal::CURRENT_COLUMN   = "current_column";

/*****************************************************************************
 * Definition of class 'Fractal'
 *****************************************************************************/

Fractal::Fractal() :
   mXStart(0.0), mYStart(0.0), mXEnd(0.0), mYEnd(0.0),
   mWidth(0), mHeight(0),
   mBeforeStatement(0),
   mStatement(0),
   mAfterStatement(0),
   mCondition(0),
   mY(0.0),
   mRowNumber(0),
   mRow(0),
   mXDelta(0),
   mYDelta(0),
   mInvalidColorCount(0),
   mRed(0), mGreen(0), mBlue(0),
   mCurrentPtr(0),
   mCountPtr(0),
   mMappingXStartPtr(0),
   mMappingYStartPtr(0),
   mMappingXEndPtr(0),
   mMappingYEndPtr(0),
   mMappingXPixelsPtr(0),
   mMappingYPixelsPtr(0),
   mM_EPtr(0),
   mM_LOG2EPtr(0),
   mM_LOG10EPtr(0),
   mM_LN2Ptr(0),
   mM_LN10Ptr(0),
   mM_PIPtr(0),
   mM_PI_2Ptr(0),
   mM_PI_4Ptr(0),
   mM_1_PIPtr(0),
   mM_2_PIPtr(0),
   mM_2_SQRTPIPtr(0),
   mM_SQRT2Ptr(0),
   mM_SQRT1_2Ptr(0),
   mCurrentRowPtr(0),
   mCurrentColumnPtr(0)
{
   // Ensure mComplexVariables and mDoubleVariables contain
   // our pre-defined values so that while we're parsing when we check
   // to see if they are defined we will succeed

   mCurrentPtr        = mComplexVariables.assign(CURRENT);
   mCountPtr          = mDoubleVariables.assign(COUNT);
   mMappingXStartPtr  = mDoubleVariables.assign(MAPPING_X_START);
   mMappingYStartPtr  = mDoubleVariables.assign(MAPPING_Y_START);
   mMappingXEndPtr    = mDoubleVariables.assign(MAPPING_X_END);
   mMappingYEndPtr    = mDoubleVariables.assign(MAPPING_Y_END);
   mMappingXPixelsPtr = mDoubleVariables.assign(MAPPING_X_PIXELS);
   mMappingYPixelsPtr = mDoubleVariables.assign(MAPPING_Y_PIXELS);
   mM_EPtr            = mDoubleVariables.assign(_M_E);
   mM_LOG2EPtr        = mDoubleVariables.assign(_M_LOG2E);
   mM_LOG10EPtr       = mDoubleVariables.assign(_M_LOG10E);
   mM_LN2Ptr          = mDoubleVariables.assign(_M_LN2);
   mM_LN10Ptr         = mDoubleVariables.assign(_M_LN10);
   mM_PIPtr           = mDoubleVariables.assign(_M_PI);
   mM_PI_2Ptr         = mDoubleVariables.assign(_M_PI_2);
   mM_PI_4Ptr         = mDoubleVariables.assign(_M_PI_4);
   mM_1_PIPtr         = mDoubleVariables.assign(_M_1_PI);
   mM_2_PIPtr         = mDoubleVariables.assign(_M_2_PI);
   mM_2_SQRTPIPtr     = mDoubleVariables.assign(_M_2_SQRTPI);
   mM_SQRT2Ptr        = mDoubleVariables.assign(_M_SQRT2);
   mM_SQRT1_2Ptr      = mDoubleVariables.assign(_M_SQRT1_2);
   mCurrentRowPtr     = mDoubleVariables.assign(CURRENT_ROW);
   mCurrentColumnPtr  = mDoubleVariables.assign(CURRENT_COLUMN);
}

Fractal::~Fractal()
{
   DDELETE(mBeforeStatement);
   DDELETE(mStatement);
   DDELETE(mAfterStatement);
   DDELETE(mCondition);
   DADELETE(mRow);
}

void Fractal::setComplexCoordinates(
   double xStart, double yStart, double xEnd, double yEnd
)
{
   mXStart = xStart;
   mYStart = yStart;
   mXEnd   = xEnd;
   mYEnd   = yEnd;
}

double Fractal::getXStart() const { return(mXStart); }
double Fractal::getYStart() const { return(mYStart); }
double Fractal::getXEnd()   const { return(mXEnd);   }
double Fractal::getYEnd()   const { return(mYEnd);   }

void Fractal::setDimensions(int width, int height)
{
   mWidth  = width;
   mHeight = height;
}

int Fractal::getWidth()  const { return(mWidth);  }
int Fractal::getHeight() const { return(mHeight); }

/*****************************************************************************
 * Methods to fulfill our role as 'ColorEnvironment'
 *****************************************************************************/

ColorTable &Fractal::getColorTable()
{
   return(mColorTable);
}

void Fractal::foundInvalidColor()
{
   mInvalidColorCount++;
}

void Fractal::setRGB(int red, int green, int blue)
{
   mRed   = red;
   mGreen = green;
   mBlue  = blue;
}

int Fractal::getRGB(int index, int *red, int *green, int *blue)
{
   *red   = 0;
   *green = 0;
   *blue  = 0;

   int invalid = 0;

   getColorTable().lookup(index, red, green, blue, &invalid);

   if(invalid)
      foundInvalidColor();

   return(!invalid);
}

ComplexVariables &Fractal::getComplexVariables()
{
   return(mComplexVariables);
}

DoubleVariables &Fractal::getDoubleVariables()
{
   return(mDoubleVariables);
}

void Fractal::setBeforeStatement(const Statement *s)
{
   mBeforeStatement = s;
}

void Fractal::setStatement(const Statement *s)
{
   mStatement = s;
}

void Fractal::setAfterStatement(const Statement *s)
{
   mAfterStatement = s;
}

void Fractal::setCondition(const BooleanNode *theCondition)
{
   mCondition = theCondition;
}

void Fractal::begin()
{
   mRowNumber = 0;

   // From start => end in "y" to compensate for the
   // fact that we generate our image file from top to bottom
 
   mXDelta = (mXEnd   - mXStart) / (double)(mWidth  - 1);
   mYDelta = (mYStart - mYEnd)   / (double)(mHeight - 1);

   if(!mRow)
   {
      DNEW(mRow, unsigned char[mWidth * 3]);
   }

   mY = mYEnd;
}

int Fractal::hasMoreRows() const
{
   return(mRowNumber < mHeight);
}

unsigned char *Fractal::nextRow(InfiniteLoopCallback *callback)
{
   double x = mXStart;
   int j    = 0;

   for(int i = 0; i < mWidth; i ++, x += mXDelta)
   {
      // Ensure all variables are initialized

      mComplexVariables.initialize();
      mDoubleVariables.initialize();

      // Set the value of the predefined complex variable 'current'
      // to the current [x, y] point we're processing

      dcomplex current(x, mY);
      *mCurrentPtr = current;

      // Set our x/y start/end and x/y pixels variables.

      *mMappingXStartPtr  = mXStart;
      *mMappingYStartPtr  = mYStart;
      *mMappingXEndPtr    = mXEnd;
      *mMappingYEndPtr    = mYEnd;
      *mMappingXPixelsPtr = mWidth;
      *mMappingYPixelsPtr = mHeight;

      // Now our predefined math values

      *mM_EPtr        = 2.7182818284590452354;
      *mM_LOG2EPtr    = 1.4426950408889634074;
      *mM_LOG10EPtr   = 0.43429448190325182765;
      *mM_LN2Ptr      = 0.69314718055994530942;
      *mM_LN10Ptr     = 2.30258509299404568402;
      *mM_PIPtr       = 3.14159265358979323846;
      *mM_PI_2Ptr     = 1.57079632679489661923;
      *mM_PI_4Ptr     = 0.78539816339744830962;
      *mM_1_PIPtr     = 0.31830988618379067154;
      *mM_2_PIPtr     = 0.63661977236758134308;
      *mM_2_SQRTPIPtr = 1.12837916709551257390;
      *mM_SQRT2Ptr    = 1.41421356237309504880;
      *mM_SQRT1_2Ptr  = 0.70710678118654752440;

      // Now current row/column

      *mCurrentRowPtr    = mRowNumber;
      *mCurrentColumnPtr = i;

      // Initialize our color to black, in case it isn't assigned
      // by any of the three statements

      mRed = mGreen = mBlue = 0;

      // We have to pass a "LoopControl *" to all statements
      // but the before and after statements are outside of any
      // loops and consequently are prohibited from containing
      // break and/or continue statements

      LoopControl ignored;

      // Now execute our 'before' statement, just before entering the
      // while loop

      int status = mBeforeStatement->execute(callback, &ignored);

      if(!status)
         break;

      int count = 0;

      // The reason we have a separate 'while' construct (in addition
      // to the ForStatement class) is because we want to update
      // the pseudo variable '$count' to record the number of passes
      // through the main while loop so 'while' must be a separate
      // construct than ForStatement.  If we were willing to ditch
      // automatic recording of $count (and force the user to record
      // the loop count manually) we could create a WhileStatement
      // class and be done with it but this does have significant
      // backward compatibility issues so we'll leave it for now

      while(mCondition->evaluate())
      {
         if((count + 1) % InfiniteLoopCallback::NITERATIONS == 0)
         {
            if(callback->abortProcessing())
            {
               status = FALSE;
               break;
            }
         }

         LoopControl control;

         // Execute our main formula statement

         status = mStatement->execute(callback, &control);

         if(!status)
            break;

         // Check to see if 'doBreak' was set ... we don't need to
         // bother with doContinue as we get that one for free since
         // 'mStatement' will also be checking for break/continue and
         // will return control immediately to us if he finds either
         // of them

         if(control.doBreak)
            break;

         // Update our count ...

         *mCountPtr = (double)++count;
      }

      if(!status)
         break;

      // Execute our 'after' statement

      status = mAfterStatement->execute(callback, &ignored);

      if(!status)
         break;

      // Assign our color

      mRow[j++] = mRed;
      mRow[j++] = mGreen;
      mRow[j++] = mBlue;
   }

   ++mRowNumber;
   mY += mYDelta;

   return(mRow);
}

int Fractal::getInvalidColorCount() const
{
   return(mInvalidColorCount);
}

ostream &operator<<(ostream &out, const Fractal &f)
{
   // write out mapping section

   out << "[Mapping]" << endl;

   out << "(" << f.mXStart << ", "     <<
                 f.mYStart << ", "     <<
                 f.mXEnd   << ", "     <<
                 f.mYEnd   << ") => (" <<
                 f.mWidth  << ", "     <<
                 f.mHeight << ")"      << endl << endl;

   // now color table

   out << "[ColorTable]" << endl;
   out << f.mColorTable << endl << endl;

   // before statement

   out << "[BeforeStatement]" << endl;
   out << *f.mBeforeStatement << endl << endl;

   // while condition

   out << "[Condition]" << endl;
   out << *f.mCondition << endl << endl;

   // statement

   out << "[Statement]" << endl;
   out << *f.mStatement << endl << endl;

   // after statement

   out << "[AfterStatement]" << endl;
   out << *f.mAfterStatement << endl;

   return(out);
}
