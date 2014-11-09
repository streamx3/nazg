#include "nz_list.h"

/******************************************************************************/

#define __NZ_CHKNULLPTR_JMP(ptr,retv,jmp) \
	do{ \
		if( ptr == NULL ){ \
			retv == NZ_ENULLPTR; \
			goto jmp; \
		} \
	}while(0);

/******************************************************************************/

/* Will jump if condition is true */
#define __NZ_CHKCOND_JMP(cond,retv,jmp) \
	do{ \
		if( cond ){ \
			retv == NZ_ENULLPTR; \
			goto jmp; \
		} \
	}while(0);

/******************************************************************************/

#define __NZ_CALL_NODE_DESTRUCTOR(list,node) \
	do{ \
		if(list && node && list->fn_node_destr != NULL && node->data != NULL){ \
			list->fn_node_destr(node->data); \
			node->data = NULL; \
		} \
	}while(0);

/******************************************************************************/

s32 __nz_list_size_reset( nz_list *list ){
	s32 retval;
	u32 real_size;
	nz_node *node;

	retval = NZ_ENULLPTR;
	real_size = 0;
	if( list != NULL && list->begin != NULL && list->end != NULL ){
		for( node = list->begin; node != NULL && node != list->end;
			 node = node->next, ++real_size );
		list->size = real_size;
		retval = NZ_ESUCCESS;
	}

	return retval;
}

/******************************************************************************/
/*
 [ dst ]->[sent]<->[n1]<->[n2]<->[pd0]<->[pd1]<->...<->[sent]
			+                      ?       v             +

 [ src ]->[sent]<->[n1]<->[ps0]<->[ps1]<->...<->[ps2]<->[ps3]<->...<->[sent]
			+               ?       v             v       ?             +

LEGEND
 +  known by list
 ?  not given, not known
 v  given in input

DESCRIPTION
	This function is just like std::list.splice();
	You know, like move move chain [ps1]-...-[ps2] between [pd1->prev] and [pd1].
	It becomes [pd1->prev]-[ps1]-...-[ps2]-[pd1].
*/

s32 __nz_list_splice_internal( nz_list *dst, nz_list *src, nz_node *pd1,
								  nz_node *ps1, nz_node *ps2 ){

/**** Check if incoming source list pointers are usable. ****/
#define __NZ_LSI_PTRCHK(l,p1,p2) \
	do{ \
		if( p1 == p2 && ( p1 == l->end || p1 == l->rend ) ){ \
			retval = NZ_ENOTFOUND; \
			goto __nz_list_splice_internal_out; \
		} \
	}while(0);
/************************************************************/

	nz_node *pd0, *ps0, *ps3;
	s32 retval;

	retval = NZ_ESUCCESS;

	__NZ_LSI_PTRCHK( src, ps1, ps2 );

	/* fixing wrong incomming ps1 */
	if( ps1 == dst->rend )
		ps1 = ps1->next;

	pd0 = pd1->prev;
	ps0 = ps1->prev;
	ps0->next = ps1;

	if( ps2 == src->end )
		ps2 = ps2->prev;

	ps3 = ps2->next;

	if( ps1 == src->begin ){
		src->begin = ps3;
		src->rend->next = src->begin;
		src->begin->prev = src->rend;
	}

	/* This is main splicing action */
	pd0->next = ps1;
	ps1->prev = pd0;
	pd1->prev = ps2;
	ps2->next = pd1;
	ps0->next = ps3;
	ps3->prev = ps0;

	dst->begin = dst->rend->next;
	dst->begin->prev = dst->rend;

	if( dst->end->prev != dst->rbegin ){
		dst->rbegin = dst->end->prev;
		dst->rbegin->next = dst->end;
	}

	__nz_list_size_reset( dst ); /* TODO Should log here? */
	__nz_list_size_reset( src ); /* TODO And here? */

__nz_list_splice_internal_out:;
	return retval;
}

/******************************************************************************/

