#include "tests_pack_1.h"

s32 show_list_s32(nz_list *list)
{
	s32 retval;
	u32 i;
	nz_node *it;
	printf("nz_list[%p]{size = %u}:\n",(void*)list, list->size);
	for(i = 0, it = list->begin;
		i < list->size && it != NULL && it != list->end;
		++i, it = it->next){
		printf("[%u][%d]\n",i,*((s32*)it->data));
	}

	return retval;
}

s32 listverify_s32(nz_list *list, s32 *arr, u32 size)
{
	u32 i;
	nz_node *it;

	i = 0;
	NZ_ASSERT(list != NULL, "[LISTCMPS32] Incoming ptrs");

	for(i = 0, it = list->begin;
		i < size && it != NULL && it->data != NULL && it != list->end;
		it = it->next, ++i){

		if((*((s32*)it->data)) !=(arr[i])){
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
#define size 10
	s32 data[size] = {10,11,12,13,14,15,16,17,18,19};

	NZ_ASSERT(list != NULL, "Icomming data");

	nz_list_init(list);

	show_list_s32(list);

	for(i = 0; i < 10; ++i){
		NZ_LOG("i = %d;",i);
		nz_list_push_back(list, &(data[i]));
	}
	show_list_s32(list);

	errh = listverify_s32(list, data, size);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_verify 1");

	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_1");
	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_2");
	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_3");


	errh = listverify_s32(list, data, size-3);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_verify 2");

	show_list_s32(list);

	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_exit");

	return NZ_ESUCCESS;
}

s32 test_3(nz_list *list)
{
#define t3_size 5
	s32 errh, i;
	nz_node *it1;

	NZ_ASSERT(list != NULL, "Incomming data");
	s32 data[t3_size] = {30,31,32,33,34};

	errh = nz_list_init(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list init");

	for(i = 0; i < t3_size; ++i){
		nz_list_push_back(list, &(data[i]));
	}

	errh = listverify_s32(list,data,t3_size);
	NZ_ASSERT(errh == NZ_ESUCCESS, "Verification 1: after push");

	it1 = list->begin->next->next;

	errh = nz_list_remove_by_iter(list, it1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "Removed middle by iterator");

	errh = nz_list_remove_by_iter(list, list->begin);
	NZ_ASSERT(errh == NZ_ESUCCESS, "Removed head by iterator");

	errh = nz_list_remove_by_iter(list, list->rbegin);
	NZ_ASSERT(errh == NZ_ESUCCESS, "Removed tail by iterator");

	errh = nz_list_exit(list);

	NZ_ASSERT(errh == NZ_ESUCCESS, "Exit");

	return NZ_ESUCCESS;
}

s32 test_4(nz_list *list)
{
#define t4_size 2
	s32 errh;
	s32 data[t4_size] = {41,42};

	NZ_ASSERT(list != NULL, "Incoming data");

	errh = nz_list_init(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List init");

//	nz_list_push_back(list, );

	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List exit");

	return NZ_ESUCCESS;
}
