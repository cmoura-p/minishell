/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:37:27 by brendon           #+#    #+#             */
/*   Updated: 2025/03/04 23:40:25 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	exec_redir_in(t_minishell *minishell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: input redirection failed");
		minishell->exit_status = 1;
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: input redirection failed");
		close(fd);
		minishell->exit_status = 1;
		return ;
	}
	close(fd);
}

static	void	exec_redir_out(t_minishell *minishell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: output redirection failed");
		minishell->exit_status = 1;
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: output redirection failed");
		close(fd);
		minishell->exit_status = 1;
		return ;
	}
	close(fd);
}

static	void	exec_redir_app(t_minishell *minishell, t_redir *redir)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: append redirection failed");
		minishell->exit_status = 1;
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: append redirection failed");
		close(fd);
		minishell->exit_status = 1;
		return ;
	}
	close(fd);
}

void	ft_exec_redir(t_minishell *minishell, t_redir *redir)
{
	int	tmp_stdout;
	int	tmp_stdin;

	tmp_stdout = dup(STDOUT_FILENO);
	tmp_stdin = dup(STDIN_FILENO);
	if (redir->type == REDIR_IN)
		exec_redir_in(minishell, redir);
	else if (redir->type == REDIR_OUT)
		exec_redir_out(minishell, redir);
	else if (redir->type == REDIR_APP)
		exec_redir_app(minishell, redir);
	ft_execute(minishell, redir->next);
	dup2(tmp_stdout, STDOUT_FILENO);
	dup2(tmp_stdin, STDIN_FILENO);
	close(tmp_stdout);
	close(tmp_stdin);
}
