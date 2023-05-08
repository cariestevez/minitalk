#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_printf/ft_printf.h"

void signal_handler(int signum)
{
	static int	bit = 0;
	static char byte = 0;
	
	if (signum == SIGUSR1)
		byte |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", byte);
		bit = 0;
		byte = 0;
	}
}

/*1st call bit(0)++
2nd call bit(1)++
3rd call bit(2)++
4th call byte(00000000) += [00000001 << bit(3) -> 00001000]
		 bit(3)++
5th call bit(4)++
6th call bit(5)++
7th call byte(00001000) += [00000001 << bit(6) -> 01000000] -> 01001000
		 bit(6)++
8th call bit(7)++
9th call bit(8)
		 printf(byte)*/

int main(void)
{
	int pid;
//	struct sigaction	action;

	pid = getpid();
	printf("Welcome!\nServer's PID: %d\n", pid);
/*	action.sa_handler = signal_handler;
	//sigemptyset(&action.sa_mask);
	action.sa_flags = 0;*/
	while(1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
		//usleep(10);
	}
	return (0);
}
