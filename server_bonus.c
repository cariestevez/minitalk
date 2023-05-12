#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_printf/ft_printf.h"

void signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	pid = 0;
	static char byte = 0;
	
	(void)context;
	pid = info->si_pid;
	if (signum == SIGUSR1)
		byte |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if(!byte)
		{
			kill (pid, SIGUSR1);
			pid = 0;
			ft_printf("\n");
			return;
		}
		ft_printf("%c", byte);
		byte = 0;
	}
	kill(pid, SIGUSR2);
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
	struct sigaction	action;

	pid = getpid();
	ft_printf("Welcome!\nServer's PID: %d\n", pid);
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while(1)
		pause();
	return (0);
}
