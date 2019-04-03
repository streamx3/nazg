#ifndef NZ_LIST_H
#define NZ_LIST_H

#include "nz_common.h"

typedef struct nz_list nz_list;
typedef struct nz_node nz_node;

/*!
    \brief NAZG List node type
*/
struct nz_node{
    nz_node *next;
    nz_node *prev;
    void    *data;
};

/*!
    \brief NAZG List root structure
*/
struct nz_list{
    nz_node         *begin;
    nz_node         *rbegin;
    nz_node         *end;
    nz_node         *rend;
    nz_destructor_t fn_node_destr;
    u32             size;
};

/*! \fn s32 nz_list_init(nz_list *list)
    \brief Initialises structure nz_list
    \param list pointer to list to be inilialized
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/

s32 nz_list_init(nz_list *list);

/*! \fn s32 nz_list_exit(nz_list *list)
    \brief creares and deinitializez list. Does not call free()!
    \param list pointer to list to be cleared
    \return NZ_ESUCCESS on success, NZ_EINVALID on internal logic error
*/
s32 nz_list_exit(nz_list *list);

/*! \fn s32 nz_list_pop_back(nz_list *list)
    \brief removes last data element from list if any
    \param list pointer to list to be popped
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/
s32 nz_list_pop_back(nz_list *list);

/*! \fn s32 nz_list_pop_front(nz_list *list)
    \brief removes first data element from list if any
    \param list pointer to list to be popped
*/
s32 nz_list_pop_front(nz_list *list);

/*! \fn s32 nz_list_push_back(nz_list *list, void *data)
    \brief pushes data pointer to data to the end of the list
    \param list pointer to list to be populated
    \param data pointer to data object
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/
s32 nz_list_push_back(nz_list *list, void *data);

/*! \fn s32 nz_list_push_front(nz_list *list, void *data)
    \brief pushes data pointer to data to the begining of the list
    \param list pointer to list to be populated
    \param data pointer to data object
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/
s32 nz_list_push_front(nz_list *list, void *data);

/*! \fn s32 nz_list_remove_by_iter(nz_list *list, nz_node *node)
    \brief removes node by pointer to node
    \param list pointer to list to be cleared
    \param node target for removing
    \return NZ_ESUCCESS on success, NZ_ENOTFOUND if aim is out of list
*/
s32 nz_list_remove_by_iter(nz_list *list, nz_node *node);

/*! \fn s32 nz_list_set_node_destructor(nz_list *list, nz_destructor_t destructor_fn)
    \brief sets node destructor to list
    \param list pointer to list to be configured
    \param destructor_fn data deallocation function
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/
s32 nz_list_set_node_destructor(nz_list *list, nz_destructor_t destructor);

/*! \fn s32 nz_list_empty(nz_list *list)
    \brief checks if list is empty and valid
    \param list pointer to list to be checked
    \return 0 if full, 1 if empty, -NZ_ENULLPTR on,
            -NZ_EINVALID if it's something wrong with it
*/
s32 nz_list_empty(nz_list *list);

/*! \fn s32 nz_list_clear(nz_list *list)
    \brief cleares list; calls node destructor if set;
    \param list pointer to list to be cleared
    \return NZ_ESUCCESS on sucess or NZ_ENULLPTR if list == NULL
*/
s32 nz_list_clear(nz_list *list);

/*! \fn s32 nz_list_splice(nz_list *dst, nz_node *pos, nz_list *src)
    \brief nz_list_splice Moves src-list to dst-list, into pos->next
    \param dst destination for splicing
    \param pos splicing position
    \param src list to be spliced out entirely
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on some NULL incomming,
            NZ_ENOTFOUND on NOT-NULL but invalid incomming data
*/
s32 nz_list_splice(nz_list *dst, nz_node *pos, nz_list *src);

/*! \fn s32 nz_list_splice_pos(nz_list *dst, nz_node *pos, nz_list *src, nz_node *i)
    \brief
    \param
    \param
    \param
    \return
*/
s32 nz_list_splice_pos(nz_list *dst, nz_node *pos, nz_list *src, nz_node *i);

/*! \fn s32 nz_list_splice_range(nz_list *dst, nz_node *pos, nz_list *src, nz_node *first, nz_node *last)
    \brief
    \param
    \param
    \param
    \return
*/
s32 nz_list_splice_range(nz_list *dst, nz_node *pos, nz_list *src, nz_node *first, nz_node *last);

/*! \fn s32 nz_list_resize(nz_list *list, u32 size, void* val)
    \brief resizes list to be as long as "size"
    \param list target list to resize
    \param size new size of list
    \param val default initializer; can be NULL
    \return NZ_ESUCCESS on success, NZ_ENULLPTR if wrong list given
*/
s32 nz_list_resize(nz_list *list, u32 size, void* val);

/*! \fn s32 nz_list_swap(nz_list *a, nz_list *b)
    \brief exchanges content of two lists
    \param a first list to swap
    \param b second list to swap
    \return NZ_ESUCCESS on success, NZ_ENULLPTR on wrong input
*/
s32 nz_list_swap(nz_list *a, nz_list *b);

/*! \fn s32 nz_list_reverse(nz_list *list)
    \brief reverses nodes order in list
    \param list is the list to reverse
    \return
*/
s32 nz_list_reverse(nz_list *list);

/*! \fn s32 __nz_list_vrf(nz_list *list, nz_error *err)
    \brief checks if list is valid inside
    \return NZ_ESUCCESS if valid, NZ_EINVAL if invalid,
        NZ_NULLPTR if wrong list given
 */

s32 __nz_list_vrf(nz_list *list, nz_error *err);

#endif // NZ_LIST_H
