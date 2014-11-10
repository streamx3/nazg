#ifndef NZ_ASSERT_H
#define NZ_ASSERT_H

#define NZ_ASSERT(cond,fmt,...) \
do{\
	printf( "[%s" RESET "] "fmt";\n", \
			(cond) ? BOLDGREEN "SUCCESS" : BOLDRED "FAILURE",\
			##__VA_ARGS__);\
	if(!(cond)){\
		return 1;\
	}\
}while(0)

#endif // NZ_ASSERT_H