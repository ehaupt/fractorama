// C/C++ Headers

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#   include <windows.h>
#   include <ctype.h>
#   include <direct.h>
#else
#   include <unistd.h>
#endif

// Local Headers

#include "persist.h"
#include "messagehandler.h"
#include "dmemory.h"

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static char *canonicalizeSubDirectory(char *subdir);
static char *getPath();
static int programExists(
   const char *path, const char *separator, const char *program
);
static char *findPath(const char *argv0);
static char *getUserName();
static char *getHome();
static char *fixDirectory(char *directory);

/*****************************************************************************
 * Local #defines
 *****************************************************************************/

#ifdef _WIN32
#   define CSEP      '\\'
#   define SSEP      "\\"
#   define SPATH     ";"
#   define OTHER_SEP '/'
#else
#   define CSEP      '/'
#   define SSEP      "/"
#   define SPATH     ":"
#   define OTHER_SEP '\\'
#endif

/*****************************************************************************
 * Definition of class Persist
 *****************************************************************************/

char *Persist::getApplicationDirectory(
   char *argv0,
   char *fileName,
   char *subdir,
   int perUser
)
{
   char *result = findPath(argv0);

   if(result == NULL)
      return(result);

   if(fileName)
   {
      char *suffix = NULL;
      char *user   = NULL;

      int size = strlen(result);

      if(subdir)
      {
         suffix = canonicalizeSubDirectory(subdir);
         size += strlen(suffix);
      }

      if(perUser)
      {
         if((user = getUserName()) != NULL)
            size += (strlen(user) + 1);
      }

      size += strlen(fileName);

      char *buffer = 0;
      DNEW(buffer, char[size + 1]);

      sprintf(
         buffer,
         "%s%s%s%s%s",
         result,
         (suffix ? suffix : ""),
         (user   ? user   : ""),
         (user   ? "_"    : ""),
         fileName
      );

      if(user)
         DADELETE(user);

      DADELETE(suffix);
      DADELETE(result);

      result = buffer;
   }

   return(result);
}

char *Persist::getUserDirectory(char *fileName, char *subdir)
{
   char *home   = getHome();
   int size     = strlen(home);

   if(fileName)
   {
      size += strlen(fileName);

      char *suffix = NULL;

      if(subdir)
      {
         suffix = canonicalizeSubDirectory(subdir);
         size += strlen(suffix);
      }

      size++;

      char *buffer = 0;
      DNEW(buffer, char[size]);

      sprintf(
         buffer,
         "%s%s%s",
         home, suffix ? suffix : "", fileName
      );

      DADELETE(suffix);
      DADELETE(home);

      home = buffer;
   }

   return(home);
}

char *Persist::directoryFromFileName(char *fileName)
{
   char *result = NULL;
   char *ptr    = strrchr(fileName, CSEP);

   if(ptr == NULL)
   {
      DNEW(result, char[3]);
      sprintf(result, ".%c", CSEP);
   }
   else
   {
      int length = (ptr - fileName) + 1;
      DNEW(result, char[length + 1]);
      sprintf(result, "%.*s", length, fileName);
   }

   return(result);
}

int Persist::directoryExists(char *theDirectory)
{
   char *fixedDirectory = fixDirectory(theDirectory);
   struct stat s;

   int returnValue = FALSE;

   if(stat(fixedDirectory, &s) == 0 && (s.st_mode & S_IFDIR) == S_IFDIR)
      returnValue = TRUE;

   DADELETE(fixedDirectory);

   return(returnValue);
}

int Persist::makeDirectory(char *theDirectory)
{
   int status = 0;

#ifdef _WIN32

   status = mkdir(theDirectory);

#else

   // Create the directory with wide-open permissions, but restore
   // the umask to its original value when we're done making
   // the directory

   int currentValue = umask(0);
   status           = mkdir(theDirectory, 0777);
   umask(currentValue);

#endif

   return(status == 0 ? TRUE : FALSE);
}

int Persist::makeDirectories(char *theDirectory)
{
   if(directoryExists(theDirectory) || makeDirectory(theDirectory))
      return(TRUE);

   int returnValue = FALSE;

   // Get our parent directory

   int length = strlen(theDirectory);

   if(length > 0)
   {
      char *ptr = theDirectory + (length - 1);

      if(*ptr == CSEP)
         --ptr;

      while(ptr >= theDirectory && *ptr != CSEP)
         --ptr;

      if(*ptr == CSEP)
      {
         int count       = (ptr - theDirectory) + 1;
         char *parentDir = 0;

         DNEW(parentDir, char[count + 1]);

         sprintf(parentDir, "%.*s", count, theDirectory);

         returnValue =
            (makeDirectories(parentDir) && makeDirectory(theDirectory));

         DADELETE(parentDir);
      }
   }

   return(returnValue);
}

