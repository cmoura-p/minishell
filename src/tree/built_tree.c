/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:48:17 by brendon           #+#    #+#             */
/*   Updated: 2025/03/03 11:48:18 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_pipe(t_token *start, t_token *aux, t_minishell *bash)
{
	t_pipe	*pipe;
	t_token	*left;
	t_token	*right;

	if (!aux || !aux->next)
		return (NULL);
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	left = start;
	right = aux->next;
	if (aux->prev)
		aux->prev->next = NULL;
	if (aux->next)
		aux->next->prev = NULL;
	free_token(aux);
	pipe->type = PIPE;
	pipe->left = ft_tree(left, bash);
	pipe->right = ft_tree(right, bash);
	return (pipe);
}

void	*ft_redir_in(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || !aux->next || !aux->prev)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_IN;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_RDONLY);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		bash->exit_status = 1;
		free(redir->file_name);
		free(redir);
		return (NULL);
	}
	ft_remove_tokens(aux);
	redir->next = ft_tree(start, bash);
	return (redir);
}

void	*ft_redir_out(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || !aux->next || !aux->prev)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_OUT;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		bash->exit_status = 1;
		free(redir->file_name);
		free(redir);
		return (NULL);
	}
	ft_remove_tokens(aux);
	redir->next = ft_tree(start, bash);
	return (redir);
}

void	*ft_redir_app(t_token *start, t_token *aux, t_minishell *bash)
{
	t_redir	*redir;

	if (!aux || !aux->next || !aux->prev)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_APP;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		bash->exit_status = 1;
		free(redir->file_name);
		free(redir);
		return (NULL);
	}
	ft_remove_tokens(aux);
	redir->next = ft_tree(start, bash);
	return (redir);
}

void	*ft_tree(t_token *start, t_minishell *bash)
{
	t_token	*aux;

	if (!start)
		return (NULL);
	aux = find_token_by_type(start, PIPE);
	if (aux)
		return (handle_pipe(start, aux, bash));
	aux = find_token_by_type(start, REDIR_IN);
	if (aux)
		return (handle_redir_in(start, aux, bash));
	aux = find_token_by_type(start, REDIR_OUT);
	if (aux)
		return (handle_redir_out(start, aux, bash));
	aux = find_token_by_type(start, REDIR_APP);
	if (aux)
		return (handle_redir_app(start, aux, bash));
	return (handle_command(start));
}
