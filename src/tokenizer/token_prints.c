/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:00:13 by dramos-j          #+#    #+#             */
/*   Updated: 2025/02/09 09:36:46 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*format_data_parentheses(const char *data)
{
	size_t	len;
	char	*formatted;

	len = ft_strlen(data);
	formatted = malloc(len + 3);
	if (!formatted)
		return ("(allocation failed)");
	formatted[0] = '(';
	ft_strcpy(formatted + 1, (char *)data);
	formatted[len + 1] = ')';
	formatted[len + 2] = '\0';
	return (formatted);
}

const char	*get_token_type_str(enum e_type type)
{
	if (type == WORD)
		return ("Word");
	else if (type == BLANK)
		return ("Blank");
	else if (type == PIPE)
		return ("Pipe");
	else if (type == REDIR_IN)
		return ("Redir in");
	else if (type == REDIR_APP)
		return ("Redir append");
	else if (type == REDIR_OUT)
		return ("Redir out");
	else if (type == FILE_IN)
		return ("File in");
	else if (type == FILE_APP)
		return ("File append");
	else if (type == FILE_OUT)
		return ("File out");
	else if (type == HEREDOC)
		return ("Heredoc");
	else if (type == S_QUOTE)
		return ("Single Quote");
	else if (type == D_QUOTE)
		return ("Double Quote");
	else if (type == EXP_EXIT)
		return ("Exp exit code");
	else if (type == EXP_ENVP)
		return ("Exp var");
	else if (type == COMMAND)
		return ("Command");
	else if (type == ARGUMENT)
		return ("Argument");
	else if (type == EXP_NULL)
		return ("Expand NULL");
	else if (type == BUILTIN)
		return ("Built-ins");
	else
		return ("Unknown");
}

const char	*get_token_quote_str(enum e_status quote)
{
	if (quote == NO_QUOTE)
		return ("No quote");
	else if (quote == SINGLE_Q)
		return ("Single");
	else if (quote == DOUBLE_Q)
		return ("Double");
	return ("Unknown");
}

void	print_token_list(t_token *token)
{
	t_token	*aux;
	int		index;
	char	*formatted_data;

	printf("+-------+----------------------------------------------------+----------------------+------------+\n");
	printf("| Index | Data                                               | Type                 | Quote      |\n");
	printf("+-------+----------------------------------------------------+----------------------+------------+\n");
	aux = token;
	index = 0;
	while (aux)
	{
		formatted_data = aux->name ? format_data_parentheses(aux->name) : NULL;
		printf("| %-5d | %-50.50s | %-20.15s | %-10.10s |\n",
			index,
			formatted_data,
			get_token_type_str(aux->type),
			get_token_quote_str(aux->status));
		printf("+-------+----------------------------------------------------+----------------------+------------+\n");
		if ((formatted_data != NULL) && (ft_strcmp(formatted_data, "(null)") != 0))
			free(formatted_data);
		aux = aux->next;
		index++;
	}
}
