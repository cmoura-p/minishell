/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:28 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/05 18:26:02 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_sobra_out(t_help_recursion *aux_hr, char **temp)
{
	if (!aux_hr->before)
		aux_hr->before = "";
	if (!aux_hr->after)
		aux_hr->after = "";
	*temp = ft_strjoin(aux_hr->before, aux_hr->after);
	if (aux_hr->after)
	{
		free(aux_hr->after);
		aux_hr->after = NULL;
	}
	if (aux_hr->before)
	{
		free(aux_hr->before);
		aux_hr->before = NULL;
	}
	if (aux_hr->new_line)
	{
		free(aux_hr->new_line);
		aux_hr->new_line = NULL;
	}
}

void	join_sobra_in(t_help_recursion *aux_hr, char *expand, char **temp)
{
	if (!aux_hr->sobra)
		aux_hr->sobra = "";
	if (!expand)
		expand = "";
	*temp = ft_strjoin(expand, aux_hr->sobra);
	if (aux_hr->after)
	{
		free(aux_hr->after);
		aux_hr->after = NULL;
	}
	if (aux_hr->sobra)
	{
		free(aux_hr->sobra);
		aux_hr->sobra = NULL;
	}
	if (aux_hr->env_var)
	{
		free(aux_hr->env_var);
		aux_hr->env_var = NULL;
	}
}

void	check_exp_in_hd(char **line, t_minishell *bash)
{
	t_help_recursion	*aux_hr;
	char				*expand;
	char				*temp_after;
	char				*temp_new_line;
	t_envp				*aux_exp;

	aux_exp = bash->envp;
	aux_hr = malloc(sizeof(t_help_recursion));
	if (!aux_hr)
		return ;
	aux_hr->new_line = *line;
	aux_hr->after = NULL;
	aux_hr->before = NULL;
	if (split_string(*line, &aux_hr->before, &aux_hr->after, '$'))
	{
		aux_hr->env_var = envp_name(aux_hr->after);
		aux_hr->sobra = ft_substr(aux_hr->after, ft_strlen(aux_hr->env_var), \
		ft_strlen(aux_hr->after) - ft_strlen(aux_hr->env_var));
		expand = ft_getenv(aux_exp, aux_hr->env_var);
		join_sobra_in(aux_hr, expand, &temp_after);
		aux_hr->after = temp_after;
		check_exp_in_hd(&aux_hr->after, bash);
		join_sobra_out(aux_hr, &temp_new_line);
		*line = temp_new_line;
	}
	free(aux_hr);
}
