#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "dup.h"

int dup_one(int fd){
  int newfd;
  newfd = fcntl(fd, F_DUPFD, 3);
  return newfd;
}

int dup_two(int oldfd, int newfd){
  int is_exist;
  if ((is_exist = fcntl(oldfd, F_GETFL)) == -1){
    if (errno == EBADF){
      close(oldfd);
    }
  }
  newfd = fcntl(oldfd, F_DUPFD, 3);
  return newfd;
}
