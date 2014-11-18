#include <stdio.h>
#include "nz_list.h"

#include "tests_pack_1.h"

int main(int argc, char* argv[]){
	s32 errh;
	nz_list list1;

	errh = test_1(&list1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "TEST 1");
	errh = test_2(&list1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "TEST 2");
	test_3(&list1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "TEST 3");
	test_4(&list1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "TEST 4");

	return 0;
}
