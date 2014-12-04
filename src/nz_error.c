#include "nz_common.h"

/******************************************************************************/

#define __nz_errstr_try_flush(error) \
do{ \
	if(error->errstr){ \
		nz_free(error->errstr); \
		error->errstr = NULL; \
	} \
}while(0)

/******************************************************************************/

const char *nz_error_strings[] = {
	"NZ_ESUCCESS",
	"NZ_EUNKNOWN",
	"NZ_ENULLPTR",
	"NZ_ENOMEM",
	"NZ_ENOTFOUND",
	"NZ_EEXISTS",
	"NZ_EINVALID"
};

const char *nz_error_str_na = "N/A";

/******************************************************************************/

s32 nz_error_init(nz_error *error)
{
	s32 retval;
	retval = NZ_ESUCCESS;
	if(error == NULL){
		return NZ_ENULLPTR;
	}
	error->errcode = NZ_ESUCCESS;
	error->errstrlen = 0;
	error->errstr = NULL;

	return retval;
}

/******************************************************************************/

s32 nz_error_write(nz_error *error, s32 errcode, char *fmt, ...)
{
	va_list arg;
	s32 retval, written;
	char buffer[NZ_ERR_BUFSZ];

	written = 0;
	retval = NZ_ESUCCESS;
	if(error == NULL || fmt == NULL)
		return NZ_ENULLPTR;

	// If message is lost/corrupted
	if(error->errstr == NULL && error->errstrlen != 0)
		return NZ_EINVALID;

	va_start(arg, fmt);
	written = snprintf(buffer, (unsigned int)NZ_ERR_BUFSZ - written, fmt, arg);
	va_end(arg);

	__nz_errstr_try_flush(error);
	error->errstrlen = strlen(buffer);
	error->errstr = nz_malloc(written+1);
	if(error->errstr == NULL){
		return NZ_ENULLPTR;
	}
	error->errcode = NZ_EUNKNOWN;
	strncpy(error->errstr,buffer,written);

	return retval;
}

/******************************************************************************/

s32 nz_error_print(nz_error *error)
{
	const char *errcodestr, *errstring;
	s32 retval;

	retval = NZ_ESUCCESS;

	if(error == NULL){
		return NZ_ENULLPTR;
	}
	if(error->errstr == NULL){
		errstring = nz_error_str_na;
	}
	errcodestr = nz_errstr(error->errcode);
	if(errcodestr == NULL){
		errcodestr = nz_error_str_na;
	}
	nz_print(error->errcode == NZ_ESUCCESS ? NZ_LVL_INFO : NZ_LVL_ERR \
			 "[%s] %s\n", errcodestr, errstring);

	return retval;
}

/******************************************************************************/

const char* nz_errstr(s32 error_code)
{
	if(error_code < 0)
		error_code = ~ error_code;
	if(error_code < sizeof(nz_error_strings))
		return nz_error_strings[error_code];
	return NULL;
}

/******************************************************************************/

s32 nz_error_free(nz_error *error)
{
	if(error == NULL)
		return NZ_ENULLPTR;
	__nz_errstr_try_flush(error);
	return NZ_ESUCCESS;
}
