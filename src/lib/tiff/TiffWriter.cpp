#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "dmemory.h"

extern "C"
{
   #include "tiffio.h"
}

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

#include "TiffWriter.h"

class ImageDestination
{
   public:
      ImageDestination(int width, int height);
      virtual ~ImageDestination();
 
      virtual void processRow(unsigned char *row) = 0;
 
   protected:
      int getWidth();
      int getHeight();
 
   private:
      int mWidth;
      int mHeight;
};
 
ImageDestination::ImageDestination(int width, int height) :
   mWidth(width), mHeight(height)
{
}
 
ImageDestination::~ImageDestination()
{
}
 
int ImageDestination::getWidth()
{
   return(mWidth);
}
 
int ImageDestination::getHeight()
{
   return(mHeight);
}

class TiffImageDestination : public ImageDestination
{
   public:
      TiffImageDestination(int width, int height, TIFF *ptr);
      ~TiffImageDestination();
      virtual void processRow(unsigned char *row);

   private:
      TIFF *mPtr;
      int mScanNumber;
};

TiffImageDestination::TiffImageDestination(int width, int height, TIFF *ptr) :
   ImageDestination(width, height),
   mPtr(ptr),
   mScanNumber(0)
{
}

TiffImageDestination::~TiffImageDestination()
{
   TIFFClose(mPtr);
}

void TiffImageDestination::processRow(unsigned char *row)
{
   TIFFWriteScanline(mPtr, row, mScanNumber++, 0);
}

class AntiAliasFilter : public ImageDestination
{
   public:
      AntiAliasFilter(int width, int height, ImageDestination *dest);
      ~AntiAliasFilter();
      virtual void processRow(unsigned char *row);

   private:
      void storeRGB(
         unsigned char *destRow, int offset, double r, double g, double b
      );

      void processPartialPixel(
         int outputOffset,
         int rowOffset,
         int columnOffset,
         int index
      );

      void handleFirstColumns(int *outputOffset, int rowOffset);

      void handleLastColumns(
         int width, int *outputOffset, int rowOffset
      );

      void handlePartialRow(int rowOffset);

      void handleRow();

      ImageDestination *mDest;
      int               mRowCount;
      unsigned char    *mSavedRows[9];
      unsigned char    *mOutputRow;
      double            mRawMatrix[9][9];
      double            mMatrix[9][9];
};

AntiAliasFilter::AntiAliasFilter(
   int width, int height, ImageDestination *dest
)  :
   ImageDestination(width, height),
   mDest(dest),
   mRowCount(0),
   mOutputRow(0)
{
   int size = 3 * getWidth();
   int i    = 0;

   for(i = 0; i < 9; i ++)
      DNEW(mSavedRows[i], unsigned char[size]);

   DNEW(mOutputRow, unsigned char[(size + 1) / 2]);

   int j        = 0;
   double x     = 0.0;
   double y     = 0.0;
   double total = 0.0;

   for(i = 0, y = -2.0; i < 9; i ++, y += 0.5)
   {
      for(j = 0, x = -2.0; j < 9; j ++, x += 0.5)
      {
         if(i == 4 && j == 4)
         {
            mRawMatrix[i][j] = 1.0;
         }
         else
         {
            double radius = sqrt(x * x + y * y);
            double u      = M_PI * radius;
            double v      = 0.5 * M_PI * radius;

            mRawMatrix[i][j] = sin(u) / u + sin(v) / v;
         }

         total += mRawMatrix[i][j];
      }
   }

   for(i = 0; i < 9; i ++)
   {
      for(j = 0; j < 9; j ++)
      {
         mMatrix[i][j] = mRawMatrix[i][j] / total;
      }
   }
}

AntiAliasFilter::~AntiAliasFilter()
{
   for(int i = 0; i < 9; i ++)
      DADELETE(mSavedRows[i]);

   DADELETE(mOutputRow);

   DDELETE(mDest);
}

