#include "nz_list.h"

/******************************************************************************/

s32 __nz_list_vrfptrs(nz_list *list, nz_error *err)
{
	s32 retval;
	u32 count;
	nz_node *it;

	retval = NZ_ESUCCESS;
	if(list == NULL)
		return NZ_ENULLPTR;
	if(err != NULL && err->errcode != NZ_ESUCCESS){
		return err->errcode;
	}
	if(list->end->next != NULL || list->rend->prev != NULL){
		retval = NZ_EINVALID;
		nz_error_write(err, retval, "Dead-ends invalid [%p]<->[%p];",
					list->end->next, list->rend->prev);
		return retval;
	}
	if(list->end->data != NULL || list->rend->data != NULL){
		retval = NZ_EINVALID;
		nz_error_write(err, retval, "Sentinels invalid [%p]<->[%p];",
					list->end->data, list->rend->data);
		return retval;
	}

/* There are 3 major states based on size amount of data in list:
 * 1) empty list
 * 2) list with single item
 * 3) list with more than one item
 */

	if(list->size == 0){
		if(list->begin != list->end || list->rbegin != list->rend ||
			list->begin->prev != list->rbegin ||
			list->rbegin->next != list->begin){

			// Case 1
			retval = NZ_EINVALID;
			nz_error_write(
				err, retval, "Empty list ptrerr: begin[%p],end[%p],"
				"rbegin[%p],rend[%p],"
				"begin.next[%p],begin.prev[%p],end.next[%p],end.prev[%p];",
				list->begin, list->end, list->rbegin, list->rend,
				list->begin->next, list->begin->prev,
				list->end->next, list->end->prev);
		}
		return retval;
	}

	//Case 2 or 3
	if(list->begin == list->end || list->rbegin == list->rend){
		retval = NZ_EINVALID;
		nz_error_write(err, retval, "List with simgle data item invalid:"
			"begin[%p], end[%p], rbegin[%p], rend[%p];",
			list->begin, list->end, list->rbegin, list->rend);
		return retval;
	}

	if(list->size == 1 &&
	   (list->begin != list->rbegin ||
	   list->begin->next != list->end ||
	   list->begin != list->end->prev ||
	   list->rbegin->prev != list->rend ||
	   list->rbegin != list->rend->next)){

		//Case 2
		retval = NZ_EINVALID;
		nz_error_write(err, retval, "List with simgle data item invalid:"
			"begin[%p], end[%p], rbegin[%p], rend[%p],"
			"begin.next[%p], begin.prev[%p],"
			"end.prev[%p], end.next[%p],"
			"rend.prev[%p], rend.next[%p];",
			list->begin, list->end, list->rbegin, list->rend,
			list->begin->next, list->begin->prev,
			list->end->prev, list->end->next,
			list->rend->prev, list->rend->next);
		return retval;
	}

	if(list->size > 1){
		count = 0;
		it = list->begin;
		while(it != NULL && it != list->end){
			++count;
			it=it->next;
		}

#define __nz_rollchecks(direction_str) \
		do{ \
			if(count != list->size){ \
				retval = NZ_EINVALID; \
				nz_error_write(err,retval,direction_str "Size mismatch;"); \
				return retval; \
			} \
			if(it == NULL){ \
				retval = NZ_EINVALID; \
				nz_error_write(err,retval,direction_str "List unexpected termination;"); \
				return retval; \
			} \
		}while(0)

		__nz_rollchecks("[Direct]");

		count = 0;
		it = list->rbegin;
		while(it != NULL && it != list->rend){
			++count;
			it = it->prev;
		}

		__nz_rollchecks("[Reverse]");
	}

	return retval;
}

/******************************************************************************/

s32 __nz_list_vrf(nz_list *list, nz_error *err)
{
	s32 errh;
	errh = NZ_ESUCCESS;
	if(err != NULL && err->errcode != NZ_ESUCCESS){
		return err->errcode;
	}
	errh = __nz_list_vrfptrs(list,err);
	if(errh != NZ_ESUCCESS)
		return errh;

	return errh;
}

/******************************************************************************/

void __nz_ptrswap(void **a, void **b)
{
	void *c;
	c = *(a);
	*(a) = *(b);
	*(b) = c;
}

/******************************************************************************/

void __show_list_ptrs(nz_list *list)
{
	NZ_LOG("list = %p", list);
	NZ_LOG("list->begin = %p", list->begin);
	NZ_LOG("list->rbegin = %p", list->rbegin);
	NZ_LOG("list->end = %p", list->end);
	NZ_LOG("list->rend = %p", list->rend);
}

/******************************************************************************/

