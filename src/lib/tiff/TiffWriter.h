#ifndef _TIFF_WRITER_H_
#   define _TIFF_WRITER_H_

class ImageDestination;

class TiffWriter
{
   public:

      static TiffWriter *makeWriter(
         const char *name,
         int width,
         int height,
         int doAntiAlias,
         char **errMsgPtr
      );

      ~TiffWriter();

      const char *getName();

      void writeRow(unsigned char *row);

   private:

      TiffWriter(const char *name, ImageDestination *dest);
      TiffWriter(const TiffWriter &other);
      TiffWriter &operator=(const TiffWriter &other);

   private:
      char *mName;
      ImageDestination *mDest;
};
#endif
