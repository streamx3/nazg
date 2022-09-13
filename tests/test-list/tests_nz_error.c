#include "tests_nz_error.h"

#define T005ErrStr "Sample error message"

s32 test_nz_error_write() {
    nz_error *err1;
    err1 = nz_malloc(sizeof(nz_error));
    nz_error_init(err1);
    NZ_ASRTCND(err1 != NULL);
    NZ_ASRTCND(NZ_ESUCCESS == nz_error_write(err1, NZ_ESUCCESS, T005ErrStr));
    NZ_ASRTCND(err1->errstr != NULL);
    NZ_ASRTCND(strcmp(err1->errstr, T005ErrStr) == 0);
    NZ_ASRTCND(err1->errstrlen == strlen(T005ErrStr));
    NZ_ASRTCND(err1->errcode == NZ_ESUCCESS);
    NZ_ASRTCND(NZ_ESUCCESS == nz_error_free(err1) );
    nz_free(err1);

    return NZ_ESUCCESS;
}
