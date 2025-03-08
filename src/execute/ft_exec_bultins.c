/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bultins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:37:42 by brendon           #+#    #+#             */
/*   Updated: 2025/03/04 23:40:10 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	ft_exec_builtin(t_minishell *minishell, char **args)
{
	if (!args || !args[0])
		return ;
	if (strcmp(args[0], "cd") == 0)
		ft_cd(minishell, &args[1]);
	else if (strcmp(args[0], "echo") == 0)
		ft_echo(minishell, &args[1]);
	else if (strcmp(args[0], "env") == 0)
		ft_env(minishell, &args[1]);
	else if (strcmp(args[0], "exit") == 0)
		ft_exit(minishell, &args[1]);
	else if (strcmp(args[0], "export") == 0)
		ft_export(minishell, &args[1]);
	else if (strcmp(args[0], "pwd") == 0)
		ft_pwd(minishell, &args[1]);
	else if (strcmp(args[0], "unset") == 0)
		ft_unset(minishell, &args[1]);
}
