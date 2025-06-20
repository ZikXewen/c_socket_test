#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int createTCPIpv4Socket();
void createIpv4Address(struct sockaddr_in *addr, char *ip, int port);

#endif
