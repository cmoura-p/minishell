/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:33:00 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/05 20:13:31 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc(t_minishell *bash)
{
	pid_t		pid;
	t_heredoc	*hd_node;
	char		*c;
    int         status;

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
//		vai buscar o status do precesso filho
//		se for ctrl+c tem que lidar pq foi abortado
//      todo heredoc e fazer return
		hd_node = hd_node->next;
	}
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
