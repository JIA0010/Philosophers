/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:28:04 by yoshimurahi       #+#    #+#             */
/*   Updated: 2024/02/08 11:38:13 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    check_argv(char **argv)
{   	
    int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (!(argv[i][j] >= '0' || argv[i][j] <= '9'))
				return (printf("invalid input"), false);
			j++;
		}
		i++;
	}
	return (true);
}

int main(int argc, char **argv)
{
    t_data data;

    if(argc < 5 || argc > 6)
        return (printf("error: wrong number of arguments\n"), 1);
    if(check_argv(argv) == false)
        return (1);
    if(init_main(&data, argc, argv) == false)
        return (1);
    if(start_philo(&data) == false)
        return (1);
	ft_exit(&data);
    return (0);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q philo");
// }