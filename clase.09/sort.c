#include <stdio.h>
#include <stdlib.h>

#include "product.h"
#include "client.h"

#ifndef RES_OK
	#define RES_OK 0
#endif

#ifndef RES_OUT_OF_MEM
	#define RES_OUT_OF_MEM -1
#endif


int clone_product(void* dst, const void* src) {
	product_t *p_src = (product_t*) src;
	product_t *p_dst = (product_t*) dst;
	return product_clone(p_dst, p_src);
}

void destroy_product(void* target) {
	product_destroy((product_t*) target);
}

int clone_client(client_t* dst, client_t* src) {
	product_t product;
	
	stack_t *src_cart = &(src->cart);
	stack_t *dst_cart = &(dst->cart);	
	stack_t auxiliary;

	stack_destroy(&(dst->cart));

	stack_create(&auxiliary, sizeof(product_t), clone_product, destroy_product);
	
	while(! stack_is_empty(src_cart)) {
		stack_pop(src_cart, &product);
		stack_push(&auxiliary, &product);
	}
	
	while(! stack_is_empty(&auxiliary)) {
		stack_pop(&auxiliary, &product);
		stack_push(src_cart, &product);
		stack_push(dst_cart, &product);
	}
	
	return RES_OK;
}

int main(int argc, char** argv) {
	product_t *product = product_create();
	product_set_code(product, "1.01");
	product_set_description(product, "test");
	
	client_t *client = client_create();
	
	client_push(client, product);
	
	client_t *clone = client_create();
	clone_client(clone, client);
	
	product_t actual;
	client_pop(clone, &actual);
	
	char code[PRODUCT_CODE_LEN];
	product_get_code(product, code);
	char description[PRODUCT_DESC_LEN];
	product_get_description(product, description);
	
	printf("producto: {\n\tcode: \"%s\",\n\tdescription: \"%s\"\n}\n", code, description);
	
	client_destroy(client);
	product_destroy(product);
		
	return EXIT_SUCCESS;
}
























