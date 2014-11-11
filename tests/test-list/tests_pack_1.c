#include "tests_pack_1.h"

s32 show_list_s32(nz_list *list)
{
	s32 retval;
	u32 i;
	nz_node *it;
	printf("nz_list[%p]{size = %u}:\n",(void*)list, list->size);
	for(i = 0, it = list->begin;
		i < list->size && it != NULL && it != list->end;
		++i){
		printf("[%u][%d]\n",i,*((s32*)it->data));
	}

	return retval;
}

s32 listverify_s32(nz_list *list, s32 *arr[], u32 size)
{
	u32 i;
	nz_node *it;

	i = 0;
	NZ_ASSERT( list != NULL, "[LISTCMPS32] Incoming ptrs");

	for(i = 0, it = list->begin;
		i < size && it != NULL && it->data != NULL && it != list->end;
		it = it->next, ++i){

		if((*((s32*)it->data)) !=(*arr[i]) ) {
			return NZ_EINVALID;
		}
	}

	return NZ_ESUCCESS;
}

s32 test_1(nz_list *list)
{
	s32 errh;
	NZ_ASSERT(list!= NULL, "Incoming list valid");
	errh = nz_list_init(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List init");
	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List exit");

	return NZ_ESUCCESS;
}

s32 test_2(nz_list *list)
{
	s32 errh,i;
	const s32 size = 10;
	s32 data[size] = {0,1,2,3,4,5,6,7,8,9};

	NZ_ASSERT(list != NULL, "Icomming data");

	nz_list_init(list);

	show_list_s32(list);

	for(i = 0; i < 10; ++i){
		NZ_LOG("i = %d;",i);
		nz_list_push_back(list, &(data[i]));
	}
	show_list_s32(list);

	nz_list_exit(list);

	return NZ_ESUCCESS;
}