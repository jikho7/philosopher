/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:30:10 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/16 16:27:10 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (check_nb_of_arg(ac) == 1)
		return (0);
	if (check_args(av[1]) == -1 || check_args(av[2]) == -1
		|| check_args(av[3]) == -1 || check_args(av[4]) == -1
		|| (av[5] && check_args(av[5]) == -1))
		return (0);
	if (!av[5])
	{
		info.nb_of_eating = -1;
	}
	else
		info.nb_of_eating = ft_atoi(av[5]);
	if (ft_atoi(av[1]) == 0)
		return (0);
	info.nb_of_philo = ft_atoi(av[1]);
	info.time_to_die = ft_atoi(av[2]);
	info.time_to_eat = ft_atoi(av[3]);
	info.time_to_sleep = ft_atoi(av[4]);
	philosopher(info);
	return (0);
}
