// C/C++ Headers

#include <stdio.h>

// Local Headers

#include "messagehandler.h"
#include "dmemory.h"

/*****************************************************************************
 * Declaration of class: DefaultMessageHandler
 *****************************************************************************/

class DefaultMessageHandler : public MessageHandler
{
   public:
      DefaultMessageHandler();
      ~DefaultMessageHandler();
      virtual MessageHandler *clone();
      void accept(const char *theMessage);
};

/*****************************************************************************
 * DefaultMessageHandler - methods
 *****************************************************************************/

DefaultMessageHandler::DefaultMessageHandler()
{
   // Nothing to do
}

DefaultMessageHandler::~DefaultMessageHandler()
{
   // Nothing to do
}

MessageHandler *DefaultMessageHandler::clone()
{
   DefaultMessageHandler *h = 0;
   DNEW(h, DefaultMessageHandler());
   return(h);
}

void DefaultMessageHandler::accept(const char *theMessage)
{
   printf("%s\n", theMessage);
}

/*****************************************************************************
 * MessageHandler - methods
 *****************************************************************************/

MessageHandler *MessageHandler::getDefaultHandler()
{
   DefaultMessageHandler *h = 0;
   DNEW(h, DefaultMessageHandler());
   return(h);
}
