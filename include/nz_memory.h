#ifndef NZ_MEMORY_H
#define NZ_MEMORY_H

/*! Overriding default memory management */
#define	nz_malloc(x)	malloc(x)
#define nz_calloc(x,y)	calloc(x,y)
#define nz_realloc(x,y)	realloc(x,y)
#define nz_free(x)		free(x)

#endif // NZ_MEMORY_H