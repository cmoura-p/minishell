/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:42:44 by brendon           #+#    #+#             */
/*   Updated: 2025/04/07 10:09:26 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_exit(t_minishell **minishell, int exit_code)
{
	if ((*minishell)->root)
		ft_free_tree((*minishell)->root);
	free_bash(*minishell);
	rl_clear_history();
	exit(exit_code);
}

int	verify_ll(char *str)
{
	if (ft_strlen(str) > 20 || (ft_strlen(str) == 20 && str[0] != '-'))
		return (0);
	if (ft_strlen(str) < 19)
		return(1);
	if (ft_strlen(str) == 19 && ft_strcmp(str, "9223372036854775807") <= 0)
		return (1);
	if (ft_strlen(str) == 20
		&& ft_strcmp(str, "-9223372036854775808") <= 0)
		return (1);
	return (0);
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
		ft_fprintf(STDERR_FILENO, "exit\n");
		free_exit(&minishell, 0);
	}
	exit_code = 0;
	if (ft_strisdigit(args[0]) && verify_ll(args[0]) && !args[1])
	{
		exit_code = ft_atoi_int(args[0]) % 256;
		if (exit_code < 0)
			exit_code += 256;
		ft_fprintf(STDOUT_FILENO, "exit\n");
		free_exit(&minishell, exit_code);
	}
	if ((!ft_strisdigit(args[0]) || !verify_ll(args[0])))
	{
		ft_fprintf(STDERR_FILENO,
			"exit\nminishell: exit: %s: numeric argument required\n", args[0]);
		free_exit(&minishell, 2);
	}
	minishell->exit_status = 1;
	ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
}
