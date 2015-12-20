#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "dup.h"

void info(int fd){
  off_t position;
  int flags, is_flag;
  flags = fcntl(fd, F_GETFL);
  position = lseek(fd, 0, SEEK_CUR);
  printf("  File descriptor %d\n"
         "  File offset %lld\n",
          fd, position);
  is_flag = flags & O_RDONLY;
  if (is_flag == O_RDONLY){
    puts("  File flag is O_RDONLY");
  } else {
    puts("  File flag is not O_RDONLY");
  }
}

void close_fd(int fd){
  if (close(fd) == -1){
    perror("close");
  }
}

int main(int argc, char **argv){
  int oldfd, newfd;
  off_t ret, position;
  const char *file;

  if (argc != 2){
    printf("Exercise 5-3: Implement dup(2) and dup2(2) using fcntl\nUsage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  file  = argv[1];

  if ((oldfd = open(file, O_RDONLY)) == -1){
    perror("open"); exit(EXIT_FAILURE);
  }

  printf("Original file descriptor (%s):\n", file);
  info(oldfd);
  newfd = dup_one(oldfd);
  puts("Duplication of original file descriptor:");
  info(newfd);
  close_fd(oldfd);
  close_fd(newfd);
}
