#include "sorted_list.h"

struct sorted_list_struct {
	straight_list_t base;
	sorted_list_compare_t compare;
	
	size_t size;
	sorted_list_copy_t copy;
	sorted_list_destroy_t destroy;
};

sorted_list_t* sorted_list_create(sorted_list_compare_t cmp, size_t size, 
                              straight_list_copy_t cpy, straight_list_destroy_t destroy) {
								  
	sorted_list_t* new_list = (sorted_list_t*) malloc(sizeof(sorted_list_t));
	if(!new_list) return NULL;
	
	if(straight_list_create(& new_list->base, size, cpy, destroy) != RES_OK) {
		free(new_list);
		return NULL;
	}
	new_list->compare = cmp;
	
	new_list->size = size;
	new_list->copy = cpy;
	new_list->destroy = destroy;
	return new_list;
}


void sorted_list_destroy(sorted_list_t* list) {
	straight_list_destroy(&list->base);
	free(list);
}

int sorted_list_save(sorted_list_t* list, void* data) {
	straight_list_insert(&list->base, straight_list_first, data);
	return 0;
}
int sorted_list_update(sorted_list_t* list, void* data) {
	return 0;
}
int sorted_list_delete(sorted_list_t* list, void* data) {
	return 0;
}

int sorted_list_get(sorted_list_t* list, void* data) {
	void* tmp = malloc(list->size);
	if(!tmp) return RES_OUT_OF_MEM;

	straight_list_get(&list->base, tmp);
	if(list->compare(tmp, data) > 0) {
		straight_list_move(&list->base, straight_list_first);
		straight_list_get(&list->base, tmp);
	}
	
	while(list->compare(tmp, data) < 0 
	         && straight_list_move(&list->base, straight_list_next)) {
		straight_list_get(&list->base, tmp);
	}
	
	int res;
	if(!list->compare(tmp, data)) {
		straight_list_get(&list->base, data);
		res = RES_OK;
	} else {
		res = RES_NOT_FOUND;
	}
	free(tmp);
	return res;
}







