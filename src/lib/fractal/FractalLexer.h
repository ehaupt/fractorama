#ifndef _FRACTAL_LEXER_H_
#   define _FRACTAL_LEXER_H_

class FractalLexer
{
   public:
      static FractalLexer *getInstance();
      static int parseInteger(char *theText);
      void begin(const char *text);
      void end();
      int getLineNumber();
      void nextLine();
      int getText(char *dest, int maxSize);
      int getFileOffset();
      int getLineOffset();
      void getCurrentLine(char *line);
      void advance(char *theText);
      enum { MAX_LINE_LENGTH = 255 };

   private:
      FractalLexer();
      int mLineNumber;
      char *mText;
      int mTextIndex;
      int mTextLength;
      int mFileOffset;
      int mLineOffset;
};
#endif
