/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:04:23 by brendon           #+#    #+#             */
/*   Updated: 2025/04/14 16:38:23 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		free(path);
	free(oldpwd);
}

void	ft_cd(t_minishell *minishell, char **args)
{
	char	*oldpwd;
	char	*path;

	oldpwd = ft_getenv(minishell->envp, "PWD");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if (args == NULL || args[0] == NULL)
		path = ft_getenv(minishell->envp, "HOME");
	else if (args[1])
		return (handle_cd_error(minishell, args, oldpwd, NULL));
	else if (ft_strcmp(args[0], "-") == 0)
		path = ft_getenv(minishell->envp, "OLDPWD");
	else if (args[0][0] == '-' && args[0][1] != '\0')
		return (handle_cd_error(minishell, args, oldpwd, NULL));
	else
		path = ft_strdup(args[0]);
	if (!path || chdir(path) == -1)
		return (handle_cd_error(minishell, args, oldpwd, path));
	minishell->exit_status = 0;
	att_pwdold(minishell, oldpwd);
	if (args && args[0] && ft_strcmp(args[0], "-") == 0)
		ft_printf("%s\n", path);
	free(oldpwd);
	if (path)
		free(path);
}
