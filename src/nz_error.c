#include "nz_common.h"

s32 nz_err(nz_error *error, char *fmt, ...)
{
	va_list arg;
	s32 retval, written;
	char buffer[NZ_ERR_BUFSZ];

	written = 0;
	retval = NZ_ESUCCESS;
	if(error == NULL || fmt == NULL)
		return NZ_ENULLPTR;

	va_start(arg, fmt);
	written = snprintf(buffer, (unsigned int)NZ_ERR_BUFSZ - written, fmt, arg);
	va_end(arg);

	error->errstrlen = strlen(buffer);
	error->errstr = nz_malloc(written+1);
	if(error->errstr == NULL){
		return NZ_ENULLPTR;
	}
	strncpy(error->errstr,buffer,written);

	return retval;
}

s32 nz_err_free(nz_error *error)
{
	if(error == NULL)
		return NZ_ENULLPTR;

	if(error->errstr){
		nz_free(error->errstr);
		error->errstr = NULL;
	}
	nz_free(error);

	return NZ_ENULLPTR;
}