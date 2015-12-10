#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <getopt.h>

#define BUF_SIZE 1024

static const char *short_options = "hao";
static const struct option long_options[] = {
  {"help",         no_argument, NULL, 'h'},
  {"--append",     no_argument, NULL, 'a'},
};

usage(void){
  puts("--Tee--\n"
  "        Basic implementation of tee\n"
  "Options:\n"
  " -h|--help		Display help\n"
  " -a|--append	        Append\n");
}

int main(int argc, char **argv){
  int fd, w_ret, opt, opt_index;
  int options = O_WRONLY | O_CREAT | O_TRUNC;
  ssize_t r_ret;
  //size_t w_ret;
  char buffer[BUF_SIZE];
  const char *filename;

  if (argc <= 1){
    puts("No options given, try ``--help''");
    exit(1);
  }


  while ((opt = getopt_long(argc, argv, short_options,
			long_options, &opt_index)) != EOF) {
    switch (opt) {
    case 'h':
      usage(); exit(0);
    case 'a':
      options = O_WRONLY | O_APPEND; break;
    //case 'f':
    //  filename = optarg;
    default:
      break;
    }
  }


  if ((fd = open(argv[2], options)) == -1){
    perror("open");
  }
    
  while(((r_ret = read(STDIN_FILENO, buffer, BUF_SIZE)) != 0)){
     if (r_ret == -1){
       perror("read");
     }

     if ((w_ret = write(fd, buffer, r_ret)) != 0){
       if (w_ret == -1){
         perror("write"); 
       }
     }

     if ((w_ret = write(STDOUT_FILENO, buffer, r_ret)) != 0){
       if (w_ret == -1){
         perror("write"); 
       }
     }
  }

  if (close(fd) == -1){
    perror("close");
  }

}
