/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 13:13:29 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int read_hd_line(t_heredoc *hd, t_minishell *bash)
{
	char	*line;
    (void)  *bash;

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
		if ((ft_strncmp(line, hd->eo_heredoc, ft_strlen(hd->eo_heredoc)) == 0) \
			&& (ft_strlen(hd->eo_heredoc) == ft_strlen(line)))
		{
			free(line);
			return (0);
		}
		if (hd->status == NO_QUOTE)
			check_exp_in_hd(&line, bash);
		write(hd->fd_heredoc, line, ft_strlen(line));
		write(hd->fd_heredoc, "\n", 1);
		free(line);
	}
	return (0);
}
void free_recursion(char *x, char *y, char *z, char **temp, char *a)
{
	if (!a)
		a = "";
	if (!y)
		y = "";
	*temp = ft_strjoin(a, y);
	free(x);
	free(y);
	free(z);
}

void check_exp_in_hd(char **line, t_minishell *bash)
{
	char    *new_line;
    char    *after;
    char    *before;
    char    *expand;
    char    *env_var;
    char    *sobra;
    char    *temp_after;
    char    *temp_new_line;
    t_envp  *aux_exp;

    aux_exp = bash->envp;
    new_line = *line;
    after = NULL;
    before = NULL;
    if (split_string(*line, &before, &after, '$'))
    {
		env_var = envp_name(after);
        sobra = ft_substr(after, ft_strlen(env_var), ft_strlen(after) - ft_strlen(env_var));
        expand = ft_getenv(aux_exp, env_var);
		free_recursion(after, sobra, env_var, &temp_after, expand);
        after = temp_after;
        check_exp_in_hd(&after, bash);
		free_recursion(before, after, new_line, &temp_new_line, before);
        *line = temp_new_line;
    }
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
