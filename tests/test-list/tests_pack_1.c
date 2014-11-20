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
	NZ_ASSERT(list!= NULL, "T1: Incoming list valid");
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

	NZ_ASSERT(list != NULL, "T2: Icomming data");

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

	NZ_ASSERT(list != NULL, "T3: Incomming data");
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


static void destructor_free_s32(void *data)
{
	if(data == NULL){
		printf("TEST DESTRUCTOR ERROR: Invalid data!");
		return ; //(void*)(-NZ_ENULLPTR);
	}else{
		nz_free(data);
	}
}

s32 test_4(nz_list *list)
{
#define t4_size 2
	s32 errh, *p_var, i;
	s32 data[t4_size] = {41,42};

	NZ_ASSERT(list != NULL, "T4: Incoming data");

	errh = nz_list_init(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List init");

	for(i = 0; i < t4_size; ++i){
		p_var = nz_malloc(sizeof(s32));
		NZ_ASSERT(p_var != NULL, "malloc #%d;", i);
		*p_var = data[i];
		errh = nz_list_push_back(list,p_var);
		NZ_ASSERT(errh == NZ_ESUCCESS, "push_back #%d;", i);
	}

	nz_list_set_node_destructor(list, destructor_free_s32);

	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "List exit");

	return NZ_ESUCCESS;
}

s32 test_5(nz_list *list)
{
#define t5sz 10
#define stg1sz 4
#define stg2sz 7
#define stg3sz 10

	s32 errh;
	s32 data[t5sz] = {501,502,503,504,505,506,507,508,509,510};
	s32 stg1[stg1sz] = {501,502,503,504};
	s32 stg2[stg2sz] = {501,502,503,504,505,506,507};
	s32 stg3[stg3sz] = {501,502,503,504,508,509,510,505,506,507};
	nz_list spll; //Splicing buffer list

	NZ_ASSERT(list != NULL, "T5: Incomming data");

	errh = nz_list_init(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list init incomming");
	errh = nz_list_init(&spll);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list init local");

	// Primer to dest
	errh = nz_list_push_back(list, &(data[0]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[0]->dst");

	// Portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[1]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[1]->dst");
	errh = nz_list_push_back(&spll,&(data[2]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[2]->dst");
	errh = nz_list_push_back(&spll,&(data[3]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[3]->dst");

	// Test 5.1
	errh = nz_list_splice(list,list->begin,&spll);
	NZ_ASSERT(errh == NZ_ESUCCESS, "simple splicing to begin of dest list");
	errh = listverify_s32(list,stg1,stg1sz);
	NZ_ASSERT(errh == NZ_ESUCCESS, "T5: verification 1");

	// Another portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[4]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[4]->dst");
	errh = nz_list_push_back(&spll,&(data[5]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[5]->dst");
	errh = nz_list_push_back(&spll,&(data[6]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[6]->dst");

	// Test 5.2
	errh = nz_list_splice(list,list->end,&spll);
	NZ_ASSERT(errh == NZ_ESUCCESS, "simple splicing to end of dest list");
	errh = listverify_s32(list,stg1,stg1sz);
	NZ_ASSERT(errh == NZ_ESUCCESS, "T5: verification 2");

	// Another portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[7]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[7]->dst");
	errh = nz_list_push_back(&spll,&(data[8]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[8]->dst");
	errh = nz_list_push_back(&spll,&(data[9]));
	NZ_ASSERT(errh == NZ_ESUCCESS, "d[9]->dst");

	// Test 5.3
	errh = nz_list_splice(list,list->begin->next->next->next,&spll);
	NZ_ASSERT(errh == NZ_ESUCCESS, "simple splicing to middle of dest list");
	errh = listverify_s32(list,stg1,stg1sz);
	NZ_ASSERT(errh == NZ_ESUCCESS, "T5: verification 3");

	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list exit incomming");
	errh = nz_list_exit(&spll);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list exit local");

	return errh;
}
