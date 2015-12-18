#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){
  int fd;
  off_t l_ret, position;
  ssize_t ret;
  const char *file;
  char string[] = { "this is the data our program writes\n" };

  if (argc != 2){
    printf("Exercise 5-2: Open existing file with O_APPEND, seek to beginning, and then write\nUsage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  file  = argv[1];

  if ((fd = open(file, O_WRONLY | O_APPEND)) == -1){
    perror("open"); exit(EXIT_FAILURE);
  }
    
  if ((l_ret = lseek(fd, 0, SEEK_SET)) == -1){
    perror("lseek"); exit(EXIT_FAILURE);
  }

  position = lseek(fd, 0, SEEK_CUR);
  printf("Current file position is %lld\n", position);

  if ((ret = write(fd, string, sizeof(string))) == -1){
      perror("write"); exit(EXIT_FAILURE);
  } else {
    printf("Writing buffer to %s", file);
  }

  if (close(fd) == -1){
    perror("close");
  }
}
