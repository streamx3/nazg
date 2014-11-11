#include "tests_pack_1.h"

s32 test_1(nz_list *list)
{
	s32 retval;
	retval = NZ_ESUCCESS;
	NZ_ASSERT(list!= NULL, "Incoming list valid");
	retval = nz_list_init(list);
	NZ_ASSERT(retval == NZ_ESUCCESS, "List init");
	retval = nz_list_exit(list);
	NZ_ASSERT(retval == NZ_ESUCCESS, "List exit");

	return retval;
}