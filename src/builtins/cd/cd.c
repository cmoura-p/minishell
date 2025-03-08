/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:04:23 by brendon           #+#    #+#             */
/*   Updated: 2025/02/25 16:15:57 by breda-si         ###   ########.fr       */
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
		bash->exit_status = 0;
		chdir(ft_getenv(bash->envp, "HOME"));
		return (0);
	}
	if (i > 1)
	{
		bash->exit_status = 1;
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (args[0][0] == '-' && args[0][1] != '\0')
	{
		bash->exit_status = 1;
		printf("minishell: cd: %s: invalid option\n", args[0]);
		return (1);
	}
	return (0);
}

void	att_pwdold(t_minishell *minishell, char *oldpwd)
{
	ft_expoinsert(&minishell->export, ft_exponew("PWD", getcwd(NULL, 0)));
	ft_envadd(&minishell->envp, ft_exponew("PWD", getcwd(NULL, 0)));
	ft_expoinsert(&minishell->export, ft_exponew("OLDPWD", oldpwd));
	ft_envadd(&minishell->envp, ft_exponew("OLDPWD", oldpwd));
}

void	handle_cd_error(t_minishell *minishell, char **args, char *oldpwd)
{
	if (!args || !args[0])
		ft_printf("minishell: cd: HOME not set\n");
	else
		ft_printf("minishell: cd: %s: No such file or directory\n",
			args[0]);
	minishell->exit_status = 1;
	free(oldpwd);
}

void	ft_cd(t_minishell *minishell, char **args)
{
	char	*oldpwd;
	char	*path;

	path = args[0];
	oldpwd = ft_strdup(ft_getenv(minishell->envp, "PWD"));
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (!args || !args[0])
		path = ft_getenv(minishell->envp, "HOME");
	else if (ft_strcmp(args[0], "-") == 0)
		path = ft_getenv(minishell->envp, "OLDPWD");
	else if (ft_check_args(minishell, args))
		return (free(oldpwd));
	if (!path || chdir(path) == -1)
		return (handle_cd_error(minishell, args, oldpwd));
	minishell->exit_status = 0;
	att_pwdold(minishell, oldpwd);
	free(oldpwd);
}
