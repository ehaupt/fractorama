// C/C++ Headers

#include <string.h>
#include <time.h>

// Local Headers

#include "fileenvironment.h"
#include "persist.h"
#include "dmemory.h"

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static char *writeErrorMessage(char *name);

FileEnvironment::FileEnvironment(char *fileName, Environment *environment)
   : FilterEnvironment(environment),
     mFileName(0)
{
   DNEW(mFileName, char[strlen(fileName) + 1]);
   strcpy(mFileName, fileName);
}

FileEnvironment::~FileEnvironment()
{
   DADELETE(mFileName);
}

Environment *FileEnvironment::clone(char **errMsgPtr)
{
   FileEnvironment *e = 0;

   DNEW(
      e, FileEnvironment(mFileName, getEnvironment()->clone(errMsgPtr))
   );

   return(e);
}

int FileEnvironment::storeValue(char *key, char *value, char **errMsgPtr)
{
   int returnValue = FilterEnvironment::storeValue(key, value, errMsgPtr);

   if(!returnValue)
      return(returnValue);

   return(write(errMsgPtr));
}

int FileEnvironment::setValue(char *key, char *value, char **errMsgPtr)
{
   int returnValue = FilterEnvironment::setValue(key, value, errMsgPtr);

   if(!returnValue)
      return(returnValue);

   return(write(errMsgPtr));
}

int FileEnvironment::add(char *key, char *value, char **errMsgPtr)
{
   int returnValue = FilterEnvironment::add(key, value, errMsgPtr);

   if(!returnValue)
      return(returnValue);

   return(write(errMsgPtr));
}

int FileEnvironment::remove(char *key, char **errMsgPtr)
{
   int returnValue = FilterEnvironment::remove(key, errMsgPtr);

   if(!returnValue)
      return(returnValue);

   return(write(errMsgPtr));
}

int FileEnvironment::write(char **errMsgPtr)
{
   int status = FALSE;
   FILE *f    = fopen(mFileName, "w");

   if(f == NULL)
   {
      // The fopen might well have failed because mFileName includes
      // a directory path that doesn't yet exist, attempt to make
      // the directory and try one more time

      char *directory = Persist::directoryFromFileName(mFileName);

      if(Persist::makeDirectories(directory) &&
         (f = fopen(mFileName, "w")) != NULL)
      {
         status = TRUE;
      }

      DADELETE(directory);

      if(!status)
         *errMsgPtr = writeErrorMessage(mFileName);
   }
   else
      status = TRUE;

   if(status)
   {
      int i = 0;

      for(i = 0; i < 60; i ++)
         fprintf(f, "%c", getCommentChar());

      fprintf(f, "\n");

      time_t currentTime = time(NULL);

      fprintf(
         f,
         "%c Created: %s",
         getCommentChar(),
         ctime(&currentTime)
      );

      for(i = 0; i < 60; i ++)
         fprintf(f, "%c", getCommentChar());

      fprintf(f, "\n");

      status = FilterEnvironment::print(f, errMsgPtr);

      fclose(f);
   }

   return(status);
}

/*****************************************************************************
 * Local functions
 *****************************************************************************/

static char *writeErrorMessage(char *name)
{
   static char *m1 = "Error writing file: [";
   static char *m2 = "]";

   int length   = strlen(m1) + strlen(name) + strlen(m2);

   char *buffer = 0;

   DNEW(buffer, char[length]);

   sprintf(buffer, "%s%s%s", m1, name, m2);

   return(buffer);
}
