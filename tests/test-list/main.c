#include <stdio.h>
#include "nz_list.h"

int main(int argc, char* argv[]){
	s32 errh;
	nz_list list1;

	errh = nz_list_init(&list1);
	if(errh == 0){
		printf("It's ok!\n");
	}else{
		printf("It's broken!\n");
	}

	return 0;
}