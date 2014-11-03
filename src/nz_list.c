#include "nz_list.h"

/******************************************************************************/

s32 nz_list_init( nz_list *list ){
	nz_node *sentinel_first, *sentinel_last;
	s32 retval;

	retval = NZ_ESUCESS;

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

	retval = NZ_ESUCESS;
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
	/* TODO Insert destruction call here */
	nz_node *node;
	s32 retval;
	retval = NZ_ESUCESS;

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
