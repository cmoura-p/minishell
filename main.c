/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:57:24 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/18 23:53:14 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	char			*cmd_line;
	t_minishell		*minishell;
	(void)av;

	if (ac != 1)
	{
		ft_printf("Minishell: argument is not allowed -> %s \n", av[1]);  // tem que ser na saida padrao de erro? (STDERR_FILENO)
		exit(0);  //return com mensagem de erro
	}
	cmd_line = NULL;
	prompt = NULL;
	minishell = init_data(envp, &prompt);
	while (1)
	{
		if ((init_bash(&cmd_line, prompt)))
			ft_printf("%s \n", cmd_line);	// aqui vai o parsing
		else
			if (!cmd_line)
				break;
		free_necessary(&cmd_line, &minishell);
	}
	ft_clear_all(&minishell, &cmd_line);
	return (0);
}
