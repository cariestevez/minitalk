#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

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

void	send_signals(int pid, char *message)
{
	int	character;
	int	bit;

	character = 0;
	//bit = 0;
	while (message[character] != '\0')
	{
		bit = 0;
		while(bit < 8)
		{
			if ((message[character] & (0x01 << bit)))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit++;
		}
		character++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || ft_atoi(argv[1]) <= 0) // || ft_atoi(argv[2]) == 0)
	{
		printf("invalid argument(s) or format!\n");
		printf("expected: ./client <serverPID> <MESSAGE>\n");
		exit(1);
	}
	send_signals(ft_atoi(argv[1]), argv[2]);
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