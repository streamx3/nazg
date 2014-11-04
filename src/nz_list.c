#include "nz_list.h"

/******************************************************************************/

s32 nz_list_init( nz_list *list ){
	nz_node *sentinel_first, *sentinel_last;
	s32 retval;

	retval = NZ_ESUCCESS;

	if( list == NULL ){
		retval = NZ_ENULLPTR;
		goto nz_list_init_out;
	}

	sentinel_first = nz_malloc( sizeof(nz_node) );
	if( sentinel_first == NULL ){
		retval = NZ_ENOMEM;
		goto nz_list_init_out;
	}
	sentinel_last = nz_malloc( sizeof(nz_node) );
	if( sentinel_last == NULL ){
		odbus_free( sentinel_first );
		retval = NZ_ENOMEM;
		goto nz_list_init_out;
	}

	list->node_destructor = NULL;
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
}

/******************************************************************************/

s32 nz_list_exit( nz_list *list ){
	s32 retval;

	retval = NZ_ESUCCESS;
	if( list == NULL ){
		retval = NZ_ENULLPTR;
		goto nz_list_exit_out;
	}
	for( ; list->begin != NULL && list->begin != list->end;
		 nz_list_pop_front( list ) );

	if( list->begin  != NULL && list->begin  == list->end &&
		list->rbegin != NULL && list->rbegin == list->rend &&
		ist->begin->data == NULL){
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

	if( list == NULL || list->end ){
		retval = NZ_ENULLPTR;
		goto nz_list_pop_back_out;
	}

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
		if(list->fn_node_destr != NULL && node->data != NULL ){
			list->fn_node_destr( node->data );
			node->data = NULL;
		}
		nz_free( node );
		--(list->size);
	}

nz_list_pop_back_out:;
	return retval;
}

/******************************************************************************/

s32 nz_list_pop_front( nz_list *list ){

}

/******************************************************************************/

s32 nz_list_push_back( nz_list *list, void *data ){

}

/******************************************************************************/

s32 nz_list_push_front( nz_list *list, void *data ){

}

/******************************************************************************/

s32 nz_list_remove_by_iter( nz_list *list, nz_node *node ){

}

/******************************************************************************/

s32 nz_list_set_node_destructor( nz_list *list, nz_destructor_t destructor_fn ){
	int retval;
	errh = NZ_ESUCCESS;

	if( list == NULL || destruction == NULL ){
		retval = NZ_ENULLPTR;
		goto nz_list_set_node_destructor_out;
	}
	list->fn_node_destr = destructor_fn;

nz_list_set_node_destructor_out:;
	return retval;
}
