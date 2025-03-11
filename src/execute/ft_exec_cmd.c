/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:40:14 by breda-si          #+#    #+#             */
/*   Updated: 2025/03/11 10:56:09 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <errno.h>

static	void	exec_child_process(t_minishell *minishell, t_exec *cmd)
{
	char	*path;
	char	**env;

	path = ft_find_path(minishell, cmd->args[0]);
	if (!path)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->args[0]);
		free_exit(&minishell, 127);
	}
	env = ft_env_args(minishell->envp);
	if (!env)
	{
		perror("minishell: failed to allocate env");
		free(path);
		free_exit(&minishell, 1);
	}
	execve(path, cmd->args, env);
	perror("minishell");
	free(path);
	free_args(env);
	if (errno == EACCES)
		free_exit(&minishell, 126);
	free_exit(&minishell, 127);
}

void	ft_exec_cmd(t_minishell *minishell, t_exec *cmd)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_is_builtin(cmd->args[0]))
	{
		ft_exec_builtin(minishell, cmd->args);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(minishell, cmd);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		else
			minishell->exit_status = 1;
	}
	else
		perror("fork");
}
