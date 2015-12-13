#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

int main(int argc, char **argv){
  int ifd, ofd, opt, opt_index, size = 1024, seek = 1024;
  off_t curr, offset = 0;
  ssize_t r_ret, w_ret;
  const char *infile;
  const char *outfile;

  //if (argc < 3 && argc > 5){
  if (argc != 5){
    printf("Usage: %s <infile> <outfile> <seek> <size>\n", argv[0]);
    //printf("Usage: %s <infile> <outfile> [seek] [size]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  infile  = argv[1];
  outfile = argv[2];
  seek    = atoi(argv[3]);
  size    = atoi(argv[4]);
  //if (argv[3]){ 
  //  printf("argv3 %s", argv[3]); 
  //  seek = atoi(argv[3]);
  //}
  //if (argv[4]) { 
  //  printf("argv4 %s", argv[4]);
  //  size = atoi(argv[4]);
  //}
  
  char buffer[size];

  if ((ifd = open(infile, O_RDONLY)) == -1){
    perror("open"); exit(EXIT_FAILURE);
  }
    
  if ((ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1){
    perror("open"); exit(EXIT_FAILURE);
  }
    
  while(((r_ret = read(ifd, buffer, size)) > 0)){
     if (r_ret == -1){
       perror("read"); exit(EXIT_FAILURE);
     }

     if ((w_ret = write(ofd, buffer, r_ret)) > 0){
       if (w_ret == -1){
         perror("write"); exit(EXIT_FAILURE);
       }
     }

     offset += seek;
     if ((curr = lseek(ifd, offset, SEEK_SET))){
       if (curr == -1){
         perror("lseek"); exit(EXIT_FAILURE);
       }
       printf("Offset %lld, Bytes Written(size) %lu\n", curr, w_ret);
     }

  }

  if (close(ifd) == -1){
    perror("close");
  }
  if (close(ofd) == -1){
    perror("close");
  }

}
