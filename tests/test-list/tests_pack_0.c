#include "tests_pack_0.h"

s32 test_005()
{
#define T005ErrStr "Sample error message"
	nz_error *err1;
	err1 = nz_malloc(sizeof(nz_error));
	NZ_ASRTCND(err1 != NULL);
	NZ_ASRTCND(NZ_ESUCCESS == nz_err(err1, T005ErrStr));
	NZ_ASRTCND(err1->errstr != NULL);
	NZ_ASRTCND(strcmp(err1->errstr, T005ErrStr) == 0);
	NZ_ASRTCND(err1->errstrlen == strlen(T005ErrStr));
	NZ_ASRTCND(err1->errcode != NZ_ESUCCESS);
	NZ_ASRTCND(NZ_ESUCCESS == nz_err_free(err1) );
	nz_free(err1);

	return NZ_ESUCCESS;
}
