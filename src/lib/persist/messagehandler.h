#ifndef _MESSAGE_HANDLER_H_
#   define _MESSAGE_HANDLER_H_

class MessageHandler
{
   public:
      virtual ~MessageHandler() {}
      virtual MessageHandler *clone()             = 0;
      virtual void accept(const char *theMessage) = 0;

      static MessageHandler *getDefaultHandler();
};

#endif