#define __NZ_CALL_NODE_DESTRUCTOR(list,node) \
	do{ \
		if(list && node && list->fn_node_destr != NULL && node->data != NULL){ \
			list->fn_node_destr(node->data); \
			node->data = NULL; \
		} \
	}while(0);

/******************************************************************************/

s32 __nz_list_size_reset(nz_list *list)
{
	s32 retval;
	u32 real_size;
	nz_node *node;

	retval = NZ_ENULLPTR;
	real_size = 0;
	if(list != NULL && list->begin != NULL && list->end != NULL){
		for(node = list->begin; node != NULL && node != list->end;
			node = node->next, ++real_size);
		list->size = real_size;
		retval = NZ_ESUCCESS;
	}

	return retval;
}

/******************************************************************************/
/*
[ dst ]->[sentinel]<->[n1]<->[n2]<->[pd0]<->[pd1]<->...<->[sentinel]
			+                         ?       v             +

[ src ]->[sentinel]<->[n1]<->[ps0]<->[ps1]<->...<->[ps2]<->[ps3]<->...<->[sentinel]
			+                  ?       v             v       ?             +

LEGEND
 +  known by list
 ?  not given, not known
 v  given in input

DESCRIPTION
	This function is just like std::list.splice();
	You know, like move move chain [ps1]-...-[ps2] between [pd1->prev] and [pd1]
	It becomes [pd1->prev]-[ps1]-...-[ps2]-[pd1].
*/

s32 __nz_list_splice_internal(nz_list *dst, nz_list *src, nz_node *pd1,
							  nz_node *ps1, nz_node *ps2)
{

/**** Check if incoming source list pointers are usable. ****/
#define __NZ_LSI_PTRCHK(l,p1,p2) \
	do{ \
		if(p1 == p2 && (p1 == l->end || p1 == l->rend)){ \
			retval = NZ_ENOTFOUND; \
			goto __nz_list_splice_internal_out; \
		} \
	}while(0);
/************************************************************/

	nz_node *pd0, *ps0, *ps3;
	s32 retval;

	retval = NZ_ESUCCESS;

	__NZ_LSI_PTRCHK(src, ps1, ps2);

	/* fixing wrong incomming ps1 */
	if(ps1 == dst->rend)
		ps1 = ps1->next;

	pd0 = pd1->prev;
	ps0 = ps1->prev;
	ps0->next = ps1;

	if(ps2 == src->end)
		ps2 = ps2->prev;

	ps3 = ps2->next;

	/* Rebinding source list to forget about ps1-...ps2 chunk */
	ps0->next = ps3;
	ps3->prev = ps0;

	if(ps0 == src->rend && ps3 == src->end){
		src->begin = ps3;
		src->rbegin = ps0;
	}else{
		if(ps0 == src->rend){
			src->begin = ps3;
		}
		if(ps3 == src->end){
			src->rbegin = ps0;
		}
	}

	/* This is main splicing action */
	pd0->next = ps1;
	ps1->prev = pd0;
	pd1->prev = ps2;
	ps2->next = pd1;

	dst->begin = dst->rend->next;
	dst->begin->prev = dst->rend;

	if(dst->end->prev != dst->rbegin){
		dst->rbegin = dst->end->prev;
		dst->rbegin->next = dst->end;
	}else{
		// TODO Add bugfix here!
	}

	__nz_list_size_reset(dst); /* TODO Should log here? */
	__nz_list_size_reset(src); /* TODO And here? */

__nz_list_splice_internal_out:;
	return retval;
}

/******************************************************************************/

void __nz_node_push_to_empty_list(nz_list *list, nz_node *node)
{
	node->next = list->end;
	node->prev = list->rend;

	list->rend->next = node;
	list->end->prev = node;

	__show_list_ptrs(list);
	list->begin = node;
	list->rbegin = node;
}

/******************************************************************************/

/*
	STATE BEFORE
	a <--> c

	STATE AFTER
	a <--> b <--> c
*/
void __nz_node_bind_new_neigh(nz_node *a, nz_node *b, nz_node *c)
{
	a->next = b;
	b->prev = a;

	c->prev = b;
	b->next = c;
}

/******************************************************************************/

s32 nz_list_init(nz_list *list)
{
	nz_node *sentinel_first, *sentinel_last;
	s32 retval;

	retval = NZ_ESUCCESS;

	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_init_out);
	sentinel_first = nz_malloc(sizeof(nz_node));
	__NZ_CHKNULLPTR_JMP(sentinel_first, retval, nz_list_init_out);
	sentinel_last = nz_malloc(sizeof(nz_node));
	__NZ_CHKNULLPTR_JMP(sentinel_last, retval, nz_list_init_free_sentfrst);

	list->fn_node_destr = NULL;
	list->size = 0;

	/*! Sentinels binding */
	list->end = list->begin = sentinel_last;
	list->rbegin = list->rend = sentinel_first;

	sentinel_first->data = NULL;
	sentinel_first->prev = NULL;
	sentinel_first->next = sentinel_last;

	sentinel_last->data = NULL;
	sentinel_last->next = NULL;
	sentinel_last->prev = sentinel_first;

