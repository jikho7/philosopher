/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:30:10 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 15:35:56 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	if (ac < 5)
	{
		printf("Not enough args.\n");
		return (0);
	}
	if (!av[5])
		av[5] = "100000";//MAXINT
	if (check_args(av[1]) == -1 || check_args(av[2]) == -1
		|| check_args(av[3]) == -1 || check_args(av[4]) == -1
		|| check_args(av[5]) == -1)
		return (0);
	philosopher(ft_atoi(av[1]), ft_atoi(av[2]), ft_atoi(av[3]),
		ft_atoi(av[4]), ft_atoi(av[5]));
	return (0);
}
