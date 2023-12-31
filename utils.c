/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:29:46 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/08 17:57:46 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philo_and_modulo(t_philo *p)
{
	while (ready_change(0, p->info_p, 0) == 0)
		usleep(500);
	if (p->philo_nb % 2 == 0)
		usleep(p->info_p->time_to_eat * 0.9 * 1000);
}

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

int	get_time(t_info*p)
{
	int				res;
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	res = ((cur_time.tv_usec / 1000) + (cur_time.tv_sec * 1000)
			- p->start_time);
	return (res);
}

void	print_msg(t_philo *p, int msg)
{
	pthread_mutex_lock(&p->info_p->voice);
	if (ft_death_mtx(0, p->info_p, 0) == 0 && msg == 0)
		printf("%d Philo[%d] has taken a fork\n",
			get_time(p->info_p), p->philo_nb);
	if (ft_death_mtx(0, p->info_p, 0) == 0 && msg == 1)
		printf("%d Philo[%i] \033[33mis eating\033[0m\n",
			get_time(p->info_p), p->philo_nb);
	if (ft_death_mtx(0, p->info_p, 0) == 0 && msg == 2)
		printf("%d Philo[%i] \033[32mis thinking\033[0m\n",
			get_time(p->info_p), p->philo_nb);
	if (ft_death_mtx(0, p->info_p, 0) == 0 && msg == 3)
		printf("%d Philo[%i] \033[34mis sleeping\033[0m\n",
			get_time(p->info_p), p->philo_nb);
	if (ft_death_mtx(0, p->info_p, 0) == 0 && msg == 4)
		printf("%d Philo[%d] has taken the second fork\n",
			get_time(p->info_p), p->philo_nb);
	pthread_mutex_unlock(&p->info_p->voice);
}
