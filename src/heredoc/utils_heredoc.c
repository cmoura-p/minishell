/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/12 11:21:01 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_heredoc(t_heredoc *hd, t_minishell *bash)
{
	int status;

	set_heredoc_signals();
	while(1)
	{
		hd->fd_heredoc = open(hd->hd_path, O_CREAT \
		| O_RDWR | O_TRUNC, 064 );
		status = read_hd_line(hd, bash);
		if (status == 1)
			printf("warning: heredoc aborted - expected eof %s \n", hd->eo_heredoc);
		close(hd->fd_heredoc);
//		tem que ter free por aqui
		if (status == 0 || status == 1)
			exit(0);
		if (status == 2)
			exit(EXIT_SIGINT);
	}
}

int read_hd_line(t_heredoc *hd, t_minishell *bash)
{
	char	*line;
	(void)	*hd;
	(void)	*bash;

	while(1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			if (g_signal == SIGINT)
				return (2);
			else
				return (1);
		}
//		aqui tem linha para ser tratada
	}
	return (0);
}
int	child_status(int hd_exit_status)
{
	if (WIFEXITED(hd_exit_status))
		return (WEXITSTATUS(hd_exit_status));
	else if (WIFSIGNALED(hd_exit_status))
	{
		if (WTERMSIG(hd_exit_status) == SIGINT)
		{
//			ft_printf(1, "\n");
			return (EXIT_SIGINT);
		}
		else if (WTERMSIG(hd_exit_status) == SIGQUIT)
		{
//			ft_printf(1, "Quit (core dumped)\n");
			return (EXIT_SIGQUIT);
		}
	}
	return (0);
}
