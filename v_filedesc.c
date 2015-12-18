#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void info(int fd, off_t position, int flags);

void info(int fd, off_t position, int flags){
  int is_flag;
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

int main(int argc, char **argv){
  int oldfd, newfd, flags;
  off_t ret, position;
  const char *file;

  if (argc != 2){
    printf("Exercise 5-5: Verify settings of duplicate file descriptors\nUsage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  file  = argv[1];

  if ((oldfd = open(file, O_RDONLY)) == -1){
    perror("open"); exit(EXIT_FAILURE);
  }
    
  if ((ret = lseek(oldfd, 1, SEEK_SET)) == -1){
    perror("lseek"); exit(EXIT_FAILURE);
  }

  printf("Original file descriptor (%s):\n", file);
  position = lseek(oldfd, 0, SEEK_CUR);
  flags = fcntl(oldfd, F_GETFL);
  info(oldfd, position, flags);

  newfd = dup(oldfd);
  flags = fcntl(newfd, F_GETFL);
  puts("Duplication of original file descriptor:");
  info(newfd, position, flags);

  if (close(oldfd) == -1){
    perror("close");
  }
  if (close(newfd) == -1){
    perror("close");
  }
}
