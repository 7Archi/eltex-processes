GCC = gcc -Wall -Werror

.PHONY: all 

all: main

main: proc.c 
	$(GCC) proc.c -o proc
		



