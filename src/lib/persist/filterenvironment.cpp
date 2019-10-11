// Local Headesr

#include "filterenvironment.h"
#include "dmemory.h"

FilterEnvironment::FilterEnvironment(Environment *environment)
   : mEnvironment(environment)
{
}

FilterEnvironment::~FilterEnvironment()
{
   DDELETE(mEnvironment);
}

int FilterEnvironment::keyDefined(char *key)
{
   return(mEnvironment->keyDefined(key));
}

char *FilterEnvironment::getValueDefaulted(
   char *key,
   char *theDefault,
   char **errMsgPtr
)
{
   return(mEnvironment->getValueDefaulted(key, theDefault, errMsgPtr));
}

char *FilterEnvironment::getValue(char *key, char **errMsgPtr)
{
   return(mEnvironment->getValue(key, errMsgPtr));
}

int FilterEnvironment::storeValue(char *key, char *value, char **errMsgPtr)
{
   return(mEnvironment->storeValue(key, value, errMsgPtr));
}

int FilterEnvironment::setValue(char *key, char *value, char **errMsgPtr)
{
   return(mEnvironment->setValue(key, value, errMsgPtr));
}

int FilterEnvironment::add(char *key, char *value, char **errMsgPtr)
{
   return(mEnvironment->add(key, value, errMsgPtr));
}

int FilterEnvironment::remove(char *key, char **errMsgPtr)
{
   return(mEnvironment->remove(key, errMsgPtr));
}

int FilterEnvironment::print(FILE *out, char **errMsg)
{
   return(mEnvironment->print(out, errMsg));
}

Environment *FilterEnvironment::getEnvironment()
{
   return(mEnvironment);
}
