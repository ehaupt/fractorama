// C/C++ Headers

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Local Headers

#include "kvenvironment.h"
#include "dmemory.h"

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static char *openErrorMessage(char *name);
static char *trim(char *buffer);
static int parseLine(
   char *buffer, char **key, char **value, char **errMsgPtr
);
static int ignoreThisLine(char *line);

/*****************************************************************************
 * Definition of class KVEnvironment
 *****************************************************************************/

KVEnvironment *KVEnvironment::create()
{
   KVEnvironment *kv = 0;

   DNEW(kv, KVEnvironment());

   return(kv);
}

KVEnvironment *KVEnvironment::create(
   char *fileName,
   Option errorOption,
   char **errMsgPtr
)
{
   KVEnvironment *environment = NULL;
   FILE *f                    = NULL;

   if((f = fopen(fileName, "r")) == NULL)
   {
      if(errorOption == ErrorIfOpenFails)
      {
         *errMsgPtr = openErrorMessage(fileName);
      }
      else
      {
         DNEW(environment, KVEnvironment());
      }
   }
   else
   {
      DNEW(environment, KVEnvironment());

      if(!environment->read(f, errMsgPtr))
      {
         DDELETE(environment);
         environment = NULL;
      }

      fclose(f);
   }

   return(environment);
}

KVEnvironment::~KVEnvironment()
{
   destroy();
}

Environment *KVEnvironment::clone(char **errMsgPtr)
{
   KVEnvironment *env = 0;

   DNEW(env, KVEnvironment());

   for(int i = 0; i < mCount; i ++)
   {
      if(!env->add(mKeys[i], mValues[i], errMsgPtr))
      {
         DDELETE(env);
         return(NULL);
      }
   }

   return(env);
}

int KVEnvironment::keyDefined(char *key)
{
   return(findIndex(key) != -1);
}

char *KVEnvironment::getValue(char *key, char **errMsgPtr)
{
   int index   = findIndex(key);
   char *value = NULL;

   if(index != -1)
   {
      DNEW(value, char[strlen(mValues[index]) + 1]);

      sprintf(value, "%s", mValues[index]);

      return(value);        
   }
   else
   {
      *errMsgPtr = keyNotDefinedMessage(key);
   }

   return(value);

}

int KVEnvironment::setValue(char *key, char *value, char **errMsgPtr)
{
   int index       = findIndex(key);
   int returnValue = FALSE;

   if(index != -1)
   {
      DADELETE(mValues[index]);

      DNEW(mValues[index], char[strlen(value) + 1]);

      sprintf(mValues[index], "%s", value);

      returnValue = TRUE;
   }
   else
   {
      *errMsgPtr = keyNotDefinedMessage(key);
   }

   return(returnValue);

}

int KVEnvironment::add(char *key, char *value, char **errMsgPtr)
{
   int index       = findIndex(key);
   int returnValue = FALSE;

   if(index == -1)
   {
       char *pk = 0;
       char *pv = 0;

       DNEW(pk, char[strlen(key)   + 1]);
       DNEW(pv, char[strlen(value) + 1]);

      addEntry(strcpy(pk, key), strcpy(pv, value));

      returnValue = TRUE;
   }
   else
   {
      *errMsgPtr = keyAlreadyDefinedMessage(key);
   }

   return(returnValue);

}

int KVEnvironment::remove(char *key, char **errMsgPtr)
{
   int index       = findIndex(key);
   int returnValue = FALSE;

   if(index == -1)
   {
      removeEntry(index);
      returnValue = FALSE;
   }
   else
   {
      *errMsgPtr = keyNotDefinedMessage(key);
   }

   return(returnValue);
}

int KVEnvironment::print(FILE *out, char **)
{
   // Make things look nice, figure out the longest key ...

   int i       = 0;
   int longest = 0;

   for(i = 0; i < mCount; i ++)
   {
      int length = strlen(mKeys[i]);

      if(length > longest)
         longest = length;
   }

   for(i = 0; i < mCount; i ++)
   {
      fprintf(out, "%s", mKeys[i]);

      int length = strlen(mKeys[i]);

      for(int j = length; j < longest; j ++)
         fprintf(out, " ");

      fprintf(out, " = %s\n", mValues[i]);
   }

   return(TRUE);
}

KVEnvironment::KVEnvironment()
   : mCount(0), mKeys(0), mValues(0)
{
}