Persist::Persist(
   Environment *environment,
   MessageHandler *handler
)  :
   mEnvironment(0),
   mHandler(0)
{
   mEnvironment = environment;
   mHandler     = (handler ? handler : MessageHandler::getDefaultHandler());
}

Persist::~Persist()
{
   DDELETE(mEnvironment);
   DDELETE(mHandler);
}

Persist *Persist::clone()
{
   char *errMsg     = NULL;
   Environment *env = mEnvironment->clone(&errMsg);

   if(env == NULL)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);

      return(NULL);
   }

   Persist *p = 0;
   DNEW(p, Persist(env, mHandler->clone()));

   return(p);
}

int Persist::keyDefined(char *key)
{
   return(mEnvironment->keyDefined(key));
   return(FALSE);
}

char *Persist::getValueDefaulted(char *key, char *theDefault)
{
   char *errMsg = NULL;
   char *value  = mEnvironment->getValueDefaulted(key, theDefault, &errMsg);

   if(!value)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(value);
}

char *Persist::getValue(char *key)
{
   char *errMsg = NULL;
   char *value  = mEnvironment->getValue(key, &errMsg);

   if(!value)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(value);
}

int Persist::storeValue(char *key, char *value)
{
   char *errMsg = NULL;
   int returnValue  = mEnvironment->storeValue(key, value, &errMsg);

   if(!returnValue)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(returnValue);
}

int Persist::setValue(char *key, char *value)
{
   char *errMsg    = NULL;
   int returnValue = mEnvironment->setValue(key, value, &errMsg);

   if(!returnValue)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(returnValue);
}

int Persist::add(char *key, char *value)
{
   char *errMsg    = NULL;
   int returnValue = mEnvironment->add(key, value, &errMsg);

   if(!returnValue)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(returnValue);
}

int Persist::remove(char *key)
{
   char *errMsg    = NULL;
   int returnValue = mEnvironment->remove(key, &errMsg);

   if(!returnValue)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(returnValue);
}

int Persist::print(FILE *out)
{
   char *errMsg    = NULL;
   int returnValue = mEnvironment->print(out, &errMsg);

   if(!returnValue)
   {
      mHandler->accept(errMsg);
      DADELETE(errMsg);
   }

   return(returnValue);
}

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

// Base path location related functions

static char *findPath(const char *argv0)
{
   char *result = NULL;

   // First determine if argv0 contains the platform-dependent directory
   // separator character

   char *separator = strrchr(argv0, CSEP);

   if(separator == NULL)
   {
      // We need to search PATH for the location of the program

      char *path = getPath();

      if(path != NULL)
      {
         char *token = strtok(path, SPATH);

         while(token != NULL && result == NULL)
         {
            char *suffix = "";

            if(token[strlen(token) - 1] != CSEP)
               suffix = SSEP;

            if(programExists(token, suffix, argv0))
            {
               DNEW(result, char[strlen(token) + strlen(suffix) + 1]);

               sprintf(result, "%s%s", token, suffix);
               break;
            }

            token = strtok(NULL, SPATH);
         }

         DADELETE(path);
      }
   }
   else
   {
      // We want to grab all characters up to and including the last
      // separator

      int count = (separator - argv0) + 1;
      DNEW(result, char[count + 1]);

      sprintf(result, "%.*s", count, argv0);
   }

   return(result);
}

static char *canonicalizeSubDirectory(char *subdir)
{
   int length   = strlen(subdir);
   char *suffix = "";
   char *buffer = NULL;

   if(length == 0 || subdir[length - 1] != CSEP)
      suffix = SSEP;

   DNEW(buffer, char[length + strlen(suffix) + 1]);
   sprintf(buffer, "%s%s", subdir, suffix);

   for(int i = 0; buffer[i]; i ++)
      if(buffer[i] == OTHER_SEP)
         buffer[i] = CSEP;

   return(buffer);
}

static char *getPath()
{
   // On windows, your PATH is always treated like it contains the
   // current directory as its first element

#ifdef _WIN32
#   define IMPLICIT_PATH ".;"
#else
#   define IMPLICIT_PATH ""
#endif

   char *path   = getenv("PATH");
   char *buffer = NULL;

   if(path != NULL)
   {
      DNEW(buffer, char[strlen(path) + strlen(IMPLICIT_PATH) + 1]);

      sprintf(buffer, "%s%s", IMPLICIT_PATH, path);
   }

   return(buffer);
}

