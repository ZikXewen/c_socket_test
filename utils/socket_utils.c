#include "socket_utils.h"

int createTCPIpv4Socket() {
  return socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP
}

void createIpv4Address(struct sockaddr_in *addr, char *ip, int port) {
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port); // htons = host to network short (endians)
  inet_pton(AF_INET, ip,
            &addr->sin_addr.s_addr); // presentation to network format
}
