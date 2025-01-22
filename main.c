/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:57:24 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/22 20:10:55 by brendon          ###   ########.fr       */
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
		ft_printf("Minishell: argument is not allowed -> %s \n", av[1]);// tem que ser na saida padrao de erro? (STDERR_FILENO)
		exit(0);  //return com mensagem de erro
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
