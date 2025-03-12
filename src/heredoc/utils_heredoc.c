/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/11 18:34:46 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	child_status(int hd_exit_status)
{
	if (WIFEXITED(hd_exit_status))
		return (WEXITSTATUS(hd_exit_status));
	else if (WIFSIGNALED(hd_exit_status))
	{
		if (WTERMSIG(hd_exit_status) == SIGINT)
		{
			return (EXIT_SIGINT);
		}
		else if (WTERMSIG(hd_exit_status) == SIGQUIT)
		{
			return (EXIT_SIGQUIT);
		}
	}
	return (0);
}

void	go_write(int fd_hd, char *line)
{
	write(fd_hd, line, ft_strlen(line));
	write(fd_hd, "\n", 1);
	free(line);
}

int	read_hd_line(t_heredoc *hd, t_minishell *bash)
{
	char	*line;

	(void)	*bash;
	while (1)
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
		if ((ft_strncmp(line, hd->eo_heredoc, ft_strlen(hd->eo_heredoc)) == 0) \
			&& (ft_strlen(hd->eo_heredoc) == ft_strlen(line)))
		{
			free(line);
			return (0);
		}
		if (hd->status == NO_QUOTE)
			check_exp_in_hd(&line, bash);
		go_write(hd->fd_heredoc, line);
	}
	return (0);
}

int	checked_for_hd(t_token *token)
{
	t_token	*aux;

	aux = token;
	while (aux && aux->prev)
	{
		if ((aux->type == WORD || aux->type == BLANK || aux->type == EXP_ENVP) \
			&& (aux->prev->type == HEREDOC))
		{
			token->type = WORD;
			return (1);
		}
		aux = aux->prev;
	}
	return (0);
}
