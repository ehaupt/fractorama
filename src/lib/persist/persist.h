#ifndef _PERSIST_H_
#   define _PERSIST_H_

#include "environment.h"

class MessageHandler;

class Persist
{
   public:
      static char *getApplicationDirectory(
         char *argv0,
         char *fileName = NULL,
         char *subdir   = NULL,
         int perUser    = FALSE
      );

      static char *getUserDirectory(
         char *fileName = NULL,
         char *subdir   = NULL
      );

      static char *directoryFromFileName(
         char *fileName
      );

      static int directoryExists(
         char *theDirectory
      );

      static int makeDirectory(
         char *theDirectory
      );

      static int makeDirectories(
         char *theDirectory
      );

      Persist(
         Environment *environment,
         MessageHandler *handler = NULL
      );

      ~Persist();

      Persist *clone();

      int keyDefined(char *key);

      char *getValueDefaulted(
         char *key,
         char *theDefault
      );

      char *getValue(char *key);
      int storeValue(char *key, char *value);
      int setValue(char *key, char *value);
      int add(char *key, char *value);
      int remove(char *key);
      int print(FILE *out);

   private:

      Persist(const Persist &);
      Persist &operator=(const Persist &);

      Environment *mEnvironment;
      MessageHandler *mHandler;
};

#endif
