/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:40:14 by breda-si          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:43 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_execperror(char *str, char *cmd)
{
	ft_fprintf(STDERR_FILENO, "%s: %s: ", str, cmd);
	perror("");
}

void	fork_siginal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
	}
	else
		signal(SIGINT, signal_handler);
}

void	ft_exit_status(t_minishell *minishell, int status)
{
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			minishell->exit_status = 130;
			printf("\n");
		}
		else
			minishell->exit_status = 128 + WTERMSIG(status);
	}
	else
		minishell->exit_status = 1;
}

static	void	exec_child_process(t_minishell *minishell, t_exec *cmd)
{
	char	*path;
	char	**env;

	signal(SIGINT, signal_handler);
	path = ft_find_path(minishell, cmd->args[0]);
	if (!path || cmd->args[0][0] == '\0')
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
	ft_execperror("minishell", cmd->args[0]);
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
		return (ft_exec_builtin(minishell, cmd->args));
	fork_siginal(0);
	pid = fork();
	if (pid == 0)
		exec_child_process(minishell, cmd);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		ft_exit_status(minishell, status);
	}
	else
		perror("fork");
	fork_siginal(1);
}
