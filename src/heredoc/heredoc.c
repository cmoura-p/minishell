/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:15:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/11 23:55:09 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc(t_minishell *bash)
{
	pid_t		pid;
	t_heredoc	*hd_node;
	char		*c;
	int			status;

	hd_node = bash->heredoc;
	create_hd_list(bash);
	while (hd_node)
	{
		c = ft_itoa(hd_node->counter);
		hd_node->hd_path = ft_strjoin("/tmp/temp_heredoc", c);
		free(c);
		pid = fork();
		if (pid == 0)
			set_heredoc(hd_node, bash);
		waitpid(pid, &status, 0);
		if (child_status(status) == EXIT_SIGINT)
		{
			heredoc_ctrl_c(bash);
			return ;
		}
		hd_node = hd_node->next;
	}
	change_hd_tokens(bash);
}

int	set_heredoc(t_heredoc *hd, t_minishell *bash)
{
	int	status;

	set_heredoc_signals();
	while (1)
	{
		hd->fd_heredoc = open(hd->hd_path, O_CREAT \
		| O_RDWR | O_TRUNC, 0644);
		status = read_hd_line(hd, bash);
		if (status == 1)
			printf("warning: heredoc aborted - expected eof %s \n", \
			hd->eo_heredoc);
		close(hd->fd_heredoc);
		if (status == 0 || status == 1)
			free_exit(&bash, 0);
		if (status == 2)
			free_exit(&bash, SIGINT);
	}
}

void	add_heredoclst(t_heredoc **hd, char *name, enum e_status status_q)
{
	t_heredoc	*newhd;

	newhd = ft_calloc(1, sizeof(t_heredoc));
	if (!newhd)
		return ;
	while ((*hd)->next)
		(*hd) = (*hd)->next;
	newhd->fd_heredoc = 0;
	newhd->eo_heredoc = ft_strdup(name);
	newhd->hd_path = NULL;
	newhd->status = status_q;
	newhd->counter = ((*hd)->counter) + 1;
	newhd->next = NULL;
	(*hd)->next = newhd;
}

void	create_hd_list(t_minishell *bash)
{
	t_token		*token;
	t_heredoc	*hd_node;
	bool		first_time;

	first_time = true;
	token = bash->token;
	hd_node = bash->heredoc;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (first_time)
			{
				hd_node->eo_heredoc = ft_strdup(token->next->name);
				hd_node->status = token->next->status;
				first_time = false;
			}
			else
				add_heredoclst(&hd_node, token->next->name, \
				token->next->status);
		}
		token = token->next;
	}
}

void	change_hd_tokens(t_minishell *bash)
{
	t_token		*aux;
	t_heredoc	*hered;

	aux = bash->token;
	hered = bash->heredoc;
	while (aux)
	{
		if (aux->type == HEREDOC)
		{
			free(aux->next->name);
			aux->next->name = ft_strdup(hered->hd_path);
			aux->next->type = FILE_IN;
			aux->type = REDIR_IN;
			hered = hered->next;
		}
		aux = aux->next;
	}
}
