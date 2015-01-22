#ifndef TESTS_PACK_1_H
#define TESTS_PACK_1_H

#include "nz_common.h"
#include "nz_list.h"

s32 show_list_s32(nz_list* list);

s32 listcmp_s32(nz_list *a, nz_list *b);

s32 test_nz_list_init(nz_list *list);

s32 test_nz_list_exit(nz_list *list);

s32 test_nz_list_pop_back(nz_list *list);

s32 test_nz_list_pop_front(nz_list *list);

// nz_list_remove_my_iter test
s32 test_3(nz_list *list);

// nz_list_set_node_destructor test
s32 test_4(nz_list *list);

// nz_list_splice test
s32 test_5(nz_list *list);

// nz_list_resize test
s32 test_6(nz_list *list);

#endif //  TESTS_PACK_1_H
