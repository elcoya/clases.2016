#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string.h>
#include <stdlib.h>

#ifndef RES_OK
	#define RES_OK 0
#endif

#define PRODUCT_CODE_LEN 64
#define PRODUCT_DESC_LEN 256

typedef struct product {
	char code[PRODUCT_CODE_LEN];
	char description[PRODUCT_DESC_LEN];
} product_t;

int product_create(product_t*);
void product_destroy(product_t*);
int product_clone(product_t*, const product_t*);

void product_set_code(product_t*, const char*);
void product_get_code(product_t*, char*);

void product_set_description(product_t*, const char*);
void product_get_description(product_t*, char*);

#endif
