#ifndef _COLOR_ENVIRONMENT_H_
#   define _COLOR_ENVIRONMENT_H_

class ColorTable;

class ColorEnvironment
{
   public:
      virtual ColorTable &getColorTable()                             = 0;
      virtual void foundInvalidColor()                                = 0;
      virtual void setRGB(int red, int green, int blue)               = 0;
      virtual int  getRGB(int index, int *red, int *green, int *blue) = 0;
};

#endif
