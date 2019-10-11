#ifndef _KV_ENVIRONMENT_H_
#   define _KV_ENVIRONMENT_H_

#include "environment.h"

class KVEnvironment : public Environment
{
   public:

      typedef enum
      {
         ErrorIfOpenFails,
         ErrorIfReadFails
         
      } Option;

      static KVEnvironment *create();

      static KVEnvironment *create(
         char *fileName,
         Option errorOption,
         char **errMsgPtr
      );

#ifdef __GNUC__
      friend class PacifyGPlusPlus;
#endif

      ~KVEnvironment();

      virtual Environment *clone(char **errMsgPtr);

      virtual int keyDefined(char *key);

      virtual char *getValue(char *key, char **errMsgPtr);
      virtual int setValue(char *key, char *value, char **errMsgPtr);
      virtual int add(char *key, char *value, char **errMsgPtr);
      virtual int remove(char *key, char **errMsgPtr);
      virtual int print(FILE *out, char **errMsgPtr);

   private:
      KVEnvironment(const KVEnvironment &);
      KVEnvironment &operator=(const KVEnvironment &);

      KVEnvironment();
      int read(FILE *, char **errMsgPtr);
      void destroy();
      int findIndex(char *key);
      void addEntry(char *key, char *value);
      void removeEntry(int index);

      int mCount;
      char **mKeys;
      char **mValues;
};

#endif
