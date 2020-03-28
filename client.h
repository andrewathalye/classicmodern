#include "data.h"
/*Create client function pointer table*/
int8_t (*clientfunction[256][256])(int32_t,struct client *); /*state id | int32_t size, struct client * local*/

int8_t initialise_client_functions();
