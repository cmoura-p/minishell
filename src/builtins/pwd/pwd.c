/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:12:36 by brendon           #+#    #+#             */
/*   Updated: 2025/01/20 08:44:09 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_minishell *minishell, char **args)
{
	char	*pwd;

	(void)minishell;
	if (args && args[0] && args[0][0] == '-' && args[0][1] != '\0')
	{
		ft_printf("minishell: pwd: %s: invalid option\n", args[0]);
		ft_printf("pwd: usage: pwd\n");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf("minishell: pwd: ERROR\n");
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}
	//é preciso tratar o erro