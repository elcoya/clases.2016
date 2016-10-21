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

int main(int argc, char** argv) {
	product_t product;
	product_create(&product);
	product_set_code(&product, "1.01");
	product_set_description(&product, "test");

	client_t *client = client_create();
	if(!client) {
		product_destroy(&product);
		return EXIT_FAILURE;
	}
	
	client_push(client, &product);
	
	client_t *clone = client_create();
	client_clone(clone, client);
	
	product_t actual;
	client_pop(clone, &actual);
	
	char code[PRODUCT_CODE_LEN];
	product_get_code(&actual, code);
	char description[PRODUCT_DESC_LEN];
	product_get_description(&actual, description);
	
	printf("producto: {\n\tcode: \"%s\",\n\tdescription: \"%s\"\n}\n", code, description);

	client_destroy(clone);
	client_destroy(client);
	product_destroy(&product);
		
	return EXIT_SUCCESS;
}
























