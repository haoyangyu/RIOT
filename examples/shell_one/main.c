#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "shell_commands.h"

int hello_world(int argc, char **argv){
	(void)argc;
	(void)argv;
	printf("hello world!\n");
	return 0;
}

const shell_command_t shell_commands[] = {
	{"hello", "print hello world", hello_world},
	{NULL, NULL, NULL}
};

int main(void){
	(void)puts("welcome my first program");
	
	shell_init(&shell,shell_commands,UART0_BUFSIZE, uart0_readc, uart0_putc);
	shell_run(&shell);
}
