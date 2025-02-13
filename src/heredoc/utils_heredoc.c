/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/13 20:15:52 by cmoura-p         ###   ########.fr       */
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
        if (ft_strncmp(line, hd->eo_heredoc, ft_strlen(hd->eo_heredoc)) == 0)
		{
			free(line);
			return (0);
		}
        check_expand_in_hd(line, bash);
//      aqui tem uma avaliacao para expansao dentro do heredoc
//		if (tmp_hd->eof_quote == NO_QUOTE)
//			check_hd_expand(&line, bash);
		write(hd->fd_heredoc, line, ft_strlen(line));
		write(hd->fd_heredoc, "\n", 1);
		free(line);
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
//			write(STDOUT_FILENO, "\n", 1);
			return (EXIT_SIGINT);
		}
		else if (WTERMSIG(hd_exit_status) == SIGQUIT)
		{
//			write(STDOUT_FILENO, "Quit\n", 5);
			return (EXIT_SIGQUIT);
		}
	}
	return (0);
}
void    check_expand_in_hd(char **line, t_minishell *bash)
{
    char    *new_line;

    new_line = check_dquote(bash, *line);
    free(*line);
    *line = new_line;
}
