/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:57:24 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/23 01:08:59 by cmoura-p         ###   ########.fr       */
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
		ft_printf("Minishell: argument is not allowed -> %s \n", av[1]);  // tem que ser na saida padrao de erro? (STDERR_FILENO)
		exit(0);  //return com mensagem de erro
	}
	prompt = NULL;
	init_data(&minishell, envp, &prompt);
	while (1)
	{
		if ((init_bash(minishell, prompt)))
		{
			if (minishell->cmd_line[0] != '\0')
				ft_printf("%s \n", minishell->cmd_line);	// aqui vai o parsing
		}
		else
			if (!minishell->cmd_line)
				break;
		free_line(&minishell);
	}
	free_it_all(&minishell);
	return (0);
}
