/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:44 by brendon           #+#    #+#             */
/*   Updated: 2025/01/07 19:44:09 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strisdigit(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_code;

	if (!args[1])
	{
		printf("exit\n");
		free_exit(&minishell, 0);
	}
	exit_code = 0;
	if (args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		free_exit(&minishell, 2);
	}
	if (ft_strisdigit(args[1]))
	{
		exit_code = ft_atoi(args[1]) % 256;
		if (exit_code < 0)
			exit_code += 256;
		free_exit(&minishell, exit_code);
	}
	else
		ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
}

