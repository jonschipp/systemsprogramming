#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char * check_file(const char *file){
  if ((open(file, O_RDONLY)) == -1){
    return "A";
  } else {
    return "B";
  }
}

int seek_end(int fd){
  off_t l_ret;
  if ((l_ret = lseek(fd, 0, SEEK_END)) == -1){
    perror("lseek"); exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char **argv){
  int fd, num_bytes, skip_append, count;
  ssize_t ret;
  const char *file;
  const char *byte;

  if (argc < 3 || argc > 4){
    printf("Exercise 5-3: Atomic append\nUsage: %s <file> <num_bytes> [noappend]\n", argv[0]);
    puts("Test1: $ atomic_append f1 1000000 & atomic_append f1 1000000");
    puts("Test2: $ atomic_append f2 1000000 noappend & atomic_append f2 1000000 noappend");
    puts("Verify: $ ls -l f1 f2");
    exit(EXIT_FAILURE);
  }

  file      = argv[1];
  num_bytes = atoi(argv[2]);
  if (argv[3]){
    skip_append = 1;
  }

  if (skip_append == 1){
    byte = check_file(file);
    if ((fd = open(file, O_WRONLY | O_CREAT, 0744)) == -1){
      perror("open"); exit(EXIT_FAILURE);
    }
    printf("File %s opened.\n", file);
  } else {
    byte = check_file(file);
    if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0744)) == -1){
      perror("open"); exit(EXIT_FAILURE);
    }
    printf("File %s opened with O_APPEND.\n", file);
  }
    
  for (count = 0; count <= num_bytes; count++){
    if (skip_append == 1){
      seek_end(fd);
      if (count == 0){
        puts("Seeking to end of file for each one byte write");
      }
    }
    if ((ret = write(fd, byte, 1)) == -1){
      perror("write"); exit(EXIT_FAILURE);
    }
  }

  if (close(fd) == -1){
    perror("close");
  }
}
