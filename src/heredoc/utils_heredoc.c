/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/28 00:33:04 by cmoura-p         ###   ########.fr       */
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
		| O_RDWR | O_TRUNC, 0644 );
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

void    check_exp_in_hd(char **line, t_minishell *bash)
{
    char    *new_line;
    char    *after;
    char    *before;
    char    *expand;
	char	*env_var;
    char    *sobra;
    t_envp  *aux_exp;

    after = NULL;
    before = NULL;
    new_line = *line;
    aux_exp = bash->envp;
    if (split_string(*line, &before, &after, '$'))
    {
        env_var = envp_name(after);
        sobra = ft_substr((after), (ft_strlen(env_var)), \
			(ft_strlen(after)-1));
	    expand = ft_getenv(aux_exp, env_var);
        after = ft_strjoin(expand, sobra);
		free(sobra);
		free(env_var);
		check_exp_in_hd(&after, bash);
        new_line = ft_strjoin(before, after);
    }
    *line = new_line;
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