void AntiAliasFilter::storeRGB(
   unsigned char *destRow, int offset, double r, double g, double b
)
{
   r = (int)(r + 0.5);
   g = (int)(g + 0.5);
   b = (int)(b + 0.5);

   r = (r < 0.0 ? 0.0 : r > 255.0 ? 255.0 : r);
   g = (g < 0.0 ? 0.0 : g > 255.0 ? 255.0 : g);
   b = (b < 0.0 ? 0.0 : b > 255.0 ? 255.0 : b);

   destRow[offset++] = (unsigned char)r;
   destRow[offset++] = (unsigned char)g;
   destRow[offset++] = (unsigned char)b;
}

void AntiAliasFilter::processPartialPixel(
   int outputOffset,
   int rowOffset,
   int columnOffset,
   int index
)
{
   double r     = 0.0;
   double g     = 0;
   double b     = 0;
   double total = 0;

   int k = rowOffset;

   for(int i = 0; i < 9; i ++, k ++)
   {
      if(k >= 0 && k <= 8)
      {
         int m = columnOffset;
         int n = index;

         for(int j = 0; j < 9; j ++, m ++)
         {
            if(m >= 0 && m <= 8)
            {
               double factor = mRawMatrix[i][j];
               total        += factor;
               r            += factor * mSavedRows[k][n];
               g            += factor * mSavedRows[k][n + 1];
               b            += factor * mSavedRows[k][n + 2];
               n            += 3;
            }
         }
      }
   }

   r /= total;
   g /= total;
   b /= total;

   storeRGB(mOutputRow, outputOffset, r, g, b);
}

void AntiAliasFilter::handleFirstColumns(int *outputOffset, int rowOffset)
{
   int beginValues[][2] = { {-4, 0}, {-2, 6} };
   int offset           = *outputOffset;

   for(int i = 0; i < 2; i ++, offset += 3)
   {
      processPartialPixel(
         offset, rowOffset, beginValues[i][0], beginValues[i][1]
      );
   }

   *outputOffset = offset;
}

void AntiAliasFilter::handleLastColumns(
   int width, int *outputOffset, int rowOffset
)
{
   int endValues[][2] = { {2, (width - 7) * 3}, {4, (width - 5) * 3 } };
   int offset         = *outputOffset;

   if(width % 2 == 0)
   {
      endValues[0][0]--;
      endValues[1][0]--;

      endValues[0][1] -= 3;
      endValues[1][1] -= 3;
   }

   for(int i = 0; i < 2; i ++, offset += 3)
   {
      processPartialPixel(
         offset, rowOffset, endValues[i][0], endValues[i][1]
      );
   }

   *outputOffset = offset;
}

void AntiAliasFilter::handlePartialRow(int rowOffset)
{
   int outputOffset = 0;
   int i            = 0;
   int j            = 0;
   int width        = getWidth();

   // Do columns 0 and 2 first

   handleFirstColumns(&outputOffset, rowOffset);

   // Now the "normal" portion of the row

   for(i = j = 0; i + 8 < width; i += 2, j += 6)
   {
      processPartialPixel(outputOffset, rowOffset, 0, j);
      outputOffset += 3;
   }

   // Now the next to last and last columns

   handleLastColumns(width, &outputOffset, rowOffset);

   mDest->processRow(mOutputRow);
}

void AntiAliasFilter::handleRow()
{
   int outputOffset = 0;
   int i            = 0;
   int j            = 0;
   int width        = getWidth();

   // Do columns 0 and 2 first

   handleFirstColumns(&outputOffset, 0);

   // Now the "normal" portion of the row

   for(i = j = 0; i + 8 < width; i += 2, j += 6)
   {
      double r = 0;
      double g = 0;
      double b = 0;

      for(int k = 0; k < 9; k ++)
      {
         for(int m = 0; m < 9; m ++)
         {
            double factor = mMatrix[m][k];
            r += factor * mSavedRows[k][j + 3 * m];
            g += factor * mSavedRows[k][j + 3 * m + 1];
            b += factor * mSavedRows[k][j + 3 * m + 2];
         }
      }

      storeRGB(mOutputRow, outputOffset, r, g, b);
      outputOffset += 3;
   }

   // Now the next to last and last columns

   handleLastColumns(width, &outputOffset, 0);

   mDest->processRow(mOutputRow);
}

