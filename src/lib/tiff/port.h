/*
 * Warning, this file was automatically created by the TIFF configure script
 * VERSION:	 v3.4beta037
 * DATE:	 Sun Nov 29 13:56:11 CST 1998
 * TARGET:	 x86-sun-solaris2.6
 * CCOMPILER:	 /usr/local/bin/gcc-2.8.1
 */
#ifndef _PORT_
#define _PORT_ 1
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#define HOST_FILLORDER FILLORDER_MSB2LSB
#define HOST_BIGENDIAN	0
#define HAVE_MMAP 1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
typedef double dblparam_t;
#ifdef __STRICT_ANSI__
#define	INLINE	__inline__
#else
#define	INLINE	inline
#endif
#define GLOBALDATA(TYPE,NAME)	extern TYPE NAME
#ifdef __cplusplus
}
#endif
#endif
