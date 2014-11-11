#ifndef NZ_MEMORY_H
#define NZ_MEMORY_H

#include "nz_space.h"

/*** Overriding default memory management *************************************/
#ifdef NZ_USERSPACE
#define	nz_malloc(x)	malloc(x)
#define nz_calloc(x,y)	calloc(x,y)
#define nz_realloc(x,y)	realloc(x,y)
#define nz_free(x)		free(x)
#else
#define	nz_malloc(x)	vmalloc(x)
#define nz_calloc(x,y)	vcalloc(x,y)
#define nz_realloc(x,y)	vrealloc(x,y)
#define nz_free(x)		vfree(x)
#endif


#endif // NZ_MEMORY_H