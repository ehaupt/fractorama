// Standard C++ headers

#include <iostream>
#include <stdlib.h>
#include <ctype.h>

#include <errno.h>

using std::cout;
using std::endl;

// Qt headers

#include <qapplication.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qregexp.h>

// Local headers

#include "application.h"
#include "persist.h"
#include "kvenvironment.h"
#include "nocaseenvironment.h"
#include "fileenvironment.h"
#include "messagehandler.h"
#include "state.h"
#include "dmemory.h"

/*****************************************************************************
 * Local function prototypes
 *****************************************************************************/

static int getFileNameIndex(int argc, char **argv);
static int getOption(int argc, char **argv, char theChar);
static int getExtendedOption(int argc, char **argv, char *key, char *value);
static Persist *handlePersistence(char *argv0, char **errMsgPtr);

/*****************************************************************************
 * Singleton Persist - for saving application state
 *****************************************************************************/

static Persist *instance = NULL;

/*****************************************************************************
 * Local class, for displaying errors related to persistence
 *****************************************************************************/

class PersistMessageHandler : public MessageHandler
{
   public:
      virtual MessageHandler *clone();
      virtual void accept(const char *theMessage);
      static void handleErrMsg(char *theMessage);
};

MessageHandler *PersistMessageHandler::clone()
{
   MessageHandler *m = 0;

   DNEW(m, PersistMessageHandler());

   return(m);
}

void PersistMessageHandler::accept(const char *theMessage)
{
   PersistMessageHandler::handleErrMsg((char *)theMessage);
}

void PersistMessageHandler::handleErrMsg(char *theMessage)
{
   QMessageBox::information(NULL, "Warning", theMessage, "Ok");
   DADELETE(theMessage);
}

/*****************************************************************************
 * Local function to initialize persistence
 *****************************************************************************/

static Persist *handlePersistence(char *argv0, char **errMsgPtr)
{
   char *persistName = NULL;

#ifdef _WIN32

   persistName = Persist::getApplicationDirectory(
      argv0,
      "fractorama.txt", // filename associated with persistent state
      NULL,            // don't store it in a subdirectory
      TRUE             // create one persistent file per user
   );

#else

   persistName = Persist::getUserDirectory(
      "fractorama.txt", // filename associated with persistent state
      ".fractorama"     // store data in: '.fractorama' subdirectory
   );

#endif

   if(persistName == NULL)
   {
      char *message =
         "Unable to determine persistent storage filename "
         "from program name: [%s]";

      int size = strlen(message) - strlen("%s") + strlen(argv0) + 1;

      DNEW(*errMsgPtr, char[size]);

      sprintf(*errMsgPtr, message, argv0);

      return(FALSE);
   }

   // Create our environment object, note that via the flag we
   // pass "KVEnvironment::ErrorIfReadFails" we are indicating that
   // for "persistName" to not be present isn't an error but an
   // error encountered while reading from "persistName" (when it
   // does exist) is an error

   Environment *env = KVEnvironment::create(
      persistName,
      KVEnvironment::ErrorIfReadFails,
      errMsgPtr
   );

   if(env == NULL)
   {
      DADELETE(persistName);
      return(FALSE);
   }

   // We want this object to be case insensitive

   DNEW(env, NoCaseEnvironment(env));

   MessageHandler *handler = 0;

   DNEW(handler, PersistMessageHandler());

   // Now create our application-wide persistence object, it will
   // automatically commit any changes to its state to disk

   FileEnvironment *f = 0;

   DNEW(f, FileEnvironment(persistName, env));

   DNEW(instance, Persist(f, handler));

   // We're done with 'persistName'

   DADELETE(persistName);

   char *errMsg = NULL;
   env          = env->clone(&errMsg);

   if(env == NULL)
   {
      PersistMessageHandler::handleErrMsg(errMsg);
      return(NULL);
   }

   Persist *p = 0;

   DNEW(p, Persist(env, handler->clone()));

   return(p);
}

/*****************************************************************************
 * Local functions
 *****************************************************************************/

