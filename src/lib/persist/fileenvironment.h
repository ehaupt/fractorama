#ifndef _FILE_ENVIRONMENT_H_
#   define _FILE_ENVIRONMENT_H_

#include "filterenvironment.h"

class FileEnvironment : public FilterEnvironment
{
   public:
      FileEnvironment(
         char *fileName,
         Environment *environment
      );

      ~FileEnvironment();

      virtual Environment *clone(char **errMsgPtr);

      virtual int storeValue(char *key, char *value, char **errMsgPtr);
      virtual int setValue(char *key, char *value, char **errMsgPtr);
      virtual int add(char *key, char *value, char **errMsgPtr);
      virtual int remove(char *key, char **errMsgPtr);

   private:
      FileEnvironment(const FileEnvironment &);
      FileEnvironment &operator=(const FileEnvironment &);

      int write(char **errMsgPtr);
      char *mFileName;
};

#endif