void __nz_node_push_to_empty_list( nz_list *list, nz_node *node ){
	node->next = list->end;
	node->prev = list->rend;

	list->rend->next = node;
	list->end->prev = node;

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
void __nz_node_bind_new_neigh( nz_node *a, nz_node *b, nz_node *c){
	a->next = b;
	b->prev = a;

	c->prev = b;
	b->next = c;
}

/******************************************************************************/

s32 nz_list_init( nz_list *list ){
	nz_node *sentinel_first, *sentinel_last;
	s32 retval;

	retval = NZ_ESUCCESS;

	__NZ_CHKNULLPTR_JMP( list, retval, nz_list_init_out );
	sentinel_first = nz_malloc( sizeof(nz_node) );
	__NZ_CHKNULLPTR_JMP( sentinel_first, retval, nz_list_init_out );
	sentinel_last = nz_malloc( sizeof(nz_node) );
	__NZ_CHKNULLPTR_JMP( sentinel_last, retval, nz_list_init_free_sentfrst );

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

s32 nz_list_exit( nz_list *list ){
	s32 retval;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP( list, retval, nz_list_exit_out );

	for( ; list->begin != NULL && list->begin != list->end;
		 nz_list_pop_front( list ) );

	if( list->begin  != NULL && list->begin  == list->end &&
		list->rbegin != NULL && list->rbegin == list->rend &&
		list->begin->data == NULL){
		nz_free( list->begin );
		nz_free( list->rbegin );
		list->rbegin = list->rend = list->begin = list->end = NULL;
	}else{
		retval = NZ_EINVALID;
	}

nz_list_exit_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_pop_back( nz_list *list ){
	nz_node *node;
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP( list == NULL || list->end == NULL, \
					  retval, nz_list_pop_back_out );

	if( list->begin != list->end && list->size ){
		/* Get target */
		node = list->end;
		/* Rebuild tail */
		list->end = list->end->prev;
		list->end->next = list->rbegin;
		list->rbegin->prev = list->end;

		if( node == list->rend ){
			list->rend = list->rbegin;
		}
		__NZ_CALL_NODE_DESTRUCTOR(list, node);
		nz_free( node );
		--(list->size);
	}

nz_list_pop_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_pop_front( nz_list *list ){
	nz_node *node;
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP( list == NULL || list->begin == NULL, \
					  retval, nz_list_pop_front_out );

	if( list->begin != list->end && list->size > 0 ){
		/* Get target */
		node = list->begin;
		/* Rebuild tail */
		list->begin = list->begin->next;
		list->begin->prev = list->rend;
		list->rend->next = list->begin;

		if( node == list->rend ){
			list->rbegin = list->rend;
		}
		__NZ_CALL_NODE_DESTRUCTOR(list, node);
		nz_free( node );
		--(list->size);
	}

nz_list_pop_front_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_push_back( nz_list *list, void *data ){
	nz_node *node;
	s32 retval, errh;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP( list, retval, nz_list_push_back_out );
	node = nz_malloc( sizeof(nz_node) );
	__NZ_CHKNULLPTR_JMP( node, retval, nz_list_push_back_out );
	node->data = data;

	errh = nz_list_empty( list );
	if( errh < 0 ){
		retval = ((-1)*errh);
		goto nz_list_push_back_out;
	}
	/* Since here list is valid and empty or ont empty */
	if( errh ){
		/* List is empty */
		__nz_node_push_to_empty_list( list, node );
	}else{
		/* List is not empty */
		__nz_node_bind_new_neigh( list->rbegin, node,list->end );
		list->rbegin = node;
	}

nz_list_push_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_push_front( nz_list *list, void *data ){
	nz_node *node;
	s32 retval, errh;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP( list, retval, nz_list_push_back_out );
	node = nz_malloc( sizeof(nz_node) );
	__NZ_CHKNULLPTR_JMP( node, retval, nz_list_push_back_out );
	node->data = data;

	errh = nz_list_empty( list );
	if( errh < 0 ){
		retval = ((-1)*errh);
		goto nz_list_push_back_out;
	}
	/* Since here list is valid and empty or ont empty */
	if( errh ){
		/* List is empty */
		__nz_node_push_to_empty_list( list, node );
	}else{
		/* List is not empty */
		__nz_node_bind_new_neigh( list->rend, node, list->begin );
		list->begin = node;
	}

nz_list_push_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_remove_by_iter( nz_list *list, nz_node *aim ){
	s32 retval;
	nz_node *node;

	retval = NZ_ENOTFOUND;

	__NZ_CHKCOND_JMP( list == NULL || aim == NULL || list->begin == NULL, \
					  retval, nz_list_remove_by_iter_out );
	if( aim == list->end ){
		retval = NZ_EUNKNOWN;
		goto nz_list_remove_by_iter_out;
	}

	if( aim == list->begin )
		return nz_list_pop_front( list );
	
	if( aim == list->rbegin )
		return nz_list_pop_back( list );

	for( node = list->begin;
		 node->next != aim && node != list->end && node != NULL;
		 node = node->next );
	if( node == aim ){
		node->next = node->next->next;
		node->next->prev = node;
		__NZ_CALL_NODE_DESTRUCTOR( list, aim );
		--(list->size);
		retval = NZ_ESUCCESS;
	}

nz_list_remove_by_iter_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_set_node_destructor(nz_list *list, nz_destructor_t destructor){
	s32 retval;
	retval = NZ_ESUCCESS;

	__NZ_CHKCOND_JMP(list == NULL || destructor == NULL, retval, \
					 nz_list_set_node_destructor_out);

	list->fn_node_destr = destructor;

nz_list_set_node_destructor_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_empty(nz_list *list){
	if(list == NULL){
		return -NZ_ENULLPTR;
	}
	if(list->size == 0){
		if(list->begin == list->end && list->rend == list->rbegin &&
		   list->begin->prev == list->rbegin &&list->rend->next == list->end){
			return 1; // TRUE AND VALID
		}else{
			return -NZ_EINVALID;
		}
	}
	return 0; // FALSE
}

/******************************************************************************/

s32 nz_list_clear(nz_list *list){
	s32 retval;

	retval = NZ_ESUCCESS;
	__NZ_CHKNULLPTR_JMP(list, retval, nz_list_clear_out);

	for( ; list->begin != NULL && list->begin != list->end;
		 nz_list_pop_front(list));

nz_list_clear_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice(nz_list *dst, nz_node *pos, nz_list *src)
{
	s32 retval;
	__NZ_CHKCOND_JMP(dst != NULL && pos != NULL && src != NULL,
					 retval, nz_list_splice_out);
	retval = __nz_list_splice_internal(dst, src, pos, src->begin, src->rbegin);
nz_list_splice_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice_pos(nz_list *dst, nz_node *pos, nz_list *src, nz_node *src_pos)
{
	s32 retval;
	__NZ_CHKCOND_JMP(dst != NULL && pos != NULL && src != NULL && src_pos != NULL,
					 retval, nz_list_splice_pos_out);
	retval = __nz_list_splice_internal(dst, src, pos, src_pos, src_pos);
nz_list_splice_pos_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_splice_range(nz_list *dst, nz_node *pos, nz_list *src, nz_node *first, nz_node *last)
{
	s32 retval;
	__NZ_CHKCOND_JMP(dst != NULL && pos != NULL && src != NULL &&
					 first != NULL && last != NULL,
					 retval, nz_list_splice_range_out);
	retval = __nz_list_splice_internal(dst, src, pos, first, last);
nz_list_splice_range_out:;
	return retval;
}
