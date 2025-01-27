/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:57:24 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/26 19:51:08 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	t_minishell		*minishell;

	(void)av;
	if (ac != 1)
	{
		ft_printf("Minishell: argument is not allowed -> %s \n", av[1]);
		exit(SUCCESS);
	}
	minishell = init_data(envp, &prompt);
	while (1)
	{
		if (init_bash(minishell, prompt))
		{
			if (minishell->cmd_line[0] != '\0')
				run(minishell);
		}
		else
			if (!minishell->cmd_line)
				break ;
		if (minishell->cmd_line)
			free(minishell->cmd_line);
	}
	free_to_quit(minishell, prompt);
	return (0);
}
