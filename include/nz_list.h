#ifndef NZ_LIST
#define NZ_LIST

#include "nz_int.h"
#include <stdio.h>

typedef struct nz_list nz_list;
typedef struct nz_node nz_node;

struct nz_node {
	nz_node	*next;
	nz_node	*prev;
	void	*data;
};

struct nz_list {
	nz_node	*begin;
	nz_node *rbegin;
	nz_node	*end;
	nz_node	*rend;
	u32		size;
};

s32 nz_list_init(nz_list *list);

#endif // NZ_LIST