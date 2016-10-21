#include "stack.h"

void stack_create(stack_t *sp, size_t size, stack_copy_t copy, stack_destroy_t destroy)
{
	sp->top = NULL;
	sp->size = size;
	sp->copy = copy;
	sp->destroy = destroy;
}

void stack_destroy(stack_t* sp)
{
	stack_clear(sp);
}

void stack_clone(stack_t* dst, const stack_t* src) {
	dst->copy = src->copy;
	dst->destroy = src->destroy;
	dst->size = src->size;
	
	stack_node_t *src_i = src->top;
	if(!src_i) {
		dst->top = NULL;
		return;
	}

	stack_node_t *dst_i = (stack_node_t*) malloc(sizeof(stack_node_t));
	dst_i->data = malloc(dst->size);
	dst->copy(dst_i->data, src_i->data);
	dst->top = dst_i;
	src_i = src_i->next;
	
	while( src_i ) {
		
		dst_i->next = (stack_node_t*) malloc(sizeof(stack_node_t));
		dst_i = dst_i->next;
		
		dst_i->data = malloc(dst->size);
		dst->copy(dst_i->data, src_i->data);
		
		src_i = src_i->next;
	}
	dst_i->next = NULL;
	
}

void stack_clear(stack_t* sp)
{
	stack_node_t* next=sp->top;
	while (next)
	{
		next = sp->top->next;
		sp->destroy(sp->top->data);
		free(sp->top->data);
		free(sp->top);
		sp->top = next;
	}
	sp->top = NULL;
}

int stack_is_empty(const stack_t* sp)
{
	return (sp->top == NULL);
}

int stack_push(stack_t *sp, const void* data)
{
	int result = 0;
	stack_node_t *node = (stack_node_t*) malloc(sizeof(stack_node_t));
	if (!node) {
		return FALSE;
	}
	node->data = malloc (sp->size);
	if(!node->data)
	{
		free(node);
		return FALSE;
	}

	result = sp->copy(node->data, data);
	if(result != RES_OK) {
		free(node->data);
		free(node);
		return FALSE;
	}
	node->next = sp->top;
	sp->top = node;
	return TRUE;
}

int stack_pop(stack_t *sp, void* data)
{
	stack_node_t *aux = sp->top;
	if(aux == NULL || RES_OK != sp->copy(data, aux->data)) {
		return FALSE;
	}
	sp->top = sp->top->next;
	sp->destroy(aux->data);
	free(aux->data);
	free(aux);
	return TRUE;
}

