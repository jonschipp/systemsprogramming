#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){
  int fd1, fd2, fd3;
  const char *file;
  char path[256];

  if (argc != 2){
    printf("Exercise 5-6: Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  file  = argv[1];
  sprintf(path, "cat %s", file);

  fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  printf("File descriptor %d created from %s\n", fd1, file);
  fd2 = dup(fd1);
  printf("File descriptor %d duplicated as %d\n", fd1, fd2);
  fd3 = open(file, O_RDWR);
  printf("File descriptor %d created from %s\n", fd3, file);

  write(fd1, "Hello,", 6);
  printf("Wrote 6 bytes to file descriptor %d:\n", fd1);
  system(path);
  puts("");

  write(fd2, "world", 6);
  printf("\nWrote 6 bytes to file descriptor %d:\n", fd2);
  system(path);
  puts("");

  lseek(fd2, 0, SEEK_SET);
  printf("\nSeek to position 0 of %d\n", fd2);
  write(fd1, "HELLO,", 6);
  printf("Wrote 6 bytes to file descriptor %d:\n", fd1);
  system(path);
  puts("");

  write(fd3, "Gidday", 6);
  printf("\nWrote 6 bytes to file descriptor %d:\n", fd3);
  system(path);
  puts("");
}
