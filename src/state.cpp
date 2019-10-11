// C/C++ headers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local headers

#include "state.h"
#include "main.h"
#include "application.h"
#include "dmemory.h"

/*****************************************************************************
 * Local #defines
 *****************************************************************************/

#define OPEN_DIRECTORY         "openDirectory"
#define OPEN_DIRECTORY_DEFAULT "."

#define SAVE_DIRECTORY         "saveDirectory"
#define SAVE_DIRECTORY_DEFAULT "."

#define DIMENSIONS             "dimensions"
#define WIDTH_DEFAULT          "640"
#define HEIGHT_DEFAULT         "480"
#define DIMENSIONS_DEFAULT     WIDTH_DEFAULT" "HEIGHT_DEFAULT

#define ZOOM_COLOR             "zoomColor"
#define RED_DEFAULT            "0"
#define GREEN_DEFAULT          "0"
#define BLUE_DEFAULT           "0"
#define ZOOM_COLOR_DEFAULT     RED_DEFAULT" "GREEN_DEFAULT" "BLUE_DEFAULT

#define SPLIT_SIZES            "splitSizes"
#define TOP_DEFAULT            "0"
#define BOTTOM_DEFAULT         "0"
#define SPLIT_SIZES_DEFAULT    TOP_DEFAULT" "BOTTOM_DEFAULT

#define ZOOMOUT_FACTOR         "zoomOutFactor"
#define ZOOMOUT_FACTOR_DEFAULT "2.0"

#define ZOOMIN_WIDTH_OPTION    "zoomInWidthOption"
#define ZOOMIN_HEIGHT_OPTION   "zoomInHeightOption"
#define ZOOMIN_WIDTH           "zoomInWidth"
#define ZOOMIN_WIDTH_DEFAULT   "640"
#define ZOOMIN_HEIGHT          "zoomInHeight"
#define ZOOMIN_HEIGHT_DEFAULT  "480"

#define FONT_SIZE              "fontSize"
#define FONT_SIZE_DEFAULT      "12"

#define ANTI_ALIAS             "antiAlias"
#define ANTI_ALIAS_DEFAULT     "0"

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static void storeValue(Persist *p, char *key, const char *value);

/*****************************************************************************
 * Definition of class: State
 *****************************************************************************/

// Constructor

State::State(Persist *p) :
   mOpenDirectory(NULL),
   mSaveDirectory(NULL),
   mWidth(0), mHeight(0),
   mRed(0), mGreen(0), mBlue(0),
   mZoomOutFactor(0.0),
   mZoomInWidthOption(ZoomInDialog::UNSPECIFIED_WIDTH),
   mZoomInHeightOption(ZoomInDialog::UNSPECIFIED_HEIGHT),
   mZoomInWidth(0),
   mZoomInHeight(0),
   mFontSize(0),
   mAntiAlias(0),
   mPersist(p)
{
   mOpenDirectory = mPersist->getValueDefaulted(
      OPEN_DIRECTORY, OPEN_DIRECTORY_DEFAULT
   );

   mSaveDirectory = mPersist->getValueDefaulted(
      SAVE_DIRECTORY, SAVE_DIRECTORY_DEFAULT
   );

   char *value = NULL;

   value = mPersist->getValueDefaulted(DIMENSIONS, DIMENSIONS_DEFAULT);

   if(sscanf(value, "%d %d", &mWidth, &mHeight) != 2 ||
      mWidth <= 0 || mHeight <= 0)
   {
      mWidth  = atoi(WIDTH_DEFAULT);
      mHeight = atoi(HEIGHT_DEFAULT);
   }

   DADELETE(value);

   value = p->getValueDefaulted(ZOOM_COLOR, ZOOM_COLOR_DEFAULT);

   if(sscanf(value, "%d %d %d", &mRed, &mGreen, &mBlue) != 3 ||
      mRed < 0 || mGreen < 0 || mBlue < 0)
   {
      mRed   = atoi(RED_DEFAULT);
      mGreen = atoi(RED_DEFAULT);
      mBlue  = atoi(RED_DEFAULT);
   }

   DADELETE(value);

   value = p->getValueDefaulted(SPLIT_SIZES, SPLIT_SIZES_DEFAULT);

   if(sscanf(value, "%d %d", &mTop, &mBottom) != 2 ||
      mTop <= 0 || mBottom <= 0)
   {
      mTop    = atoi(TOP_DEFAULT);
      mBottom = atoi(BOTTOM_DEFAULT);
   }

   DADELETE(value);

   value = p->getValueDefaulted(
      ZOOMOUT_FACTOR, ZOOMOUT_FACTOR_DEFAULT
   );

   if((mZoomOutFactor = atof(value)) == 0.0)
      mZoomOutFactor = atof(ZOOMOUT_FACTOR_DEFAULT);

   DADELETE(value);

   value = p->getValueDefaulted(
      ZOOMIN_WIDTH_OPTION,
      (char *)ZoomInDialog::toString(
         ZoomInDialog::widthOptionFromString("")
      )
   );

   mZoomInWidthOption = ZoomInDialog::widthOptionFromString(value);

   DADELETE(value);

   value = p->getValueDefaulted(
      ZOOMIN_HEIGHT_OPTION,
      (char *)ZoomInDialog::toString(
         ZoomInDialog::heightOptionFromString("")
      )
   );

   mZoomInHeightOption = ZoomInDialog::heightOptionFromString(value);

   DADELETE(value);

   value = mPersist->getValueDefaulted(ZOOMIN_WIDTH, ZOOMIN_WIDTH_DEFAULT);

   if((mZoomInWidth = atoi(value)) <= 0)
      mZoomInWidth = atoi(ZOOMIN_WIDTH_DEFAULT);

   DADELETE(value);

   value = mPersist->getValueDefaulted(ZOOMIN_HEIGHT, ZOOMIN_HEIGHT_DEFAULT);

   if((mZoomInHeight = atoi(value)) <= 0)
      mZoomInHeight = atoi(ZOOMIN_HEIGHT_DEFAULT);

   DADELETE(value);

   value = mPersist->getValueDefaulted(FONT_SIZE, FONT_SIZE_DEFAULT);

   if((mFontSize = atoi(value)) <= 0)
      mFontSize = atoi(FONT_SIZE_DEFAULT);

   DADELETE(value);

   value = mPersist->getValueDefaulted(ANTI_ALIAS, ANTI_ALIAS_DEFAULT);

   if(*value == 'y')
      mAntiAlias = 1;
   else
      mAntiAlias = 0;

   DADELETE(value);
}

