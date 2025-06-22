#include <stdio.h>
#include <unistd.h>

#include "socket_utils.h"

int main() {
  int serverFd = createTCPIpv4Socket();
  if (serverFd == -1) {
    perror("fd");
    return 1;
  }

  struct sockaddr_in serverAddr;
  createIpv4Address(&serverAddr, "", 8000);

  int res = bind(serverFd, (struct sockaddr *)&serverAddr, sizeof serverAddr);
  if (res == -1) {
    perror("bind");
    return -1;
  }
  printf("Socket bound successfully\n");

  res = listen(serverFd, 10);
  if (res == -1) {
    perror("listen");
    return -1;
  }
  printf("Listening...\n");

  struct sockaddr_in clientAddr;
  socklen_t clientAddrSz = sizeof clientAddr;
  int clientFd =
      accept(serverFd, (struct sockaddr *)&clientAddr, &clientAddrSz);
  if (clientFd == -1) {
    perror("accept");
    return -1;
  }
  printf("Accepting connection...\n");

  char buf[2048];
  while (1) {
    ssize_t ct = recv(clientFd, buf, 2048, 0);
    if (ct == 0) {
      break;
    }
    if (ct == -1) {
      perror("recv");
      continue;
    }
    buf[ct] = 0;

    printf("%d: %s\n", clientFd, buf);
  }

  close(clientFd);
  close(serverFd);
}
