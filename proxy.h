#ifndef PROXY_H_INCLUDED
#define PROXY_H_INCLUDED

#define MAX_CLIENTS 20
#define MAX_MOTD_LENGTH 255

struct sockaddr_in SERVER_ADDR;
int8_t* MOTD;
socklen_t ADDR_LEN;

int8_t get_players();
#endif
