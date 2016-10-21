#include "client.h"

int client_clone_product(void* dst, const void* src) {
	product_t *p_src = (product_t*) src;
	product_t *p_dst = (product_t*) dst;
	return product_clone(p_dst, p_src);
}

void client_destroy_product(void* this) {
	product_destroy((product_t*) this);
}

int client_clone(client_t* dst, const client_t* src) {
	stack_clear(&(dst->cart));
	stack_clone(&(dst->cart), &(src->cart));
	return RES_OK;
}

/* PRIMITIVAS */
client_t* client_create() {
	client_t *client = (client_t*) malloc (sizeof(client_t));
	if(!client) return NULL;
	stack_create(&(client->cart), sizeof(product_t), client_clone_product, client_destroy_product);
	return client;
}

void client_destroy(client_t* this) {
	stack_destroy(&this->cart);
}

int client_push(client_t* this, product_t* product) {
	stack_t *cart = &(this->cart);
	return (stack_push(cart, product))? RES_OK : RES_ERROR;
}
int client_pop(client_t* this, product_t* product) {
	stack_t *cart = &(this->cart);
	if(stack_is_empty(cart)) {
		return RES_OUT_OF_PRODUCTS;
	}
	return (stack_pop(cart, product))? RES_OK : RES_ERROR;
}
