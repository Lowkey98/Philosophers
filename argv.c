/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayafdel <ayafdel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:40:11 by ayafdel           #+#    #+#             */
/*   Updated: 2022/03/05 11:48:19 by ayafdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int fetch_argv_data(t_argv **argv_data, char **argv)
{

	*argv_data = malloc(sizeof(t_argv));
	if (*argv_data == NULL)
		return (1);	
	(*argv_data)->number_of_philo = ft_atoi(argv[1]);
	(*argv_data)->time_to_die = ft_atoi(argv[2]);
	(*argv_data)->time_to_eat = ft_atoi(argv[3]);
	(*argv_data)->time_to_sleep = ft_atoi(argv[4]);
	(*argv_data)->number_of_eats = -1;
	if (argv[5])
		(*argv_data)->number_of_eats = ft_atoi(argv[5]);
	return (0);
}
int		arg_error(char *str)
{
	int i;

	i = 0;
	if (str[0] == '0' || str[0] == '\0')
		return (1);

	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
	// printf("%s\n", str);
	return (1);
}

int     args_error(char **argv, int argc)
{
	int i;
	int j;

	j = 0;
	i = 1;
	
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		if (arg_error(argv[i]))
			return (1);
		i++;
	}
	return (0);
}