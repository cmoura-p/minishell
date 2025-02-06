/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:33:00 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/06 13:43:23 by cmoura-p         ###   ########.fr       */
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
//	em que posicao esta o hd agora?
	while (hd_node)
	{
		c = ft_itoa(hd_node->counter);
		hd_node->hd_path = ft_strjoin("/tmp/temp_heredoc", c);
		free(c);
        pid = fork();
        if (pid == 0)
            set_heredoc(hd_node, bash);
        waitpid(pid, &status, 0);
//		vai buscar o status do precesso filho, se for ctrl+c
//		tem que lidar pq foi abortado todo heredoc
//		e depois fazer return
		hd_node = hd_node->next;
	}
//	incluir o "/tmp/temp_heredoc#" nos tokens
//	como file In e type heredoc vira redir in
}
void	add_heredoclst(t_heredoc **hd,char *name, enum e_status status_q)
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
	newhd->counter = ((*hd)->counter)+1;
	newhd->next = NULL;
	(*hd)->next = newhd;
//	(*hd) = (*hd)->next;
}
void	create_hd_list(t_minishell *bash)
{
	t_token		*token;
	t_heredoc	*hd_node;
	bool		first_time;

	first_time = true;
	token = bash->token;
	hd_node = bash->heredoc;
	while(token)
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
				add_heredoclst(&hd_node, token->next->name, token->next->status);
		}
		token = token->next;
	}
}
