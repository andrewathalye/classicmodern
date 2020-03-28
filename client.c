#include "data.h"
#include "client.h"
#include "proxy.h"

/*State 0*/
int8_t handshake(int32_t size, struct client * local)
{
	printf("[client][INFO] Handshake\n");
	
	/*Skip extraneous packet data*/
	void* discard=malloc(size-1);
	assert(read(local->socket,discard,size-1)==size-1);
	free(discard);

	/*Extract state from packet*/
	local->state=readVarInt(local->socket); /*Set state*/
	return 0;
}
/*State 1*/
int8_t status_request(int32_t size, struct client * local)
{
	printf("[client][INFO] Status Request\n");

	printf("[proxy][RETURN] Status Response\n");
	/*Prepare response packet*/
	int8_t* protocol=malloc(INT_AS_STRING_LENGTH);
	sprintf(protocol,"%i",MODERN_PROTOCOL);
	int8_t* maxplayers=malloc(INT_AS_STRING_LENGTH);
	sprintf(maxplayers,"%i",MAX_CLIENTS);
	int8_t* onlineplayers=malloc(INT_AS_STRING_LENGTH);
	sprintf(onlineplayers,"%i",get_players()-1); /*Subtract current client*/
	int32_t responselength=strlen(RESPONSE_1)+strlen(MODERN_VERSION)+strlen(RESPONSE_2)+strlen(protocol)+strlen(RESPONSE_3)+strlen(maxplayers)+strlen(RESPONSE_4)+strlen(onlineplayers)+strlen(RESPONSE_5)+strlen(MOTD)+strlen(RESPONSE_6);
	int32_t packetlength=1+varIntLength(responselength)+responselength;

	/*Send response packet*/
	writeVarInt(packetlength,local->socket);
	writeVarInt(0,local->socket); /*Packet ID*/
	writeVarInt(responselength,local->socket);
	writeString(local->socket,RESPONSE_1);
	writeString(local->socket,MODERN_VERSION);
	writeString(local->socket,RESPONSE_2);
	writeString(local->socket,protocol);
	writeString(local->socket,RESPONSE_3);
	writeString(local->socket,maxplayers);
	writeString(local->socket,RESPONSE_4);
	writeString(local->socket,onlineplayers);
	writeString(local->socket,RESPONSE_5);
	writeString(local->socket,MOTD);
	writeString(local->socket,RESPONSE_6);

	free(protocol);
	free(maxplayers);
	free(onlineplayers);
	return 0;
}
int8_t status_ping(int32_t size, struct client * local)
{
	printf("[client][INFO] Status Ping\n");
	int64_t payload=readLong(local->socket);

	printf("[proxy][RETURN] Status Pong\n");
	int8_t temp=9; /*Packet Size*/
	assert(write(local->socket,&temp,1)==1);
	temp=1; /*Packet ID*/
	assert(write(local->socket,&temp,1)==1);
	writeLong(payload,local->socket);

	disconnect(local);
	return 0;
}
/*State 2*/
int8_t login(int32_t size, struct client * local)
{
	printf("[client][INFO] Login Start\n");

	int8_t temp;
	assert(read(local->socket,&temp,1)==1); /*Read username length*/
	local->username=malloc(temp&0xFF+1); /*Allocate memory for username*/
	readString(temp&0xFF,local->socket,local->username); /*Read username*/

	/*Connect client to server*/	
	assert((local->server_socket=socket(AF_INET, SOCK_STREAM, 0))!=-1);
	assert(connect(local->server_socket, (struct sockaddr *)&SERVER_ADDR, ADDR_LEN)!=-1);	
	local->server_connected=1;	
	printf("[proxy][INFO] Client connected to %s:%i\n",inet_ntoa(SERVER_ADDR.sin_addr),ntohs(SERVER_ADDR.sin_port));
	
	/*Forward Packet*/
	printf("[proxy][INFO] Player Identification\n");
	temp=0; /*Packet ID*/
	assert(write(local->server_socket,&temp,1)==1);
	temp=CLASSIC_PROTOCOL; /*Protocol Version*/
	assert(write(local->server_socket,&temp,1)==1);
	int8_t* tempstring=malloc(65);
	padString(local->username,tempstring);
	writeString(local->server_socket,tempstring); /*Send padded username*/
	padString("",tempstring);
	writeString(local->server_socket,tempstring); /*Send blank verification key*/
	free(tempstring);	
	assert(write(local->server_socket,&temp,1)==1); /*Send blank byte*/
	return 0;
}
int8_t initialise_client_functions(){
	/*State 0*/
	clientfunction[0x00][0x00]=handshake;

	/*State 1*/
	clientfunction[0x01][0x00]=status_request;
	clientfunction[0x01][0x01]=status_ping;

	/*State 2*/
	clientfunction[0x02][0x00]=login;
	return 0;
}
