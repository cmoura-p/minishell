/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:44 by brendon           #+#    #+#             */
/*   Updated: 2025/01/22 01:43:54 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_exit(t_minishell **minishell, int exit_code)
{
	free_bash(*minishell);
	rl_clear_history();
	exit(exit_code);
}

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

void	ft_exit(t_minishell *minishell, char **args)
{
	int	exit_code;

	if (!args || !args[0] || !args[0][0])
	{
		printf("exit\n");
		free_exit(&minishell, 0);
	}
	exit_code = 0;
	if (args[1])
	{
		ft_printf("minishell: exit: too many arguments\n");
		free_exit(&minishell, 2);
	}
	if (ft_strisdigit(args[0]))
	{
		exit_code = ft_atoi_int(args[0]) % 256;
		if (exit_code < 0)
			exit_code += 256;
		printf("exit\n");
		free_exit(&minishell, exit_code);
	}
	else
		ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
}
