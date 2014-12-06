#include "tests_pack_1.h"

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

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

/******************************************************************************/

s32 test_2(nz_list *list)
{
#define sz6_2_1 10
	s32 errh,i;
	s32 data[sz6_2_1] = {10,11,12,13,14,15,16,17,18,19};

	NZ_ASSERT(list != NULL, "T2: Icomming data");

	nz_list_init(list);

	show_list_s32(list);

	for(i = 0; i < sz6_2_1; ++i){
		NZ_LOG("i = %d;",i);
		nz_list_push_back(list, &(data[i]));
	}
	show_list_s32(list);

	errh = listverify_s32(list, data, sz6_2_1);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_verify 1");

	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_1");
	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_2");
	errh = nz_list_pop_back(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "pop_back_3");


	errh = listverify_s32(list, data, sz6_2_1-3);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_verify 2");

	show_list_s32(list);

	errh = nz_list_exit(list);
	NZ_ASSERT(errh == NZ_ESUCCESS, "list_exit");

	return NZ_ESUCCESS;
}

/******************************************************************************/

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


/******************************************************************************/

static void destructor_free_s32(void *data)
{
	if(data == NULL){
		printf("TEST DESTRUCTOR ERROR: Invalid data!");
		return ; //(void*)(-NZ_ENULLPTR);
	}else{
		nz_free(data);
	}
}

/******************************************************************************/

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

/******************************************************************************/

s32 test_5(nz_list *list)
{
#define t5sz 10
#define stg1sz 4
#define stg2sz 7
#define stg3sz 10

	s32 errh;
	s32 data[t5sz]   = {501,502,503,504,505,506,507,508,509,510};
	s32 stg1[stg1sz] = {502,503,504,501};
	s32 stg2[stg2sz] = {501,502,503,504,505,506,507};
	s32 stg3[stg3sz] = {501,502,503,504,508,509,510,505,506,507};
	nz_list spll; //Splicing buffer list
	nz_error err1;

	errh = nz_error_init(&err1);
	NZ_ASRT_DUMB("T5: Error struct init");

	NZ_ASSERT(list != NULL, "T5: Incomming data");

	errh = nz_list_init(list);
	NZ_ASRT_DUMB("list init incomming");

	errh = nz_list_init(&spll);
	NZ_ASRT_DUMB("list init local");

	errh = __nz_list_vrf(list,&err1);
	NZ_WARN_DUMB("T5: inited list deep check");
	nz_error_assert(&err1);

	errh = __nz_list_vrf(&spll,&err1);
	NZ_WARN_DUMB("T5: new list deep check");
	nz_error_assert(&err1);

	// Primer to dest
	errh = nz_list_push_back(list, &(data[0]));
	NZ_ASRT_DUMB("d[0]->dst");
	NZ_ASRTCND(list->size == 1);
	NZ_ASRTCND(list->begin == list->rbegin);
	NZ_ASRTCND(list->begin != list->end);
	NZ_ASRTCND(list->rbegin != list->rend);

	// Portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[1]));
	NZ_ASRT_DUMB("d[1]->src");
	NZ_ASRTCND(spll.size == 1);
	NZ_ASRTCND(spll.begin == spll.rbegin);
	NZ_ASRTCND(spll.begin != spll.end);
	NZ_ASRTCND(spll.rbegin != spll.rend);

	errh = nz_list_push_back(&spll,&(data[2]));
	NZ_ASRT_DUMB("d[2]->src");
	errh = nz_list_push_back(&spll,&(data[3]));
	NZ_ASRT_DUMB("d[3]->src");

	// Test 5.1
	errh = nz_list_splice(list,list->begin,&spll);
	NZ_ASRT_DUMB("simple splicing to begin of dest list");
	errh = __nz_list_vrf(list,&err1);
	NZ_WARN_DUMB("T5: verification 1.1");
	nz_error_assert(&err1);
	errh = listverify_s32(list,stg1,stg1sz);
	NZ_ASRT_DUMB("T5: verification 1.2");
	NZ_ASRTCND(list->size == stg1sz);

	// Another portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[4]));
	NZ_ASRT_DUMB("d[4]->src");
	errh = nz_list_push_back(&spll,&(data[5]));
	NZ_ASRT_DUMB("d[5]->src");
	errh = nz_list_push_back(&spll,&(data[6]));
	NZ_ASRT_DUMB("d[6]->src");

	// Test 5.2
	errh = nz_list_splice(list,list->end,&spll);
	NZ_ASRT_DUMB("simple splicing to end of dest list");
	errh = __nz_list_vrf(list,&err1);
	NZ_WARN_DUMB("T5: verification 2.1");
	nz_error_assert(&err1);
	errh = listverify_s32(list,stg2,stg2sz);
	NZ_ASRT_DUMB("T5: verification 2.2");
	NZ_ASRTCND(list->size == stg2sz);

	// Another portion of data to splicing-buffer list
	errh = nz_list_push_back(&spll,&(data[7]));
	NZ_ASRT_DUMB("d[7]->dst");
	errh = nz_list_push_back(&spll,&(data[8]));
	NZ_ASRT_DUMB("d[8]->dst");
	errh = nz_list_push_back(&spll,&(data[9]));
	NZ_ASRT_DUMB("d[9]->dst");

	// Test 5.3
	errh = nz_list_splice(list,list->begin->next->next->next,&spll);
	NZ_ASRT_DUMB("simple splicing to middle of dest list");
	errh = listverify_s32(list,stg3,stg3sz);
	NZ_ASRT_DUMB("T5: verification 3");

	errh = nz_list_exit(list);
	NZ_ASRT_DUMB("list exit incomming");
	errh = nz_list_exit(&spll);
	NZ_ASRT_DUMB("list exit local");

	return errh;
}