static int programExists(
   const char *path, const char *separator, const char *program
)
{
   char *fullPath = NULL;
   char *suffix   = "";

#ifdef _WIN32

   // If "program" does not end in ".exe" (case insensitive)
   // we'll tack on that suffix before attempting to decide if the
   // file exists or not

   int length = strlen(program);

   if(length > (int)strlen(".exe"))
   {
      if(program[length - 4] != '.' ||
        (program[length - 3] != 'e' && program[length - 3] != 'E') ||
        (program[length - 2] != 'x' && program[length - 2] != 'X') ||
        (program[length - 1] != 'e' && program[length - 1] != 'E'))
      {
         suffix = ".exe";
      }
   }
   else
      suffix = ".exe";
#endif

   DNEW(
      fullPath,
      char[
         strlen(path) + strlen(separator) +
         strlen(program) + strlen(suffix) + 1
      ]
   );

   sprintf(fullPath, "%s%s%s%s", path, separator, program, suffix);

   FILE *f = fopen(fullPath, "r");

   DADELETE(fullPath);

   if(f == NULL)
      return(FALSE);

   fclose(f);

   return(TRUE);
}

static char *getUserName()
{
   char *userName = NULL;

#ifdef _WIN32

   char lpBuffer[512]  = { '\0' };
   unsigned long nSize = sizeof(lpBuffer);

   if(GetUserName(lpBuffer, &nSize))
   {
      if(nSize > 0)
      {
         DNEW(userName, char[strlen(lpBuffer) + 1]);
         strcpy(userName, lpBuffer);
      }
   }

#else

   char *value = getenv("USER");

   if(value != NULL)
   {
      DNEW(userName, char[strlen(value) + 1]);
      strcpy(userName, value);
   }
#endif

   return(userName);
}

static char *getHome()
{
   char *home = NULL;

#ifdef _WIN32

   char lpBuffer[512] = { '\0' };
   unsigned int uSize = sizeof(lpBuffer);

   if(GetWindowsDirectory(lpBuffer, uSize) > 0)
   {
      char *suffix = (lpBuffer[uSize - 1] == CSEP ? "" : SSEP);
      char *user   = NULL;

      if((user = getUserName()) == NULL)
      {
         char *defaultUser = "Default User";
         DNEW(user, char[strlen(defaultUser) + 1]);
         strcpy(user, defaultUser);
      }

      char *profiles = "profiles" SSEP;

      int length = strlen(lpBuffer) + strlen(suffix) +
                   strlen(profiles) + strlen(user)   +
                   strlen(SSEP)     + 1;

      DNEW(home, char[length]);

      sprintf(home, "%s%s%s%s%s", lpBuffer, suffix, profiles, user, SSEP);

      DADELETE(user);
   }

#else

   char *value = getenv("HOME");
   int length  = 0;

   if(value != NULL && (length = strlen(value)) > 0)
   {
      const char *suffix = (value[length - 1] == CSEP ? "" : SSEP);

      length = length + strlen(suffix) + 1;
      DNEW(home, char[length]);

      sprintf(home, "%s%s", value, suffix);
   }
#endif

   return(home);
}

static char *fixDirectory(char *directory)
{
   // Put "directory" into a format such that 'stat' will tell the
   // truth as to whether or not the directory exists

   char *result = NULL;
   int length   = strlen(directory);

#ifdef _WIN32

   // We first deal with cases:
   //
   //    (1) [a-zA-Z] + ":"
   //    (2) [a-zA-Z] + ":" + "\"
   //
   // stat will only say the the directory exists for (2) above, so
   // we change (1) into (2) if we need to

   if(isalpha(directory[0]) && directory[1] == ':' &&
      length == 2 || (length == 3 && directory[2] == '\\'))
   {
      if(length == 2)
      {
         DNEW(result, char[length + 2]);
         sprintf(result, "%s\\", directory);
      }
   }

   // If the path ends in '\' we'll need to strip off the '\'
   // to make stat work properly unless directory == "\"

   else if(length > 1 && directory[length - 1] == '\\')
   {
      DNEW(result, char[length]);
      sprintf(result, "%.*s", length - 1, directory);
   }
#endif

   if(result == NULL)
   {
      DNEW(result, char[length + 1]);
      strcpy(result, directory);
   }

   return(result);
}
