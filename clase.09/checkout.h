#ifndef __CHECKOUT_H__
#define __CHECKOUT_H__

#include "queue.h"
#include "straight_list.h"

#include "product.h"
#include "client.h"
/*#include "ticket.h"*/

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

typedef struct {
	queue_t queue;
	straight_list_t tickets;
} checkout_t;

int checkout_create();
void checkout_destroy(checkout_t*);

int checkout_push(checkout_t*, client_t*);
int checkout_serve(checkout_t*);

#endif
