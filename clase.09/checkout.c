#include "checkout.h"

int checkout_serve(checkout_t* checkout) {
	client_t *client = client_create();
	
	queue_pop(&(checkout->queue), client);
	ticket_t ticket;
	serve_client(client, &ticket);
	insert_ticket(&(checkout->tickets), &ticket);
	
	return RES_OK;
}

int serve_client(client_t *client, ticket_t *ticket) {}

int insert_ticket(straight_list_t *tickets, ticket_t *ticket) {}

int buscar_en_lista(straight_list_t *list, 
	void* target, void* current, 
	int (*fcomp)(const void*, const void*),
	straight_list_movement_t *movement) {}
