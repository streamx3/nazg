#include "nz_list.h"

s32 nz_list_init(nz_list *list){
	s32 retval;

	retval = 0;

	if(list == NULL){
		retval = -1;
		goto nz_list_init_out;
	}

nz_list_init_out:;
	return retval;
}