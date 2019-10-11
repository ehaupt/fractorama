#ifndef _ENVIRONMENT_H_
#   define _ENVIRONMENT_H_

#ifndef TRUE
#   define TRUE (1)
#endif

#ifndef FALSE
#   define FALSE (0)
#endif

#include <stdio.h>

class Environment
{
   public:
      Environment();
      virtual ~Environment();

      virtual Environment *clone(char **errMsgPtr) = 0;

      virtual int keyDefined(char *key) = 0;

      virtual char *getValueDefaulted(
         char *key,
         char *theDefault,
         char **errMsgPtr
      );

      virtual char *getValue(char *key, char **errMsgPtr) = 0;

      virtual int storeValue(char *key, char *value, char **errMsgPtr);

      virtual int setValue(char *key, char *value, char **errMsgPtr) = 0;

      virtual int add(char *key, char *value, char **errMsgPtr) = 0;
      virtual int remove(char *key, char **errMsgPtr)           = 0;

      virtual int print(FILE *out, char **errMsgPtr)            = 0;

      static char getCommentChar();

   protected:
      char *keyNotDefinedMessage(char *key);
      char *keyAlreadyDefinedMessage(char *key);

   private:
      Environment(const Environment &);
      Environment &operator=(const Environment &);
};

#endif
