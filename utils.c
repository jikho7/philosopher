#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	minus;

	result = 0;
	sign = 0;
	minus = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+' || *str == 32)
	{
		if (*str == '-')
			minus++;
		sign++;
		str++;
	}
	if (sign > 1 || minus > 1)
		return (0);
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + *(str++) - '0';
	if (result == -2147483648)
		return (-2147483648);
	if (minus == 1)
		result = result * -1;
	return (result);
}

// void* print_id(void *arg)
// {
// 	long id = (long)arg;
// 	t_philo *s;
// 	int i = 0;

// 	s = (t_philo *)arg;
// 	fprintf(stderr, "philo [%i] id: %ld\n", i, id);
// 	return (0);
// }