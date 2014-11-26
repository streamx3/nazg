#ifndef NZ_ASSERT_H
#define NZ_ASSERT_H

#define NZ_ASSERT(cond,fmt,...) \
do{ \
	printf( "[%s" RESET "] "fmt";\n", \
			(cond) ? BOLDGREEN "SUCCESS" : BOLDRED "FAILURE", \
			##__VA_ARGS__); \
	if(!(cond)){ \
		exit(1); \
	} \
}while(0)

//Requires errh in current function and assumes it should be  NZ_ESUCCESS
#define NZ_ASRT_DUMB(fmt,...) \
do{ \
	printf( "[%s" RESET "] "fmt";\n", \
			(errh == NZ_ESUCCESS) ? BOLDGREEN "SUCCESS" : BOLDRED "FAILURE", \
			##__VA_ARGS__); \
	if(errh != NZ_ESUCCESS){ \
		exit(1); \
	} \
}while(0)

#define NZ_ASRTCND(cond) \
do{ \
	NZ_ASSERT(cond, #cond);\
}while(0)


#endif // NZ_ASSERT_H