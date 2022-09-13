#include <stdio.h>
#include "nz_list.h"

#include "tests_nz_error.h"
#include "tests_nz_list.h"

int main (int argc, char* argv[]) {
    s32 errh;
    nz_list list1;

    errh = test_nz_error_write();

    errh = test_nz_list_init(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_init");
    errh = test_nz_list_exit(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_exit");
    errh = test_nz_list_pop_back(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_pop_back");
    errh = test_nz_list_pop_front(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_pop_front");

    errh = test_nz_list_remove_by_iter(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_remove_by_iter");
    errh = test_nz_list_set_node_destructor(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_set_node_destructor");
    errh = test_nz_list_splice(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_splice");
    errh = test_nz_list_resize(&list1);
    NZ_ASSERT(errh == NZ_ESUCCESS, "test_nz_list_resize");

    return 0;
}
