#ifndef NZ_LIST_H
#define NZ_LIST_H

#include "nz_int.h"
#include "nz_error.h"
#include "nz_memory.h"
#include <stdio.h>

typedef struct nz_list nz_list;
typedef struct nz_node nz_node;

/*!
	\brief NAZG List node type
*/
struct nz_node{
	nz_node	*next;
	nz_node	*prev;
	void	*data;
};

/*!
	\brief NAZG List root structure
*/
struct nz_list{
	nz_node			*begin;
	nz_node			*rbegin;
	nz_node			*end;
	nz_node			*rend;
	nz_destructor_t	fn_node_destr;
	u32				size;
};

/*!	\fn s32 nz_list_init(nz_list *list)
	\brief Initialises structure nz_list
	\param list pointer to list to be inilialized
*/

s32 nz_list_init( nz_list *list );

/*!	\fn s32 nz_list_exit(nz_list *list)
	\brief creares and deinitializez list. Does not call free()!
	\param list pointer to list to be cleared
*/
s32 nz_list_exit( nz_list *list );

/*!	\fn s32 nz_list_pop_back(nz_list *list)
	\brief removes last data element from list if any
	\param list pointer to list to be popped
*/
s32 nz_list_pop_back( nz_list *list );

/*!	\fn s32 nz_list_pop_front(nz_list *list)
	\brief removes first data element from list if any
	\param list pointer to list to be popped
*/
s32 nz_list_pop_front( nz_list *list );

/*!	\fn s32 nz_list_push_back(nz_list *list, void *data)
	\brief pushes data pointer to data to the end of the list
	\param list pointer to list to be populated
	\param data pointer to data object
*/
s32 nz_list_push_back( nz_list *list, void *data );

/*!	\fn s32 nz_list_push_front(nz_list *list, void *data)
	\brief pushes data pointer to data to the begining of the list
	\param list pointer to list to be populated
	\param data pointer to data object
*/
s32 nz_list_push_front( nz_list *list, void *data );

/*!	\fn s32 nz_list_remove_by_iter(nz_list *list, nz_node *node)
	\brief removes node by pointer to node
	\param list pointer to list to be cleared
	\param node target for removing
*/
s32 nz_list_remove_by_iter( nz_list *list, nz_node *node );

/*!	\fn s32 nz_list_set_node_destructor( nz_list *list, nz_destructor_t destructor_fn );
	\brief sets node destructor to list
	\param list pointer to list to be configured
	\param destructor_fn data deallocation function
*/
s32 nz_list_set_node_destructor( nz_list *list, nz_destructor_t destructor_fn );

#endif // NZ_LIST_H