int KVEnvironment::read(FILE *f, char **errMsgPtr)
{
   char buffer[255] = { '\0' };
   int c            = 0;
   int returnValue  = TRUE;

   while((c = fgetc(f)) != EOF)
   {
      ungetc(c, f);

      fgets(buffer, sizeof(buffer), f);

      if(!ignoreThisLine(buffer))
      {
         char *key   = NULL;
         char *value = NULL;

         if(!parseLine(buffer, &key, &value, errMsgPtr))
         {
            returnValue = FALSE;
            break;
         }

         addEntry(key, value);
      }
   }

   return(returnValue);
}

void KVEnvironment::destroy()
{
   for(int i = 0; i < mCount; i ++)
   {
      DADELETE(mKeys[i]);
      DADELETE(mValues[i]);
   }

   DADELETE(mKeys);
   DADELETE(mValues);

   mCount  = 0;
   mKeys   = NULL;
   mValues = NULL;
}

int KVEnvironment::findIndex(char *key)
{
   for(int i = 0; i < mCount; i ++)
      if(strcmp(key, mKeys[i]) == 0)
         return(i);

   return(-1);
}

void KVEnvironment::addEntry(char *key, char *value)
{
   int size         = mCount + 1;
   char **newKeys   = 0;
   char **newValues = 0;
   int i            = 0;

   DNEW(newKeys,   char *[size]);
   DNEW(newValues, char *[size]);

   for(i = 0; i < mCount; i ++)
   {
      newKeys[i]   = mKeys[i];
      newValues[i] = mValues[i];
   }

   newKeys[mCount]   = key;
   newValues[mCount] = value;

   if(mKeys)
      DADELETE(mKeys);

   if(mValues)
      DADELETE(mValues);

   mKeys   = newKeys;
   mValues = newValues;

   ++mCount;
}

void KVEnvironment::removeEntry(int index)
{
   if(mCount == 1)
   {
      destroy();
   }
   else
   {
      int size         = mCount - 1;
      char **newKeys   = 0;
      char **newValues = 0;

      DNEW(newKeys,   char *[size]);
      DNEW(newValues, char *[size]);

      for(int i = 0, j = 0; i < mCount; i ++)
      {
         if(i != index)
         {
            newKeys[j]   = mKeys[i];
            newValues[j] = mValues[i];
            j++;
         }
      }

      DADELETE(mKeys[index]);
      DADELETE(mValues[index]);

      DADELETE(mKeys);
      DADELETE(mValues);

      mKeys   = newKeys;
      mValues = newValues;

      --mCount;
   }
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

static char *openErrorMessage(char *name)
{
   static char *m1 = "Error reading file: [";
   static char *m2 = "]";

   int length   = strlen(m1) + strlen(name) + strlen(m2);

   char *buffer = 0;

   DNEW(buffer, char[length]);

   sprintf(buffer, "%s%s%s", m1, name, m2);

   return(buffer);
}

static char *trim(char *buffer)
{
   int start = -1;
   int end   = -1;

   for(int i = 0; buffer[i]; i ++)
   {
      if(!isspace(buffer[i]))
      {
         if(start == -1)
            start = i;

         end = i;
      }
   }

   if(start == -1)
      return(NULL);

   int nChars   = (end - start) + 1;
   char *result = 0;

   DNEW(result, char[nChars + 1]);

   sprintf(result, "%.*s", nChars, buffer + start);

   return(result);
}

static int parseLine(
   char *buffer, char **key, char **value, char **errMsgPtr
)
{
   char *theKey   = NULL;
   char *theValue = NULL;
   char *ptr      = NULL;

   if((ptr = strchr(buffer, '=')) != NULL)
   {
      *ptr = '\0';

      theKey   = trim(buffer);
      theValue = trim(ptr + 1);

      *ptr = '=';

      if(theKey == NULL || theValue == NULL)
      {
         DADELETE(theKey);
         DADELETE(theValue);

         theKey   = NULL;
         theValue = NULL;
      }
   }

   if(theKey != NULL)
   {
      *key   = theKey;
      *value = theValue;

      return(TRUE);
   }

   static char *m1 = "Illegal line: [";
   static char *m2 = "]";

   int length = strlen(m1) + strlen(buffer) + strlen(m2) + 1;

   DNEW(*errMsgPtr, char[length]);

   sprintf(*errMsgPtr, "%s%s%s", m1, buffer, m2);

   return(FALSE);
}

static int ignoreThisLine(char *s)
{
   for(int i = 0; s[i]; i ++)
      if(!isspace(s[i]))
         return(s[i] == Environment::getCommentChar());

   return(TRUE);
}

