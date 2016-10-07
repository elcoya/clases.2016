#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "straight_list.h"

#ifndef RES_OUT_OF_MEM
	#define RES_OUT_OF_MEM -1
#endif

#ifndef RES_NOT_FOUND
	#define RES_NOT_FOUND -2
#endif

typedef struct sorted_list_struct sorted_list_t;

typedef int (*sorted_list_compare_t) (const void* left, const void* right);
typedef int (*sorted_list_copy_t) (void* dst, const void* src);
typedef void (*sorted_list_destroy_t) (void*);

sorted_list_t* sorted_list_create(sorted_list_compare_t, size_t, 
                                  sorted_list_copy_t, sorted_list_destroy_t);
void sorted_list_destroy(sorted_list_t*);

int sorted_list_save(sorted_list_t*, void*);
int sorted_list_update(sorted_list_t*, void*);
int sorted_list_delete(sorted_list_t*, void*);
int sorted_list_get(sorted_list_t*, void*);

#endif
