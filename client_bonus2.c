#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
//#include "ft_printf/ft_printf.h"

static int	terminator;

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		number;
	char	*str;

	str = (char *)nptr;
	i = 0;
	number = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}

void	send_signals(int pid, char character)
{
	int	i;
	int	bit_index;

	i = 0;
	bit_index = 0;
	while(bit_index < 8)
	{
		i = 0;
		if (character & (0x01 << bit_index))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (terminator == 0)
		{
			if (i == 100)
				printf("No response from server :(\n)");
			i++;
			usleep(100);
		}
		terminator = 0;
		bit_index++;
	}
}

void signal_confirm(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	
	terminator = 1;
	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		bit++;
	else if (signum == SIGUSR1)
	{
		printf("MSG SENT, %d bytes RECEIVED BACK FROM SERVER \n", bit/8);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	action;
	static int	i = 0;

	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = signal_confirm;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	if (argc != 3 || ft_atoi(argv[1]) <= 0)
	{
		printf("invalid argument(s) or format!\n");
		printf("expected: ./client <serverPID> <\"MESSAGE\">\n");
		exit(1);
	}
	while (argv[2][i] != '\0')
	{
		send_signals(ft_atoi(argv[1]), argv[2][i]);
		i++;
	}
	send_signals(ft_atoi(argv[1]), '\0');
	while(1)
		pause();
	return (0);
}

/*
H 072 01001000
				01001000("H")	&(compares bit to bit)	 00000001 -----> signal in 1st loop 00000000
					00000001(whose bits get shifted)	<<	bit(by how many positions;in 1st loop=0) --> 00000001
				
				01001000("H") &  00000010 ---> 00000000
					00000001 << bit(in 2nd loop 1) --> 00000010 (checks for a 1 in the 2nd position begining from the end)
				
				01001000("H") & 00000100 ---> 00000000
					00000001 << 2 --> 00000100 (checks if we have a 1 in the 3rd position)
				01001000("H") & 00001000 ---> 00000100
					00000001 << 3 --> 00001000
				
				01001000("H") & 00010000 ---> 00000000
					00000001 << 4 --> 00010000
				01001000("H)") & 00100000 ---> 00000000
					00000001 << 5 --> 00100000
				01001000("H)") & 01000000 ---> 01000000
					00000001 << 6 --> 01000000
				01001000("H)") & 10000000 ---> 00000000
					00000001 << 7 --> 10000000
		SIGURG	2-2-2-1-2-2-1-2
				0 0 0 1 0 0 1 0
i 105 */
