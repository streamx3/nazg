#ifndef NZ_ERROR_H
#define NZ_ERROR_H

/*! NAZG Error codes */
#define NZ_ESUCCESS		0
#define NZ_EUNKNOWN		1
#define NZ_ENULLPTR		2
#define NZ_ENOMEM		3
#define NZ_ENOTFOUND	4 /* 404 */
#define NZ_EEXISTS		5
#define NZ_EINVALID		6

/*!
	\brief Structure for heavy self-diagnostic
*/
typedef struct nz_error nz_error;
struct nz_error{
	s32 errcode;
	u32 errstrlen;
	char *errstr;
};

#endif // NZ_ERROR_H