static int getFileNameIndex(int argc, char **argv)
{
   for(int i = 1; i < argc; i ++)
   {
      switch(argv[i][0])
      {
         case '-': break;
         default : return(i);
      }
   }

   return(-1);
}

static int getOption(int argc, char **argv, char theChar)
{
   char upper = toupper(theChar);
   char lower = tolower(theChar);

   for(int i = 1; i < argc; i ++)
   {
      switch(argv[i][0])
      {
         case '-':
         {
            for(int j = 1; argv[i][j]; j ++)
            {
               if(j == 1 && argv[i][j] == '-')
                  break;
                                                                                
               if(argv[i][j] == upper || argv[i][j] == lower)
                  return(1);
            }
         }
         break;
      }
   }

   return(0);
}

static int getExtendedOption(int argc, char **argv, char *key, char *value)
{
   char pattern[255] = { '\0' };

   sprintf(pattern, "^--%s=(.*)$", key);

   QRegExp rx(pattern, FALSE);

   for(int i = 1; i < argc; i ++)
   {
      if(rx.search(argv[i]) != -1)
      {
         strcpy(value, rx.cap(1).latin1());
         return(TRUE);
      }
   }

   return(FALSE);
}

Persist *getApplicationInstance()
{
   return(instance);
}

/*****************************************************************************
 * main
 *****************************************************************************/

int main(int argc, char ** argv)
{
   int fileNameIndex = getFileNameIndex(argc, argv);
   int noGuiFlag      = getOption(argc, argv, 'n');
   int doHelpFlag     = getOption(argc, argv, 'h');
   int doAntiAlias    = getOption(argc, argv, 'a');

   if(doHelpFlag)
   {
      cout << "Usage: " << argv[0] << " {options} {fileName}\n";
      cout << "         -n: run without gui\n";
      cout << "         -a: apply antialiasing to output tiff file\n";
      cout << "         -h: display this message\n";
      cout << " --size=WxH: set output image size\n";
      return(-1);
   }

   if(noGuiFlag)
   {
      if(fileNameIndex == -1)
      {
         cout << "Filename required to run in non-gui mode" << endl;
         return(-1);
      }

      int theWidth    = 0;
      int theHeight   = 0;
      char value[255] = { '\0' };

      if(getExtendedOption(argc, argv, "size", value))
      {
         QRegExp rx("^([0-9]+)[xX]([0-9]+)$");

         if(rx.search(value) != -1)
         {
            theWidth  = atoi(rx.cap(1).latin1());
            theHeight = atoi(rx.cap(2).latin1());
         }
      }

      return(
         ApplicationWindow::writeTiffFile(
            argv[fileNameIndex],
            doAntiAlias,
            theWidth,
            theHeight
         )
      );
   }

   QApplication theApplication(argc, argv);

   // Determine the name/location of our "home" document

   char *s = Persist::getApplicationDirectory(
      argv[0], "index.html", "doc", FALSE
   );

   QFileInfo info(s);
   QString   home = info.absFilePath();

   DADELETE(s);

   // Initialize persistence ...

   char *errMsg = NULL;
   Persist *p   = NULL;

   if((p = handlePersistence(argv[0], &errMsg)) == NULL)
   {
      PersistMessageHandler::handleErrMsg(errMsg);
      return(-1);
   }

   State *theState = 0;

   DNEW(theState, State(p));

   // If the user gave the '-a' command-line flag set the initial
   // state of 'antialias' to true

   if(doAntiAlias)
      theState->setAntiAlias(TRUE);

   ApplicationWindow *theWindow = new ApplicationWindow(
      theState, home,
      fileNameIndex == -1 ? NULL : argv[fileNameIndex]
   );

   theWindow->show();

   // Arrange for the application to exit when the last window is closed

   theApplication.connect(
      &theApplication,
      SIGNAL(lastWindowClosed()),
      &theApplication,
      SLOT(quit())
   );

   int status = theApplication.exec();

   DDELETE(instance);

   return(status);

}  /* main */
