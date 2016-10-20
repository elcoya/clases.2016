#include <stdio.h>
#include <stdlib.h>

#include "sorted_list.h"

#ifndef RES_OK
	#define RES_OK 0
#endif

#ifndef RES_OUT_OF_MEM
	#define RES_OUT_OF_MEM -1
#endif

typedef struct  {
	int key;
	int value;
} data_t;

int copy_data(void* dst, const void* src) {
	data_t* destination = (data_t*) dst;
	data_t* source = (data_t*) src;
	
	destination->key = source->key;
	destination->value = source->value;
	
	return RES_OK;
}

void delete_data(void* target) {
	
}

int compare_data(const void* left, const void* right) {
	data_t* left_data = (data_t*) left;
	data_t* right_data = (data_t*) right;
	return left_data->key - right_data->key;
}


int main(int argc, char** argv) {
	sorted_list_t* list;
	
	list = sorted_list_create(compare_data, sizeof(data_t), copy_data, delete_data);
	
	/* prueba */
	data_t data1;
	data1.key = 1;
	data1.value = 1200;
	
	sorted_list_save(list, &data1);
	
	data_t data2;
	data2.key = 2;
	data2.value = 23423;
	
	sorted_list_save(list, &data2);

	data_t actual;
	actual.key = data1.key;
	actual.value = 0;
	
	sorted_list_get(list, &actual);
	
	if(data1.value == actual.value) {
		printf("Prueba exitosa\n");
	} else {
		printf("Prueba fallida\n");
	}
	
	sorted_list_destroy(list);
	
	return EXIT_SUCCESS;
}
























