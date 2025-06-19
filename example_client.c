#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int createTCPIpv4Socket() {
  return socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP
}

void createIpv4Address(struct sockaddr_in *addr, char *ip, int port) {
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port); // htons = host to network short (endians)
  inet_pton(AF_INET, ip,
            &addr->sin_addr.s_addr); // presentation to network format
}

int main() {
  int fd = createTCPIpv4Socket();
  if (fd == -1) {
    perror("fd");
    return 1;
  }

  struct sockaddr_in addr;
  createIpv4Address(&addr, "23.215.0.138", 80);

  int res = connect(fd, &addr, sizeof addr);
  if (res == -1) {
    perror("connect");
    return -1;
  }
  printf("Connection Established!\n\n");

  char *msg = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
  send(fd, msg, strlen(msg), 0);
  printf("Message Sent\n\n%s\n\n", msg);

  char buf[2048];
  recv(fd, buf, 2048, 0);
  printf("Response received\n\n%s\n\n", buf);
}
