.PHONY: default help

Q               = @
bold   		= $(shell tput bold)
underline 	= $(shell tput smul)
normal 		= $(shell tput sgr0)
red		= $(shell tput setaf 1)
yellow	 	= $(shell tput setaf 3)

default: help

help:
	$(Q)echo "$(bold)System Programming Examples build targets:$(normal)"
	$(Q)echo " $(red)atomic_append$(normal)     - atomic append program"
	$(Q)echo " $(red)beginning_append$(normal)  - validate how O_APPEND works"
	$(Q)echo " $(red)cp$(normal)                - a implementation of cp"
	$(Q)echo " $(red)dup$(normal)               - a implementation of dup/dup2 using fcntl ($(yellow)dup.h$(normal))"
	$(Q)echo " $(red)fdwrite$(normal)           - show output of writes(2) to different fd's"
	$(Q)echo " $(red)reboot$(normal)            - call reboot(2) with various options ($(yellow)linux/reboot.h$(normal))"
	$(Q)echo " $(red)tee$(normal)               - a implementation of tee"
	$(Q)echo " $(red)verify_dup$(normal)        - verify settings of duplicate file descriptor"

atomic_append:
	$(Q)echo " $(yellow)Building atomic_append$(normal)"
	gcc -o aappend atomic_append.c
	$(Q)echo " $(yellow)Try ./aappend$(normal)"

beginning_append:
	$(Q)echo " $(yellow)Building beginning_append$(normal)"
	gcc -o bappend b_append.c
	$(Q)echo " $(yellow)Try ./bappend$(normal)"

cp:
	$(Q)echo " $(yellow)Building cp$(normal)"
	gcc -o cp cp_bytes.c
	$(Q)echo " $(yellow)Try ./cp$(normal)"

dup:
	$(Q)echo " $(yellow)Building dup$(normal)"
	gcc -c dup.c -o dup.o
	gcc -o dup i_dup.c dup.c
	$(Q)echo " $(yellow)Try ./dup$(normal)"

fdwrite:
	$(Q)echo " $(yellow)Building fd_write$(normal)"
	gcc -o fdwrite fd_write.c
	$(Q)echo " $(yellow)Try ./fdwrite$(normal)"

reboot:
	$(Q)echo " $(yellow)Building reboot$(normal)"
	gcc -o reboot reboot.c
	$(Q)echo " $(yellow)Try ./reboot$(normal)"

tee:
	$(Q)echo " $(yellow)Building tee$(normal)"
	gcc -o tee tee.c
	$(Q)echo " $(yellow)Try ./tee$(normal)"

verify_dup:
	$(Q)echo " $(yellow)Building verify_dup$(normal)"
	gcc -o vdup v_filedesc.c
	$(Q)echo " $(yellow)Try ./vdup$(normal)"
