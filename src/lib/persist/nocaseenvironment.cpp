// C/C++ Headers

#include <string.h>
#include <ctype.h>

// Local Headers

#include "nocaseenvironment.h"
#include "dmemory.h"

NoCaseEnvironment::NoCaseEnvironment(Environment *environment)
   : FilterEnvironment(environment)
{
}

NoCaseEnvironment::~NoCaseEnvironment()
{
   // Nothing to do
}

Environment *NoCaseEnvironment::clone(char **errMsgPtr)
{
   NoCaseEnvironment *ne = 0;
   DNEW(ne, NoCaseEnvironment(getEnvironment()->clone(errMsgPtr)));
   return(ne);
}

int NoCaseEnvironment::keyDefined(char *key)
{
   char *keyLower = toLowerCase(key);
   int status     = FilterEnvironment::keyDefined(keyLower);

   DADELETE(keyLower);

   return(status);
}

char *NoCaseEnvironment::getValueDefaulted(
   char *key,
   char *theDefault,
   char **errMsgPtr
)
{
   char *keyLower = toLowerCase(key);

   char *value = FilterEnvironment::getValueDefaulted(
      keyLower, theDefault, errMsgPtr
   );

   DADELETE(keyLower);

   return(value);
}

char *NoCaseEnvironment::getValue(char *key, char **errMsgPtr)
{
   char *keyLower = toLowerCase(key);
   char *value    = FilterEnvironment::getValue(keyLower, errMsgPtr);

   DADELETE(keyLower);

   return(value);
}

int NoCaseEnvironment::storeValue(char *key, char *value, char **errMsgPtr)
{
   char *keyLower = toLowerCase(key);
   int status     = FilterEnvironment::storeValue(keyLower, value, errMsgPtr);

   DADELETE(keyLower);

   return(status);
}

int NoCaseEnvironment::setValue(char *key, char *value, char **errMsgPtr)
{
   char *keyLower = toLowerCase(key);
   int status     = FilterEnvironment::setValue(keyLower, value, errMsgPtr);

   DADELETE(keyLower);

   return(status);
}

int NoCaseEnvironment::add(char *key, char *value, char **errMsgPtr)
{
   char *keyLower = toLowerCase(key);
   int status     = FilterEnvironment::add(keyLower, value, errMsgPtr);

   DADELETE(keyLower);

   return(status);
}

int NoCaseEnvironment::remove(char *key, char **errMsgPtr)
{
   char *keyLower = toLowerCase(key);
   int status     = FilterEnvironment::remove(keyLower, errMsgPtr);

   DADELETE(keyLower);

   return(status);
}

char *NoCaseEnvironment::toLowerCase(char *key)
{
   char *value = 0;

   DNEW(value, char[strlen(key) + 1]);

   strcpy(value, key);

   for(int i = 0; value[i]; i ++)
      value[i] = tolower(value[i]);

   return(value);
}
