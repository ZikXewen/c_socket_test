#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "socket_utils.h"

#define MAX_CLIENTS 20

struct ClientSocket {
  int fd;
  struct sockaddr_in addr;
  pthread_t tid;
};

void threadFn(int fd) {
  char buf[2048];
  while (1) {
    ssize_t ct = recv(fd, buf, 2048, 0);
    if (ct == 0) {
      break;
    }
    if (ct == -1) {
      perror("recv");
      continue;
    }
    buf[ct] = 0;

    printf("%d: %s\n", fd, buf);
  }
  shutdown(fd, SHUT_RDWR);
  close(fd);
}

int main() {
  int sfd = createTCPIpv4Socket();
  if (sfd == -1) {
    perror("fd");
    return 1;
  }

  struct sockaddr_in serverAddr;
  createIpv4Address(&serverAddr, "", 8000);

  int res = bind(sfd, (struct sockaddr *)&serverAddr, sizeof serverAddr);
  if (res == -1) {
    perror("bind");
    return -1;
  }
  printf("Socket bound successfully\n");

  res = listen(sfd, 10);
  if (res == -1) {
    perror("listen");
    return -1;
  }
  printf("Listening...\n");

  struct ClientSocket sockets[MAX_CLIENTS];
  int accepted = 0;

  while (1) {
    socklen_t sz = sizeof(struct sockaddr_in);
    sockets[accepted].fd =
        accept(sfd, (struct sockaddr *)&sockets[accepted].addr, &sz);
    if (sockets[accepted].fd == -1) {
      perror("accept");
      continue;
    }
    printf("A user joined. The group now has %d users.\n", ++accepted);

    pthread_create(&sockets[accepted - 1].tid, NULL,
                   (void *(*)(void *))threadFn,
                   (void *)(size_t)sockets[accepted - 1].fd);
  }
  shutdown(sfd, SHUT_RDWR);
  close(sfd);
}
