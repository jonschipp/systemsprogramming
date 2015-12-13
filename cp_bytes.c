#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <getopt.h>

int main(int argc, char **argv){
  int ifd, ofd, opt, opt_index, size = 1, seek = 1;
  off_t curr, offset = 0;
  ssize_t r_ret, w_ret;
  const char *infile;
  const char *outfile;

  if (argc != 5){
    printf("Usage: %s <infile> <outfile> <seek> <size>", argv[0]);
    exit(EXIT_FAILURE);
  }

  infile  = argv[1];
  outfile = argv[2];
  seek    = atoi(argv[3]);
  size    = atoi(argv[4]);
  
  char buffer[size];

  if ((ifd = open(infile, O_RDONLY)) == -1){
    perror("open");
    if (errno == EISDIR) { exit(EXIT_FAILURE); }
  }
    
  if ((ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
    perror("open");
    if (errno == EISDIR) { exit(EXIT_FAILURE); }
  }
    
  while(((r_ret = read(ifd, buffer, size)) != 0)){
     if (r_ret == -1){
       perror("read");
     }

     if ((w_ret = write(ofd, buffer, r_ret)) != 0){
       if (w_ret == -1){
         perror("write"); 
       }
     }

     curr = lseek(ifd, 0, SEEK_CUR);
     offset += seek;
     printf("Current Offset %lld, Next Seek %lld, Bytes Written(size) %lu\n", curr, offset, w_ret);
     lseek(ifd, offset, SEEK_SET);
  }

  if (close(ifd) == -1){
    perror("close");
  }
  if (close(ofd) == -1){
    perror("close");
  }

}