/******************************************************************************/

s32 test_6(nz_list *list)
{
#define sz6_1 3
#define sz6_2 1
#define sz6_3 4
	s32 errh;
	s32 d1[sz6_1] = {60,61,62};
	s32 d2[sz6_2] = {60};

	NZ_ASSERT(list != NULL, "T6: Incomming data");

	nz_list_init(list);
	nz_list_push_back(list, &(d1[0]));
	nz_list_push_back(list, &(d1[1]));

	nz_list_push_back(list, &(d1[2]));

	errh = listverify_s32(list, d1, sz6_1);
	NZ_ASRT_DUMB("T6: Verification of ininitial state");

	errh = nz_list_resize(list, (u32)sz6_2, NULL);
	NZ_ASRT_DUMB("T6: resizing size to smaller");

	errh = nz_list_resize(list, (u32)sz6_2, NULL);
	NZ_ASRT_DUMB("T6: resizing size to same");

	errh = listverify_s32(list, d2, sz6_2);
	NZ_ASRT_DUMB("T6: Verification of srinked list");

	errh = nz_list_resize(list, (u32)sz6_3, NULL);
	NZ_ASRT_DUMB("T6: resizing list to biger");

	NZ_LOG("T6: Verification of increased list");
	NZ_ASRTCND(list->size == sz6_3);
	NZ_ASRTCND(list->begin->data == &(d1[0]));
	NZ_ASRTCND(list->begin->next->data == NULL);
	NZ_ASRTCND(list->begin->next->next->data == NULL);
	NZ_ASRTCND(list->begin->next->next->next->data == NULL);
	NZ_ASRTCND(list->begin->next->next->next == list->rbegin);

	errh = nz_list_resize(list, 0, NULL);
	NZ_ASRT_DUMB("T6: resizing list to zero");
	
	NZ_LOG("T6: Verification of list resized to zero");
	NZ_ASRTCND(list->size == 0);
	NZ_ASRTCND(list->begin == list->end);
	NZ_ASRTCND(list->rbegin == list->rend);

	errh = nz_list_exit(list);
	NZ_ASRT_DUMB("T6: incomming exit");

	return errh;
}

/******************************************************************************/
