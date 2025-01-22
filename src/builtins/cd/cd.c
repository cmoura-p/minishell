/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:04:23 by brendon           #+#    #+#             */
/*   Updated: 2025/01/20 08:57:27 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_check_args(t_minishell *bash, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 0)
	{
		chdir(ft_getenv(bash->envp, "HOME"));
		return (0);
	}
	if (i > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (args[0][0] == '-' && args[0][1] != '\0')
	{
		printf("minishell: cd: %s: invalid option\n", args[0]);
		return (1);
	}
	return (0);
}

void	ft_cd(t_minishell *minishell, char **args)
{
	char	*oldpwd;

	if (ft_check_args(minishell, args))
		return ;
	oldpwd = ft_getenv(minishell->envp, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		return ;
	}
	ft_expoinsert(&minishell->export, ft_exponew("PWD", args[0]));
	ft_envadd(&minishell->envp, ft_exponew("PWD", args[0]));
}
