#ifndef _FILTER_ENVIRONMENT_H_
#   define _FILTER_ENVIRONMENT_H_

#include "environment.h"

class FilterEnvironment : public Environment
{
   public:
      FilterEnvironment(Environment *environment);
      ~FilterEnvironment();

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

       virtual int print(FILE *out, char **errMsg);

   protected:
      Environment *getEnvironment();

   private:
      FilterEnvironment(const FilterEnvironment &);
      FilterEnvironment &operator=(const FilterEnvironment &);

      Environment *mEnvironment;
};
#endif