nz_list_init_out:;
	return retval;

nz_list_init_free_sentfrst:;
	nz_free(sentinel_first);
	goto nz_list_init_out;
}

/******************************************************************************/

s32 nz_list_exit(nz_list *list)
{
	s32 retval;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_exit_out);

	retval = nz_list_clear(list);
	if(retval)
		return retval;

	if(list->begin  != NULL && list->begin  == list->end &&
	   list->rbegin != NULL && list->rbegin == list->rend &&
	   list->begin->data == NULL){
		nz_free(list->begin);
		nz_free(list->rbegin);
		list->rbegin = list->rend = list->begin = list->end = NULL;
	}else{
		retval = NZ_EINVALID;
	}

nz_list_exit_out:;
	return retval;
}

/******************************************************************************/

#define __NZ_LIST_REBIND_TO_EMPTY(list) \
do{ \
    list->begin         =  list->end;    \
    list->rbegin        =  list->rend;   \
    list->begin->prev   =  list->rbegin; \
    list->rbegin->next  =  list->begin;  \
}while(0);

/******************************************************************************/

s32 nz_list_pop_back(nz_list *list)
{
	nz_node *node;
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP(list == NULL || list->end == NULL, \
					 retval, nz_list_pop_back_out);

	if(list->begin == list->end || list->size == 0){
		retval = NZ_ENOTFOUND;
		goto nz_list_pop_back_out;
	}
	/* else */

	/* Get target node */
	node = list->rbegin;

    if(list->begin == list->rbegin){
        /* If list has only one node */
        __NZ_LIST_REBIND_TO_EMPTY(list);
    }else{
        /* Rebuild tail */
        list->rbegin = list->rbegin->prev;
        list->rbegin->next = list->end;
        list->end->prev = list->rbegin;
    }

	__NZ_CALL_NODE_DESTRUCTOR(list, node);
	nz_free(node);
	--(list->size);

nz_list_pop_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_pop_front(nz_list *list)
{
	//TODO Find and fix bug here
	nz_node *node;
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP(list == NULL || list->begin == NULL, \
					 retval, nz_list_pop_front_out);
					 \
	if(list->begin == list->end || list->size == 0){
		retval = NZ_ENOTFOUND;
		goto nz_list_pop_front_out;
	}
	/* else */

	/* Get target */
	node = list->begin;
	/* Rebuild tail */
	list->begin = list->begin->next;
	list->begin->prev = list->rend;
	list->rend->next = list->begin;

	/* If list has only one node */
	if(node == list->rbegin){
		list->rbegin = list->rend;
		list->begin = list->end;
	}
	__NZ_CALL_NODE_DESTRUCTOR(list, node);
	nz_free(node);
	--(list->size);

nz_list_pop_front_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_push_back(nz_list *list, void *data)
{
	nz_node *node;
	s32 retval, errh;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_push_back_out);
	node = nz_malloc(sizeof(nz_node));
	__NZ_CHKNULLPTR_JMP(node, retval, nz_list_push_back_out);
	node->data = data;

	errh = nz_list_empty(list);
	if(errh < 0){
		retval = ((-1)*errh);
		goto nz_list_push_back_out;
	}
	/* Since here list is valid and empty or not empty */
	if(errh){
		/* List is empty */
		__nz_node_push_to_empty_list(list, node);
	}else{
		/* List is not empty */
		__nz_node_bind_new_neigh(list->rbegin, node,list->end);
		list->rbegin = node;
	}
	++(list->size);

nz_list_push_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_push_front(nz_list *list, void *data)
{
	nz_node *node;
	s32 retval, errh;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_push_back_out);
	node = nz_malloc(sizeof(nz_node));
	__NZ_CHKNULLPTR_JMP(node, retval, nz_list_push_back_out);
	node->data = data;

	errh = nz_list_empty(list);
	if(errh < 0){
		retval = ((-1)*errh);
		goto nz_list_push_back_out;
	}
	/* Since here list is valid and empty or ont empty */
	if(errh){
		/* List is empty */
		__nz_node_push_to_empty_list(list, node);
	}else{
		/* List is not empty */
		__nz_node_bind_new_neigh(list->rend, node, list->begin);
		list->begin = node;
	}
	++(list->size);

nz_list_push_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_remove_by_iter(nz_list *list, nz_node *aim)
{
	s32 retval;
	nz_node *node;

	retval = NZ_ENOTFOUND;

	__NZ_CHKCOND_JMP(list == NULL || aim == NULL || list->begin == NULL, \
					 retval, nz_list_remove_by_iter_out);
	if(aim == list->end){
		retval = NZ_EUNKNOWN;
		goto nz_list_remove_by_iter_out;
	}

	if(aim == list->begin)
		return nz_list_pop_front(list);
	
	if(aim == list->rbegin)
		return nz_list_pop_back(list);

	for(node = list->begin;
		node != NULL && node->next != aim && node != list->end;
		node = node->next);
	if(node &&  node->next == aim){
		node->next = node->next->next;
		node->next->prev = node;
		__NZ_CALL_NODE_DESTRUCTOR(list, aim);
		--(list->size);
		retval = NZ_ESUCCESS;
	}

nz_list_remove_by_iter_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_set_node_destructor(nz_list *list, nz_destructor_t destructor)
{
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP(list == NULL || destructor == NULL, retval, \
					 nz_list_set_node_destructor_out);

	list->fn_node_destr = destructor;

nz_list_set_node_destructor_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_empty(nz_list *list)
{
	if(list == NULL){
		return -NZ_ENULLPTR;
	}
	if(list->size == 0){
		if(list->begin == list->end && list->rend == list->rbegin &&
		   list->begin->prev == list->rbegin &&
		   list->rend->next == list->end){
			return 1; // TRUE AND VALID
		}else{
			return -NZ_EINVALID;
		}
	}
	return 0; // FALSE
}

/******************************************************************************/

s32 nz_list_clear(nz_list *list)
{
	s32 retval;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_clear_out);

	for(; list->begin != NULL && list->begin != list->end;
		 nz_list_pop_front(list));

nz_list_clear_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice(nz_list *dst, nz_node *pos, nz_list *src)
{
	s32 retval;
	retval = NZ_ESUCCESS;
	__NZ_CHKCOND_JMP(dst == NULL || pos == NULL || src == NULL,
					 retval, nz_list_splice_out);
	retval = __nz_list_splice_internal(dst, src, pos, src->begin, src->rbegin);
nz_list_splice_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice_pos(nz_list *dst, nz_node *pos,
					   nz_list *src, nz_node *src_pos)
{
	s32 retval;
	retval = NZ_ESUCCESS;
	__NZ_CHKCOND_JMP(dst != NULL && pos != NULL && src != NULL \
					 && src_pos != NULL, retval, \
					 nz_list_splice_pos_out);
	retval = __nz_list_splice_internal(dst, src, pos, src_pos, src_pos);
nz_list_splice_pos_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice_range(nz_list *dst, nz_node *pos, nz_list *src,
						 nz_node *first, nz_node *last)
{
	s32 retval;
	retval = NZ_ESUCCESS;
	__NZ_CHKCOND_JMP(dst != NULL && pos != NULL && src != NULL &&
					 first != NULL && last != NULL,
					 retval, nz_list_splice_range_out);
	retval = __nz_list_splice_internal(dst, src, pos, first, last);
nz_list_splice_range_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_resize(nz_list *list, u32 size, void* val)
{
	s32 retval;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list,retval,nz_list_resize_out);
	__nz_list_size_reset(list);
	if(size == list->size){
		return retval;
	}
	while(retval == NZ_ESUCCESS && size < list->size){
		retval = nz_list_pop_back(list);
	}
	while(retval == NZ_ESUCCESS && size > list->size){
		retval = nz_list_push_back(list,val);
	}

nz_list_resize_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_swap(nz_list *a, nz_list *b)
{
	s32 retval;
	u32 tmpsz;

	retval = NZ_ESUCCESS;
	__NZ_CHKCOND_JMP(a == NULL || b == NULL, retval, nz_list_swap_out);

	// TODO implement internal validation and use it here

	__nz_ptrswap((void*)&(a->begin), (void*)&(b->begin));
	__nz_ptrswap((void*)&(a->rbegin),(void*)&(b->rbegin));
	__nz_ptrswap((void*)&(a->rend),  (void*)&(b->rend));
	__nz_ptrswap((void*)&(a->end),   (void*)&(b->end));

	tmpsz = a->size;
	a->size = b->size;
	b->size = tmpsz;

nz_list_swap_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_reverse(nz_list *list)
{
	s32 retval;
	nz_node *it;
	nz_list l2; // Buffer list

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_reverse_out);

	l2.begin = list->rbegin;
	l2.rbegin = list->begin;
	for(it = l2.begin; it != l2.rbegin; it = it->next){
		__nz_ptrswap((void*)&(it->next), (void*)&(it->prev));
	}
	// TODO Continue here

nz_list_reverse_out:;
	return retval;
}

/******************************************************************************/
