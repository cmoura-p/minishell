/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:37:33 by brendon           #+#    #+#             */
/*   Updated: 2025/04/03 18:26:54 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_left_child(t_minishell *minishell, t_pipe *pipeline, int *fd)
{
	signal(SIGINT, signal_handler);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execute(minishell, pipeline->left);
	free_exit(&minishell, minishell->exit_status);
}

void	exec_right_child(t_minishell *minishell, t_pipe *pipeline, int *fd)
{
	signal(SIGINT, signal_handler);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execute(minishell, pipeline->right);
	free_exit(&minishell, minishell->exit_status);
}

void	ft_exec_pipe(t_minishell *minishell, t_pipe *pipeline)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	pid_left = fork();
	if (pid_left == 0)
		exec_left_child(minishell, pipeline, fd);
	pid_right = fork();
	if (pid_right == 0)
		exec_right_child(minishell, pipeline, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	minishell->exit_status = WEXITSTATUS(status);
	signal(SIGINT, signal_handler);
}