State::~State()
{
   DADELETE(mOpenDirectory);
   DADELETE(mSaveDirectory);
   DDELETE(mPersist);
}

State *State::clone()
{
   State *s = 0;

   DNEW(s, State(mPersist->clone()));

   return(s);
}

char *State::getOpenDirectory()
{
   return(mOpenDirectory);
}

void State::setOpenDirectory(const char *value)
{
   DADELETE(mOpenDirectory);
   DNEW(mOpenDirectory, char[strlen(value) + 1]);
   strcpy(mOpenDirectory, value);

   storeValue(this->mPersist, OPEN_DIRECTORY, mOpenDirectory);
}

char *State::getSaveDirectory()
{
   return(mSaveDirectory);
}

void State::setSaveDirectory(const char *value)
{
   DADELETE(mSaveDirectory);
   DNEW(mSaveDirectory, char[strlen(value) + 1]);
   strcpy(mSaveDirectory, value);

   storeValue(this->mPersist, SAVE_DIRECTORY, mSaveDirectory);
}

void State::getDimensions(int *width, int *height)
{
   *width  = mWidth;
   *height = mHeight;
}

void State::setDimensions(int width, int height)
{
   mWidth  = width;
   mHeight = height;

   QString s;
   s.sprintf("%d %d", mWidth, mHeight);

   storeValue(this->mPersist, DIMENSIONS, s.latin1());
}

void State::getZoomColor(int *red, int *green, int *blue)
{
   *red   = mRed;
   *green = mGreen;
   *blue  = mBlue;
}

void State::setZoomColor(int red, int green, int blue)
{
   mRed   = red;
   mGreen = green;
   mBlue  = blue;

   QString s;
   s.sprintf("%d %d %d", mRed, mGreen, mBlue);

   storeValue(this->mPersist, ZOOM_COLOR, s.latin1());
}

void State::getSplitSizes(int *top, int *bottom)
{
   *top    = mTop;
   *bottom = mBottom;
}

void State::setSplitSizes(int top, int bottom)
{
   mBottom = bottom;
   mTop    = top;

   QString s;
   s.sprintf("%d %d", mTop, mBottom);

   storeValue(this->mPersist, SPLIT_SIZES, s.latin1());
}

double State::getZoomOutFactor()
{
   return(mZoomOutFactor);
}

void State::setZoomOutFactor(double factor)
{
   mZoomOutFactor = factor;

   QString s;
   s.sprintf("%.20f", factor);

   storeValue(this->mPersist, ZOOMOUT_FACTOR, s.latin1());
}

/*****************************************************************************
 * Methods to fulfill our role as ZoomInSettings
 *****************************************************************************/

ZoomInDialog::WidthOption State::getZoomInWidthOption()
{
   return(mZoomInWidthOption);
}

ZoomInDialog::HeightOption State::getZoomInHeightOption()
{
   return(mZoomInHeightOption);
}

int State::getZoomInWidth()
{
   return(mZoomInWidth);
}

int State::getZoomInHeight()
{
   return(mZoomInHeight);
}

void State::setZoomInWidthOption(ZoomInDialog::WidthOption option)
{
   mZoomInWidthOption = option;

   storeValue(
      this->mPersist, ZOOMIN_WIDTH_OPTION, ZoomInDialog::toString(option)
   );
}

void State::setZoomInHeightOption(ZoomInDialog::HeightOption option)
{
   mZoomInHeightOption = option;

   storeValue(
      this->mPersist, ZOOMIN_HEIGHT_OPTION, ZoomInDialog::toString(option)
   );
}

void State::setZoomInWidth(int width)
{
   mZoomInWidth = width;

   QString s;
   s.sprintf("%d", mZoomInWidth);

   storeValue(this->mPersist, ZOOMIN_WIDTH, s.latin1());
}

void State::setZoomInHeight(int height)
{
   mZoomInHeight = height;

   QString s;
   s.sprintf("%d", mZoomInHeight);

   storeValue(this->mPersist, ZOOMIN_HEIGHT, s.latin1());
}

int State::getFontSize()
{
   return(mFontSize);
}

void State::setFontSize(int size)
{
   mFontSize = size;

   QString s;
   s.sprintf("%d", mFontSize);

   storeValue(this->mPersist, FONT_SIZE, s.latin1());
}

int State::getAntiAlias()
{
   return(mAntiAlias);
}

void State::setAntiAlias(int value)
{
   if(value)
      value = 1;

   mAntiAlias = value;

   storeValue(this->mPersist, ANTI_ALIAS, value ? "yes" : "no");
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

static void storeValue(Persist *p, char *key, const char *value)
{
   char *nonConstValue = (char *)value;

   // Store the changed value locally and application-wide

   p->storeValue(key, nonConstValue);
   getApplicationInstance()->storeValue(key, nonConstValue);
}
