/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: breda-si <breda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:04:23 by brendon           #+#    #+#             */
/*   Updated: 2025/04/06 21:21:40 by breda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_check_args(t_minishell *bash, char **args)
{
	int		i;
	char	*path;

	i = 0;
	while (args[i])
		i++;
	if (i == 0)
	{
		path = ft_getenv(bash->envp, "HOME");
		bash->exit_status = 0;
		chdir(path);
		free(path);
	}
	if (i > 1)
	{
		bash->exit_status = 1;
		if (args[0][0] == '-' && (args[0][1] != '\0' ||
			(args[0][1] == '-' && args[0][2] == '\0')))
			ft_fprintf(STDERR_FILENO,
				"minishell: cd: %s: invalid option\n", args[0]);
		else
			ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

void	att_pwdold(t_minishell *minishell, char *oldpwd)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_expoinsert(&minishell->export, ft_exponew("PWD", tmp));
	ft_envadd(&minishell->envp, ft_exponew("PWD", tmp));
	ft_expoinsert(&minishell->export, ft_exponew("OLDPWD", oldpwd));
	ft_envadd(&minishell->envp, ft_exponew("OLDPWD", oldpwd));
	free(tmp);
}

void	handle_cd_error(t_minishell *minishell, char **args, char *oldpwd,
	char *path)
{
	struct stat	path_stat;

	if (!args || !args[0])
		ft_fprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
	else if (ft_strcmp(args[0], "-") == 0)
		ft_fprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
	else if (stat(args[0], &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: Not a directory\n",
			args[0]);
	else
		ft_fprintf(STDERR_FILENO,
			"minishell: cd: %s: No such file or directory\n",
			args[0]);
	minishell->exit_status = 1;
	if (path)
	{
		free(path);
		path = NULL;
	}
	free(oldpwd);
}

void	ft_cd(t_minishell *minishell, char **args)
{
	char	*oldpwd;
	char	*path;

	path = ft_strdup(args[0]);
	oldpwd = ft_getenv(minishell->envp, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (!args || !args[0])
		path = ft_getenv(minishell->envp, "HOME");
	else if (args && args[0] && (ft_strcmp(args[0], "-") == 0))
	{
		path = ft_getenv(minishell->envp, "OLDPWD");
		if (!path)
			handle_cd_error(minishell, args, oldpwd, NULL);
	}
	else if (ft_check_args(minishell, args))
		return (free(oldpwd));
	if (!path || !path[0] || chdir(path) == -1)
		return (handle_cd_error(minishell, args, oldpwd, path));
	minishell->exit_status = 0;
	att_pwdold(minishell, oldpwd);
	if (path)
		free(path);
	free(oldpwd);
}
