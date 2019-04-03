#ifndef NZ_ERROR_H
#define NZ_ERROR_H

#include "nz_int.h"
#include "nz_space.h"
#include "nz_levels.h"

#define NZ_ERR_BUFSZ 512

/*! NAZG Error codes */
#define NZ_ESUCCESS     0
#define NZ_EUNKNOWN     1
#define NZ_ENULLPTR     2
#define NZ_ENOMEM       3
#define NZ_ENOTFOUND    4 /* 404 */
#define NZ_EEXISTS      5
#define NZ_EINVALID     6

extern const char *nz_error_strings[];
extern const char *nz_error_str_na;

/*!
    \brief Structure for heavy self-diagnostic
*/
typedef struct nz_error nz_error;
struct nz_error{
    s32 errcode;
    u32 errstrlen;
    char *errstr;
};

s32 nz_error_init(nz_error *error);

s32 nz_error_write(nz_error *error, s32 errcode, char *fmt, ...);

const char* nz_errstr(s32 error_code);

s32 nz_error_free(nz_error *error);

s32 __nz_error_assert(nz_error *error, s32 doexit, s32 silent);

#define nz_error_print(perror)\
    __nz_error_assert(perror,0,0)

#define nz_error_assert(perror)\
    __nz_error_assert(perror,1,0)

#define nz_error_assert_silent(perror)\
    __nz_error_assert(perror,1,1)

#endif // NZ_ERROR_H
