// C/C++ headers

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "persist.h"
#include "kvenvironment.h"
#include "fileenvironment.h"
#include "nocaseenvironment.h"
#include "dmemory.h"

using std::cout;
using std::endl;

int main(int, char **argv)
{
   // Get our persistent storage file name ...

   char *file =
      Persist::getApplicationDirectory(
         argv[0],
         "stuff.txt",
         ".junk\\mess",
         TRUE
      );

   cout << "FileName: [" << file << "]" << endl;

   // Now create our appropriate Environment subclass, choose
   // the "ErrorIfReadFails" option since we don't require that "file"
   // be present (but it is an error if the file exists and we fail
   // while reading it)

   char *errMsg = NULL;

   Environment *environment = KVEnvironment::create(
      file,
      KVEnvironment::ErrorIfReadFails,
      &errMsg
   );

   if(environment == NULL)
   {
      DADELETE(file);

      cout << errMsg << endl;

      DADELETE(errMsg);

      return(-1);
   }

   // Set up our desired behaviors for our Environment

   NoCaseEnvironment *ne = 0;

   DNEW(ne, NoCaseEnvironment(environment));
   DNEW(environment, FileEnvironment(file, ne));

   // We're done with "file"

   DADELETE(file);

   // Now set up persistence

   Persist *p = Persist::getInstance();
   errMsg        = NULL;

   if(!p->initialize(environment))
   {
      DDELETE(environment);
      return(-1);
   }

   // "environment" now belongs to our Persist object

   p->storeValue("you", "suck");

   return(0);

}  /* main */
