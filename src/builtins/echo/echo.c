/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:22:22 by brendon           #+#    #+#             */
/*   Updated: 2025/01/22 01:55:34 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_flagverify(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (args[i])
	{
		if (ft_flagverify(args[i]))
			trigger = 1;
		else
			break ;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!trigger)
		ft_printf("\n");
}
