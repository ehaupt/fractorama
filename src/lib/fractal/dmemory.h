#ifndef _DMEMORY_H_
#   define _DMEMORY_H_

/*
#define DMEMORY_DEBUG
*/

#ifdef DMEMORY_DEBUG

#include <stdio.h>

#   define DOUT(type, address)              \
       printf("%p: %s: %d: %s\n",           \
          address, __FILE__, __LINE__, type \
       )

#   define DNEW(ptr, expression) \
    do {                         \
       ptr = new expression;     \
       DOUT("new", ptr);         \
    }  while(0)

#   define DDELETE(ptr)     \
    do {                    \
       delete ptr;          \
       DOUT("delete", ptr); \
       ptr = 0;             \
    }  while(0)

#   define DADELETE(ptr)    \
    do {                    \
       delete [] ptr;       \
       DOUT("delete", ptr); \
       ptr = 0;             \
    }  while(0)

#else
#   define DNEW(ptr, expression)  ptr = new expression
#   define DDELETE(ptr)           delete ptr
#   define DADELETE(ptr)          delete [] ptr
#endif

#endif
