/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:30:05 by jdefayes          #+#    #+#             */
/*   Updated: 2023/10/07 17:56:24 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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

int	check_nb_of_arg(int ac)
{
	if (ac < 5)
	{
		printf("Not enough args.\n");
		return (1);
	}
	if (ac > 6)
	{
		printf("Too many args.\n");
		return (1);
	}
	return (0);
}