void AntiAliasFilter::processRow(unsigned char *row)
{
   int width  = getWidth();
   int height = getHeight();
   int i      = 0;
   int j      = 0;
   int index  = 0;

   if(mRowCount < 9)
      index = mRowCount;
   else
      index = 0;

   for(i = j = 0; i < width; i ++, j += 3)
   {
      mSavedRows[index][j]     = row[j];
      mSavedRows[index][j + 1] = row[j + 1];
      mSavedRows[index][j + 2] = row[j + 2];
   }

   if(mRowCount >= 9)
   {
      unsigned char *tmp = mSavedRows[0];

      for(i = 1; i < 9; i ++)
         mSavedRows[i - 1] = mSavedRows[i];

      mSavedRows[8] = tmp;
   }

   if(mRowCount == 8)
   {
      // handle rows 0 and 2

      int beginValues[2] = { -4, -2 };

      for(i = 0; i < 2; i ++)
      {
         handlePartialRow(beginValues[i]);
      }
   }

   if(mRowCount % 2 == 0 && mRowCount >= 8 && mRowCount < height)
      handleRow();

   if(mRowCount == height - 1)
   {
      // Handle the last and next to last rows

      int endValues[2] = { -4, -2 };

      if(mRowCount % 2)
      {
         endValues[0]--;
         endValues[1]--;
      }

      for(i = 0; i < 2; i ++)
         handlePartialRow(endValues[i]);
   }

   mRowCount++;
}

TiffWriter *TiffWriter::makeWriter(
   const char *name, int width, int height, int doAntiAlias, char **errMsgPtr
)
{
   TIFF *ptr = NULL;

   if((ptr = TIFFOpen(name, "w")) == NULL)
   {
      char *before = "Unable to open file: [";
      char *after  = "]";

      int length   = strlen(before) + strlen(name) + strlen(after) + 1;
      char *errMsg = 0;

      DNEW(errMsg, char[length]);

      sprintf(errMsg, "Unable to open file: [%s]", name);

      *errMsgPtr = errMsg;

      return(NULL);
   }

   int antiAlias  = 0;
   int tiffWidth  = width;
   int tiffHeight = height;

   if(doAntiAlias && width >= 9 && height >= 9)
   {
      tiffWidth  = width  / 2;
      tiffHeight = height / 2;
      antiAlias = 1;
   }

   TIFFSetField(ptr, TIFFTAG_IMAGEWIDTH,      tiffWidth);
   TIFFSetField(ptr, TIFFTAG_IMAGELENGTH,     tiffHeight);
   TIFFSetField(ptr, TIFFTAG_SAMPLESPERPIXEL, 3);
   TIFFSetField(ptr, TIFFTAG_BITSPERSAMPLE,   8);
   TIFFSetField(ptr, TIFFTAG_PLANARCONFIG,    PLANARCONFIG_CONTIG);
   TIFFSetField(ptr, TIFFTAG_COMPRESSION,     COMPRESSION_LZW);
   TIFFSetField(ptr, TIFFTAG_PHOTOMETRIC,     PHOTOMETRIC_RGB);
   TIFFSetField(ptr, TIFFTAG_ROWSPERSTRIP,    1L);

   ImageDestination *dest = 0;

   DNEW(dest, TiffImageDestination(tiffWidth, tiffHeight, ptr));

   if(antiAlias)
      DNEW(dest, AntiAliasFilter(width, height, dest));

   TiffWriter *tw = 0;

   DNEW(tw, TiffWriter(name, dest));

   return(tw);
}

TiffWriter::TiffWriter(
   const char *name,
   ImageDestination *dest
) :
   mName(0),
   mDest(dest)
{
   DNEW(mName, char[strlen(name) + 1]);
   strcpy(mName, name);
}

void TiffWriter::writeRow(unsigned char *row)
{
   mDest->processRow(row);
}

TiffWriter::~TiffWriter()
{
   DADELETE(mName);
   DDELETE(mDest);
}

const char *TiffWriter::getName()
{
   return(mName);
}
