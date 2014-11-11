#include <stdio.h>
#include "nz_list.h"

#include "tests_pack_1.h"

int main(int argc, char* argv[]){
	s32 errh;
	nz_list list1;

	errh = test_1(&list1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "TEST 1");

	return 0;
}