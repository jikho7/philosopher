#include "philo.h"

int check_args(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid args\n");
			return (-1);
		}
		i++;
	}
	return (0);
}