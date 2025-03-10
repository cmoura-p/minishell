/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:12:36 by brendon           #+#    #+#             */
/*   Updated: 2025/03/10 16:08:52 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_minishell *minishell, char **args)
{
	char	*pwd;

	minishell->exit_status = 0;
	if (args && args[0] && args[0][0] == '-' && args[0][1] != '\0')
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: %s: invalid option\n",
			args[0]);
		minishell->exit_status = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: pwd: ERROR\n");
		minishell->exit_status = 1;
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}
	//é preciso tratar o erro