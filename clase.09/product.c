#include "product.h"

product_t* product_create() {
	return (product_t *) malloc(sizeof(product_t));
}

void product_destroy(product_t* this) {
	free(this);
}

int product_clone(product_t* dst, const product_t* src) {
	strcpy(dst->code, src->code);
	strcpy(dst->description, src->description);
	return RES_OK;
}

void product_set_code(product_t* this, const char* code) {
	strcpy(this->code, code);
}

void product_get_code(product_t* this, char* code) {
	strcpy(code, this->code);
}

void product_set_description(product_t* this, const char* description) {
	strcpy(this->description, description);
}

void product_get_description(product_t* this, char* description) {
	strcpy(description, this->description);
}
