#include <pthread.h>

#include "data.h"
#include "proxy.h"

/*Include client functions*/
#include "client.h"
/*Include server functions*/
#include "server.h"

/*Create array of clients*/
struct client clients[MAX_CLIENTS];

/*Create threads*/
pthread_t logic_thread;
pthread_t connection_thread;

/*Store server configuration details*/
int32_t BIND_ADDRESS;
in_port_t BIND_PORT;
int32_t SERVER_ADDRESS;
in_port_t SERVER_PORT;
struct sockaddr_in SERVER_ADDR;
int8_t* MOTD;
socklen_t ADDR_LEN;

/*Create bind socket*/
int bindsocket;

void *logicHandler() {
	int32_t count; /*Number of bytes available*/
	int32_t size; /*Size*/
	int32_t id; /*Packet ID*/
	while(1) {
		/*TODO: Search for ready client connections and read data*/
		for(int32_t i=0;i<MAX_CLIENTS;i++)
		{
			if(clients[i].inuse)
			{
				assert(ioctl(clients[i].socket, FIONREAD, &count)==0);
				if(count>0)
				{
					/* Retrieve size and ID from packet*/
					size=readVarInt(clients[i].socket);
					id=readVarInt(clients[i].socket);					
					size-=1; /*Subtract size of packet ID*/
					printf("[logic_thread][INFO] Received client packet state %i:%x\n",clients[i].state,id);
					(*clientfunction[clients[i].state][id])(size,&clients[i]);				
				}
			}
			if(clients[i].inuse && clients[i].server_connected) /*If still in use and connected to the server*/
			{
				assert(ioctl(clients[i].server_socket, FIONREAD, &count)==0);
				if(count>0)
				{
					assert(read(clients[i].server_socket,&id,1)==1);
					printf("[logic_thread][INFO] Received server packet %x\n",id);
					(*serverfunction[id])(&clients[i]);				
				}
			}
		}
	}
}

void *connectionHandler() {
	while(1) {
		for(int32_t i=0;i<MAX_CLIENTS;i++) {
			if(!clients[i].inuse) {
				/*Accept client connection*/
				clients[i].addr_len=ADDR_LEN;				
				assert((clients[i].socket=accept(bindsocket, (struct sockaddr *)&clients[i].in_addr, &clients[i].addr_len))!=-1);				
				clients[i].inuse=1;
				clients[i].state=0; /*Set state to Handshaking*/
				printf("[connection_thread][INFO] Client %i connected from %s:%i\n",i,inet_ntoa(clients[i].in_addr.sin_addr),ntohs(clients[i].in_addr.sin_port));					
			}
		}
	}
}

int8_t get_players(){
	int8_t count;
	for(int8_t i=0; i<MAX_CLIENTS; i++)
		if(clients[i].inuse) count++;
	return count;
}

int main(int argc, char *argv[])
{
	/*Open config.txt file*/
	int config;
	assert((config=open("config.txt", O_RDONLY))!=-1);

	/*Check length of file*/
	int32_t count;
	assert(ioctl(config, FIONREAD, &count)==0);
	assert(count!=0);

	/*Extract data from file*/
	int8_t* config_data=malloc(count+1); /*allocate space for null terminator*/
	readLine(config, config_data); /*skip bindaddr comment*/
	readLine(config, config_data); /*read bindaddr*/
	BIND_ADDRESS=inet_addr(config_data);
	readLine(config, config_data); /*skip bindport comment*/
	readLine(config, config_data); /*read bindport*/
	BIND_PORT=htons(atoi(config_data));
	readLine(config, config_data); /*skip serveraddr comment*/
	readLine(config, config_data); /*read serveraddr*/
	SERVER_ADDRESS=inet_addr(config_data);
	readLine(config, config_data); /*skip serverport comment*/
	readLine(config, config_data); /*read serverport*/
	SERVER_PORT=htons(atoi(config_data));
	readLine(config, config_data); /*skip motd comment*/
	assert(readLine(config, config_data) < MAX_MOTD_LENGTH); /*read motd*/
	MOTD=memcpy(malloc(MAX_MOTD_LENGTH), config_data, strlen(config_data)+1); /*allocate memory for motd*/
	MOTD[strlen(config_data)+1]=0; /*null-terminate string*/

	/*Close file and free memory*/
	free(config_data);
	close(config);

	/*Initialise bind socket and address*/
	bindsocket=socket(AF_INET, SOCK_STREAM, 0);
	struct in_addr bind_in_addr={BIND_ADDRESS};
	struct sockaddr_in bindaddr = {AF_INET, BIND_PORT, bind_in_addr};
	
	/*Store bindaddr size for future reference*/
	ADDR_LEN=sizeof(bindaddr);

	/*Bind socket*/
	assert(bind(bindsocket, (struct sockaddr *)&bindaddr, ADDR_LEN)==0);
	assert(listen(bindsocket,3)==0); /*TODO: check backlog*/
	printf("[INFO] Bound to %s:%i\n",inet_ntoa(bindaddr.sin_addr),ntohs(bindaddr.sin_port));

	/*Create server socket address*/
	struct in_addr server_in_addr={SERVER_ADDRESS};
	SERVER_ADDR.sin_family=AF_INET;
	SERVER_ADDR.sin_port=SERVER_PORT;
	SERVER_ADDR.sin_addr=server_in_addr;

	/*Initialise function tables*/
	initialise_client_functions(); /*From client.c*/
	initialise_server_functions(); /*From server.c*/
	/*Initialise classic to modern mappings*/
	initialise_mappings(); /*From blocks.c*/
	printf("[INFO] Initialised tables and mappings\n");

	/*Create logic thread*/
	pthread_create(&logic_thread, NULL, logicHandler, NULL);
	printf("[INFO] Started logic thread\n");

	/*Create client connection thread*/
	pthread_create(&connection_thread, NULL, connectionHandler, NULL);
	printf("[INFO] Started client connection thread\n");
		
	/*Wait for logic handler to terminate*/
	pthread_join(logic_thread, NULL);

	return 0;
}
