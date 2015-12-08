#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/reboot.h>
#include <errno.h>
#include <strings.h>
#include <getopt.h>

static const char *short_options = "h12345678";
static const struct option long_options[] = {
  {"help",         no_argument, NULL, 'h'},
  {"--cad-off",    no_argument, NULL, '1'},
  {"--cad-on",     no_argument, NULL, '2'},
  {"--halt",       no_argument, NULL, '3'},
  {"--kexec",      no_argument, NULL, '4'},
  {"--power-off",  no_argument, NULL, '5'},
  {"--restart",    no_argument, NULL, '6'},
  {"--restart2",   no_argument, NULL, '7'},
  {"--sw-suspend", no_argument, NULL, '8'},
};

usage(void){
  puts("--Reboot--\n\n"
  "        Play with reboot syscall\n\n"
  "Options:\n\n"
  " -h|--help		Display help\n"
  " -1|--cad-off	        Control Alt Delete off\n"
  " -2|--cad-on	        Control Alt Delete on\n"
  " -3|--halt	        Halt\n"
  " -4|--kexec	        Execute loaded earlier (kexec_load)\n"
  " -5|--power-off	        Power off\n"
  " -6|--restart	        Restart\n"
  " -7|--restart2	        Restart 2\n"
  " -8|--sw-suspend	Suspend to disk (hibernate)\n"
  "More info: reboot(2), linux/include/uapi/linux/reboot.h");
}

funfacts(void){
  puts("--Reboot--\n\n"
  "        Fun Facts\n\n"
  "#LINUX_REBOOT_MAGIC1  is 0xfee1dead"
  "#LINUX_REBOOT_MAGIC2  is 672274793"
  "#LINUX_REBOOT_MAGIC2A is 85072278"
  "#LINUX_REBOOT_MAGIC2B is 369367448"
  "#LINUX_REBOOT_MAGIC2C is 537993216");
}

int main(int argc, char **argv){
  int opt, option, opt_index;
  void *extra_args;

  if (argc <= 1){
    puts("No options given, try ``--help''\n");
    exit(1);
  }

  while ((opt = getopt_long(argc, argv, short_options,
			long_options, &opt_index)) != EOF) {
    switch (opt) {
    case 'h':
      usage(); exit(0);
    case '1':
      option = LINUX_REBOOT_CMD_CAD_OFF; break;
    case '2':
      option = LINUX_REBOOT_CMD_CAD_ON; break;
    case '3':
      option = LINUX_REBOOT_CMD_HALT; break;
    case '4':
      option = LINUX_REBOOT_CMD_KEXEC; break;
    case '5':
      option = LINUX_REBOOT_CMD_POWER_OFF; break;
    case '6':
      option = LINUX_REBOOT_CMD_RESTART; break;
    case '7':
      option = LINUX_REBOOT_CMD_RESTART2; break;
    case '8':
      option = LINUX_REBOOT_CMD_SW_SUSPEND; break;
    default:
      usage(); exit(1);
    }
  }

  printf("LINUX_REBOOT_MAGIC1: 0x%08x\nLINUX_REBOOT_MAGIC2: 0x%08x\n", LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2);
  printf("Option: Hexidecimal 0x%08x\n", option);

  if (syscall(SYS_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, option) == -1){
	perror("ERROR: Failure using reboot");
	exit(-1);
  }

}
