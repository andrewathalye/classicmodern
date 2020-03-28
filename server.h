#include "data.h"
/*Create server function pointer table*/
int8_t (*serverfunction[256])(struct client *); /*id | struct client * local*/

int8_t initialise_server_functions();
