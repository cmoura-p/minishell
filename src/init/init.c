/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:42:58 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/17 19:42:56 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_minishell	*init_data(char **envp, char **prompt)
{
	t_minishell	*bash;
	char		*pwd;
	(void)envp;			// por enquanto

	bash = ft_calloc(sizeof(t_minishell), 1);
	if (!bash)
		exit(1);
	init_signals();
	pwd = getenv("PWD");
	if (!pwd)
		pwd = "erro pwd ";
	*prompt = ft_strjoin(pwd, ": ");
	if (!(prompt))
		*prompt = pwd;
	// inicializa a struct do minishell
	return (bash);
}

int	init_bash(char **cmd_line, char *prompt)
{
	*cmd_line = readline(prompt);
	if (!(*cmd_line))
		return (0);
	add_history(*cmd_line);
	if (!(check_syntax(*cmd_line)))
		return (0);
	return (1);
}

void	init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}
