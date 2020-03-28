#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <assert.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/*Include block values and conversion tables*/
#include "blocks.h"

#define CLASSIC_PROTOCOL 7 /*Classic protocol version*/
#define MODERN_VERSION "1.15.2" /*1.15.2 version*/
#define MODERN_PROTOCOL 578 /*1.15.2 protocol version*/

/*Response Packet Components*/
#define RESPONSE_1 "{\"version\":{\"name\":\""
#define RESPONSE_2 "\",\"protocol\":"
#define RESPONSE_3 "},\"players\":{\"max\":"
#define RESPONSE_4 ",\"online\":"
#define RESPONSE_5 "},\"description\":{\"text\":\""
#define RESPONSE_6 "\"}}}"

/*Array and size details*/
#define INT_AS_STRING_LENGTH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

/*Create client structure*/
struct client 
{
	int socket;
	int8_t state;
	int8_t server_connected;
	int server_socket;
	struct sockaddr_in in_addr;
	socklen_t addr_len;
	int8_t inuse;
	int8_t* username;
};

int32_t readVarInt(int);
int64_t readVarLong(int);
void writeVarInt(int32_t, int);
void writeVarLong(int64_t, int);
int8_t varIntLength(int32_t);
int8_t varLongLength(int64_t);
int64_t readLong(int);
void writeLong(int64_t, int);
int16_t readShort(int);
void writeShort(int16_t, int);
void readString(int32_t,int,int8_t*);
void writeString(int,int8_t*);
int32_t readLine(int, int8_t*);
void padString(int8_t*,int8_t*);
void disconnect(struct client *);
#endif
