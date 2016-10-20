#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "stack.h"
#include "product.h"

#ifndef RES_OK
	#define RES_OK 0
#endif

#ifndef RES_OUT_OF_MEM
	#define RES_OUT_OF_MEM -1
#endif

#ifndef RES_OUT_OF_PRODUCTS
	#define RES_OUT_OF_PRODUCTS -2
#endif

#ifndef RES_ERROR
	#define RES_ERROR -3
#endif

typedef struct client {
	stack_t cart;
} client_t;

client_t* client_create();
void client_destroy(client_t*);
int client_clone(client_t*, const client_t*);

int client_push(client_t*, product_t*);
int client_pop(client_t*, product_t*);

#endif
