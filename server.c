#include "server.h"

int8_t serveridentification(struct client * local)
{
	printf("[server][INFO] Server Identification\n");
	void* discard=malloc(130); /*Discard 130 bytes from the packet*/
	assert(read(local->server_socket,discard,130)==130);
	free(discard);

	printf("[proxy][INFO] Login Success\n");
	int8_t temp;
	temp=55; /*Size of Login Success packet*/
	assert(write(local->socket,&temp,1)==1);
	temp=0x02; /*Login Success Packet ID*/
	assert(write(local->socket,&temp,1)==1);
	temp=36; /*Size of UUID field*/	
	assert(write(local->socket,&temp,1)==1);
	writeString(local->socket, "00000000-0000-0000-0000-000000000000"); /*Invalid UUID*/
	temp=strlen(local->username); /*Size of username field*/	
	assert(write(local->socket,&temp,1)==1);	
	writeString(local->socket, local->username); /*Username*/
	local->state=3; /*Set state to play*/
	return 0;
}
int8_t levelinitialise(struct client * local)
{
	printf("[server][INFO] Level Initialise\n");
	return 0;
}
int8_t initialise_server_functions()
{
	serverfunction[0x00]=serveridentification;
	serverfunction[0x02]=levelinitialise;
}
