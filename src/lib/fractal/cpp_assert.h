/*****************************************************************************
 * cpp_assert.h
 *
 * Including this header file makes the macro CPP_ASSERT(whatever) available.
 * The macro can be converted to a null statement by use of:
 *
 * #define DISABLE_CPP_ASSERT
 *
 * If an assertion fails, a message is printed showing:
 *
 *    - what was being asserted
 *    - the source file where the assertion was located
 *    - the source line where the assertion was located
 *
 * Additionally, if the compiler supports this feature the name of the method
 * where the assertion was located is also printed.
 *****************************************************************************/

// For prototype of "exit"

#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

#ifdef DISABLE_CPP_ASSERT

#   define CPP_ASSERT(x) ((void)0)

#else

#   if(!defined __GNUC__ || __GNUC__ < 2 || \
      __GNUC_MINOR__ < (defined __cplusplus ? 6 : 4))

#      define CPP_ASSERT(x)                                                 \
       do                                                                   \
       {                                                                    \
          if(!(x))                                                          \
          {                                                                 \
             cout <<                                                        \
             "Assertion Failed: [" << #x                  << "]" << endl << \
             "Source File     : [" << __FILE__            << "]" << endl << \
             "Line Number     : [" << __LINE__            << "]" << endl;   \
                                                                            \
             exit(-1);                                                      \
          }                                                                 \
                                                                            \
       } while(0)

#   else
#      define CPP_ASSERT(x)                                                 \
       do                                                                   \
       {                                                                    \
          if(!(x))                                                          \
          {                                                                 \
             cout <<                                                        \
             "Assertion Failed: [" << #x                  << "]" << endl << \
             "Source File     : [" << __FILE__            << "]" << endl << \
             "Line Number     : [" << __LINE__            << "]" << endl << \
             "Method Name     : [" << __PRETTY_FUNCTION__ << "]" << endl;   \
                                                                            \
             exit(-1);                                                      \
          }                                                                 \
                                                                            \
       } while(0)
#   endif
#endif
