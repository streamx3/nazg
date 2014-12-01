#include "nz_common.h"

#define __nz_errstr_try_flush(error) \
do{ \
	if(error->errstr){ \
		nz_free(error->errstr); \
		error->errstr = NULL; \
	} \
}while(0)

s32 nz_err_init(nz_error *error)
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

s32 nz_err_write(nz_error *error, s32 errcode, char *fmt, ...)
{
	va_list arg;
	s32 retval, written;
	char buffer[NZ_ERR_BUFSZ];

	written = 0;
	retval = NZ_ESUCCESS;
	if(error == NULL || fmt == NULL)
		return NZ_ENULLPTR;
	if(error->errstr == NULL && error->errstrlen != NULL){
		return NZ_EINVALID;
	}

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

s32 nz_err_print(nz_error *error)
{
	s32 retval;
	retval = NZ_ESUCCESS;

	if(error == NULL){
		return NZ_ENULLPTR;
	}
	if(error->errcode == NZ_ESUCCESS){
		if(error->errstr == NULL){
			
		}
	}


	return retval;
}

s32 nz_err_free(nz_error *error)
{
	if(error == NULL)
		return NZ_ENULLPTR;
	__nz_errstr_try_flush(error);
	return NZ_ESUCCESS;
}
