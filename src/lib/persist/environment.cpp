// C/C++ Headers

#include <string.h>

// Local Headers

#include "environment.h"
#include "dmemory.h"

Environment::Environment()
{
   // Nothing to do
}

Environment::~Environment()
{
   // Nothing to do
}

char *Environment::getValueDefaulted(
   char *key,
   char *theDefault,
   char **errMsgPtr
)
{
   if(!keyDefined(key))
   {
      char *value = 0;

      DNEW(value, char[strlen(theDefault) + 1]);

      strcpy(value, theDefault);
      return(value);
   }

   return(getValue(key, errMsgPtr));
}

int Environment::storeValue(char *key, char *value, char **errMsgPtr)
{
   return(
      keyDefined(key) ?
      setValue(key, value, errMsgPtr) :
      add(key, value, errMsgPtr)
   );
}

char Environment::getCommentChar()
{
   return('#');
}

char *Environment::keyNotDefinedMessage(char *key)
{
   char *m1 = "Key: [";
   char *m2 = "] is not defined";

   int length   = strlen(m1) + strlen(key) + strlen(m2);
   char *buffer = 0;

   DNEW(buffer, char[length]);

   sprintf(buffer, "%s%s%s", m1, key, m2);

   return(buffer);
}

char *Environment::keyAlreadyDefinedMessage(char *key)
{
   char *m1 = "Key: [";
   char *m2 = "] is already defined";

   int length   = strlen(m1) + strlen(key) + strlen(m2);
   char *buffer = 0;

   DNEW(buffer, char[length]);

   sprintf(buffer, "%s%s%s", m1, key, m2);

   return(buffer);
}
