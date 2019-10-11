#ifndef _NOCASE_ENVIRONMENT_H_
#   define _NOCASE_ENVIRONMENT_H_

#include "filterenvironment.h"

class NoCaseEnvironment : public FilterEnvironment
{
   public:
      NoCaseEnvironment(Environment *environment);
      ~NoCaseEnvironment();

      virtual Environment *clone(char **errMsg);

      virtual int keyDefined(char *key);

      virtual char *getValueDefaulted(
         char *key,
         char *theDefault,
         char **errMsgPtr
      );

      virtual char *getValue(char *key, char **errMsgPtr);

      virtual int storeValue(char *key, char *value, char **errMsgPtr);

      virtual int setValue(char *key, char *value, char **errMsgPtr);

      virtual int add(char *key, char *value, char **errMsgPtr);

      virtual int remove(char *key, char **errMsgPtr);

   protected:
      char *toLowerCase(char *key);

   private:
      NoCaseEnvironment(const NoCaseEnvironment &);
      NoCaseEnvironment &operator=(const NoCaseEnvironment &);
};

#endif
