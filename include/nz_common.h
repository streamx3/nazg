#ifndef NZ_COMMON_H
#define NZ_COMMON_H

/*** Global includes **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*** Local includes ***********************************************************/

#include "nz_assert.h"
#include "nz_memory.h"
#include "nz_error.h"
#include "nz_int.h"

/*** Typing colours ***********************************************************/

#define RESET		"\033[0m"			// Default test
#define BLACK		"\033[30m"			// Black
#define RED			"\033[31m"			// Red
#define GREEN		"\033[32m"			// Green
#define YELLOW		"\033[33m"			// Yellow
#define BLUE		"\033[34m"			// Blue
#define MAGENTA		"\033[35m"			// Magenta
#define CYAN		"\033[36m"			// Cyan
#define WHITE		"\033[37m"			// White
#define BOLDBLACK	"\033[1m\033[30m"	// Bold Black
#define BOLDRED		"\033[1m\033[31m"	// Bold Red
#define BOLDGREEN	"\033[1m\033[32m"	// Bold Green
#define BOLDYELLOW	"\033[1m\033[33m"	// Bold Yellow
#define BOLDBLUE	"\033[1m\033[34m"	// Bold Blue
#define BOLDMAGENTA	"\033[1m\033[35m"	// Bold Magenta
#define BOLDCYAN	"\033[1m\033[36m"	// Bold Cyan
#define BOLDWHITE	"\033[1m\033[37m"	// Bold White

/*** Useful macro *************************************************************/

#define __NZ_CHKNULLPTR_JMP(ptr,retv,jmp) \
	do{ \
		if( ptr == NULL ){ \
			retv = NZ_ENULLPTR; \
			goto jmp; \
		} \
	}while(0);

/* Will jump if condition is true */
#define __NZ_CHKCOND_JMP(cond,retv,jmp) \
	do{ \
		if( cond ){ \
			retv = NZ_ENULLPTR; \
			goto jmp; \
		} \
	}while(0);

/*** CLI-LOGS *****************************************************************/

#ifdef NZ_USERSPACE

#define nz_print(FMT, ...) \
do{ \
	printf(FMT, ##__VA_ARGS__); \
}while(0)

#else

#define nz_print(FMT, ...) \
do{ \
	printk(FMT, ##__VA_ARGS__); \
}while(0)

#endif


/*
#define NZ_COUT(LEVEL, FMT, ...) \
do{ \
	nz_print() \
}while(0)
*/


#define NZ_LOG(fmt, ...) \
do{\
	nz_print(NZ_LVL_NOTICE"[" GREEN "NZ L" RESET "][%s][%d][%s]" fmt "\n", \
	__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ ); \
}while(0)

#define NZ_ERR(fmt, ...) \
do{\
	nz_print(NZ_LVL_ERR"[" RED "NZ E" RESET "][%s][%d][%s]" fmt "\n", \
	__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__ ); \
}while(0)


/*** Types ********************************************************************/

typedef void (*nz_destructor_t)(void*);

/******************************************************************************/

#endif // NZ_COMMON_H
