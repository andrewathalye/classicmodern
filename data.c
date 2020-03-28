#include "data.h"
/*TODO: See if these two functions require buf&=0xFF*/
int32_t readVarInt(int socket) {
	int8_t numRead = 0;
	int32_t result = 0;
	int8_t buf=0;
	do	
	{
		assert(read(socket, &buf, 1)==1);
		result |= ((buf & 0b01111111) << (7 * numRead));
		numRead++;
		assert(numRead<=5);
	} while ((buf & 0b10000000) != 0);
	return result;
}
int64_t readVarLong(int socket) {
	int8_t numRead = 0;
	int32_t result = 0;
	int8_t buf=0;
	do
	{
		assert(read(socket, &buf, 1)==1);
		result |= ((buf & 0b01111111) << (7 * numRead));
		numRead++;
		assert(numRead<=10);
	} while ((buf & 0b10000000) != 0);
	return result;
}
void writeVarInt(int32_t value, int socket) {
	int8_t temp;
	do
	{
		temp=value&0b01111111;
		value>>=7;
		if(value!=0) temp|=0b10000000;
		assert(write(socket, &temp, 1)==1);
	} while(value!=0);
}
void writeVarLong(int64_t value, int socket) {
	int8_t temp;
	do
	{
		temp=value&0b01111111;
		value>>=7;
		if(value!=0) temp|=0b10000000;
		assert(write(socket, &temp, 1)==1);
	} while(value!=0);
}
int8_t varIntLength(int32_t value) {
	int8_t count=0;
	int8_t temp;
	while(value!=0){
		temp=value & 0b01111111;
		value>>=7;
		if(value != 0) temp|=0b10000000;		
		count++;
	}
	return count;
}
int8_t varLongLength(int64_t value) {
	int8_t count=0;
	int8_t temp;
	while(value!=0){
		temp=value & 0b01111111;
		value>>=7;
		if(value != 0) temp|=0b10000000;		
		count++;
	}
	return count;
}
int64_t readLong(int socket)
{
	int64_t output;
	int64_t tmp;
	assert(read(socket,&tmp,1)==1);
	output=(tmp&0xFF)<<56;
	assert(read(socket,&tmp,1)==1);
	output=(tmp&0xFF)<<48;
	assert(read(socket,&tmp,1)==1);
	output|=(tmp&0xFF)<<40;
	assert(read(socket,&tmp,1)==1);
	output|=(tmp&0xFF)<<32;
	assert(read(socket,&tmp,1)==1);
	output|=(tmp&0xFF)<<24;
	assert(read(socket,&tmp,1)==1);
	output|=(tmp&0xFF)<<16;
	assert(read(socket,&tmp,1)==1);
	output|=(tmp&0xFF)<<8;
	assert(read(socket,&tmp,1)==1);
	output|=tmp&0xFF;
	return output;
}
void writeLong(int64_t input,int socket)
{
	assert(write(socket,&input,8)==8);
}
int16_t readShort(int socket)
{
	int16_t output;
	int8_t tmp;
	assert(read(socket,&tmp,1)==1);
	output=(tmp&0xFF)<<8;
	assert(read(socket,&tmp,1)==1);
	output|=tmp&0xFF;
	return output;
}
void writeShort(int16_t value,int socket)
{
	assert(write(socket,&value,2)==2);
}
/*WARNING: In order to safely use, malloc should first be used to
allocate space for the null byte*/
void readString(int32_t length, int socket, int8_t* buf)
{
	assert(read(socket,buf,length)==length);
	buf[length]=0;
}
void writeString(int socket, int8_t* buf)
{
	assert(write(socket,buf,strlen(buf))==strlen(buf));
}
/*WARNING: In order to safely use, malloc should first be used to
allocate space for the entire buffer + 1. This function will block
if input data is not available. This function also expects \n as
the line-terminator, which may not be the case under non-POSIX
operating systems.*/
int32_t readLine(int socket, int8_t* buf)
{
	int32_t i;
	int8_t tmp=0;
	for(i=0;tmp!='\n';i++)
	{
		assert(read(socket,&tmp,1)==1);
		tmp&=0xFF;
		buf[i]=tmp;
	}
	buf[i-1]=0; /*null-terminate string*/
	return i; /*return count of bytes read*/
}

/*Please only use with strings initialised with a length of 65
through malloc*/
void padString(int8_t* in,int8_t* buf)
{
	for(int32_t i=0;i<64;i++)
	{
		if(i>=strlen(in))
			buf[i]=' ';
		else
			buf[i]=in[i];
	}
	buf[64]=0;
}

void disconnect(struct client * local)
{
	assert(close(local->socket)==0);
	if(local->server_connected) assert(close(local->server_socket)==0);
	local->server_connected=0;
	local->inuse=0;
	printf("[INFO] Client disconnected from %s:%i\n",inet_ntoa(local->in_addr.sin_addr),ntohs(local->in_addr.sin_port));
}
