/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:57:24 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/22 20:25:12 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	test_builtin(t_minishell *bash)
{
	t_exec	exec;

	exec.args = ft_split(bash->cmd_line, ' ');
	if (!exec.args)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(bash->cmd_line, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	printf("args[0]: %s\n", exec.args[0]);
	if (exec.args[0] && !ft_strcmp(exec.args[0], "cd"))
		ft_cd(bash, &exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "echo"))
		ft_echo(&exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "env"))
		ft_env(bash, &exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "exit"))
		ft_exit(bash, &exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "export"))
		ft_export(bash, &exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "pwd"))
		ft_pwd(bash, &exec.args[1]);
	else if (exec.args[0] && !ft_strcmp(exec.args[0], "unset"))
		ft_unset(bash, &exec.args[1]);
	free(exec.args);
}

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
		if (init_bash(minishell, prompt) != 0)
		{
			if (minishell->cmd_line[0] != '\0')
			{
				run(minishell);
				
			}
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
