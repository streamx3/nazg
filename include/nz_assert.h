#ifndef NZ_ASSERT_H
#define NZ_ASSERT_H

#define NZ_ASSERT(__cond__,__fmt__,...) \
do{ \
	printf( "[%s" RESET "] "__fmt__";\n", \
			(__cond__) ? BOLDGREEN "SUCCESS" : BOLDRED "FAILURE", \
			##__VA_ARGS__); \
	if(!(__cond__)){ \
		exit(1); \
	} \
}while(0)


#define __NZ_ASTR_SIMPLIFIED(__exit__,__fmt__,...) \
do{ \
	printf( "[%s" RESET "] "__fmt__";\n", \
			(errh == NZ_ESUCCESS) ? BOLDGREEN "SUCCESS" : BOLDRED "FAILURE", \
			##__VA_ARGS__); \
	if(__exit__ == 1 && errh != NZ_ESUCCESS){ \
		exit(1); \
	} \
}while(0)

//Requires errh in current function and assumes it should be  NZ_ESUCCESS
#define NZ_ASRT_DUMB(__fmt__,...) \
do{ \
	__NZ_ASTR_SIMPLIFIED(1,__fmt__, ##__VA_ARGS__); \
}while(0)

#define NZ_WARN_DUMB(__fmt__,...) \
do{ \
	__NZ_ASTR_SIMPLIFIED(0,__fmt__, ##__VA_ARGS__); \
}while(0)

#define NZ_ASRTCND(cond) \
do{ \
	NZ_ASSERT(cond, #cond);\
}while(0)


#endif // NZ_ASSERT_H
