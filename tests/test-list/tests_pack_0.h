#ifndef TESTS_PACK_0_H
#define TESTS_PACK_0_H

#include "nz_common.h"

// Error creation test
void test_005(){
	nz_error *err1;
	err1 = nz_malloc(sizeof(nz_error));
	NZ_ASRTCND(err1 != NULL);
	//TODO Continue here
}

#endif // TESTS_PACK_0_H