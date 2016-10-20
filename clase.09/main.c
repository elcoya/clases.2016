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
}

int clone_client(client_t* dst, client_t* src) {
	product_t product;
	
	stack_t auxiliary;
	stack_create(&auxiliary, sizeof(product_t), clone_product, destroy_product);
	
	while(client_pop(src, &product) == RES_OK) {
		stack_push(&auxiliary, &product);
	}
	
	while(! stack_is_empty(&auxiliary)) {
		stack_pop(&auxiliary, &product);
		client_push(src, &product);
		client_push(dst, &product);
	}
	
	stack_destroy(&auxiliary);
	
	return RES_OK;
}

int main(int argc, char** argv) {
	product_t *product = product_create();
	product_set_code(product, "1.01");
	product_set_description(product, "test");
	
	printf("producto: {\n\tcode: \"%s\",\n\tdescription: \"%s\"\n}\n", product->code, product->description);
	
	client_t *client = client_create();
	if(!client) return EXIT_FAILURE;
	
	client_push(client, product);
	
	product_t *p = client->cart.top->data;
	printf("cliente->producto: {\n\tcode: \"%s\",\n\tdescription: \"%s\"\n}\n",  p->code, p->description);

	client_t *clone = client_create();
	clone_client(clone, client);
	
	p = clone->cart.top->data;
	printf("cliente->producto: {\n\tcode: \"%s\",\n\tdescription: \"%s\"\n}\n",  p->code, p->description);

	
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
























