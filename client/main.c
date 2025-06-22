#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "socket_utils.h"

void trim(char *s) {
  unsigned char *l = (unsigned char *)s;
  while (isspace(*l))
    ++l;

  if (*l == 0) {
    *s = 0;
    return;
  }

  unsigned char *r = (unsigned char *)(s + strlen(s) - 1);
  while (isspace(*r))
    --r;

  while (l <= r)
    *(s++) = *(l++);
  *s = 0;
}

int main() {
  int fd = createTCPIpv4Socket();
  if (fd == -1) {
    perror("fd");
    return 1;
  }

  struct sockaddr_in addr;
  createIpv4Address(&addr, "127.0.0.1", 8000);

  int res = connect(fd, (struct sockaddr *)&addr, sizeof addr);
  if (res == -1) {
    perror("connect");
    return -1;
  }
  printf("Connection Established!\n\n");

  char *buf = NULL;
  size_t sz = 0;
  while (1) {
    ssize_t ct = getline(&buf, &sz, stdin);
    if (ct == -1) {
      perror("getline");
      continue;
    }
    if (ct == 0) {
      continue;
    }
    buf[ct - 1] = 0;
    trim(buf);
    size_t bufLen = strlen(buf);
    if (bufLen == 0) {
      continue;
    }
    if (strcmp(buf, "exit") == 0) {
      break;
    }

    res = send(fd, buf, bufLen, 0);
    if (res == -1) {
      perror("res");
      continue;
    }
  }

  free(buf);
  close(fd);
}
