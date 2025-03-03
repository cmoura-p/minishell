#include "../../include/minishell.h"

char	**ft_env_args(t_envp *envp)
{
	char	**args;
	int		i;
	t_envp	*tmp;

	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		args[i] = malloc(strlen(tmp->name) + strlen(tmp->content) + 2);
		if (!args[i])
		{
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		sprintf(args[i], "%s=%s", tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	ft_exec_builtin(t_minishell *minishell, char **args)
{
	if (!args || !args[0])
		return ;
	if (strcmp(args[0], "cd") == 0)
		ft_cd(minishell, &args[1]);
	else if (strcmp(args[0], "echo") == 0)
		ft_echo(&args[1]);
	else if (strcmp(args[0], "env") == 0)
		ft_env(minishell, &args[1]);
	else if (strcmp(args[0], "exit") == 0)
		ft_exit(minishell, &args[1]);
	else if (strcmp(args[0], "export") == 0)
		ft_export(minishell, &args[1]);
	else if (strcmp(args[0], "pwd") == 0)
		ft_pwd(minishell, &args[1]);
	else if (strcmp(args[0], "unset") == 0)
		ft_unset(minishell, &args[1]);
}

char	*ft_find_path(char *cmd)
{
	char	*path;
	char	*full_path;
	char	**paths;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (strdup(cmd));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	ft_exec_cmd(t_minishell *minishell, t_exec *cmd)
{
	char	*path;
	char	**env;
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_is_builtin(cmd->args[0]))
	{
		ft_exec_builtin(minishell, cmd->args);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		path = ft_find_path(cmd->args[0]);
		if (!path)
		{
			fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
			exit(127);
		}
		env = ft_env_args(minishell->envp);
		if (!env)
		{
			perror("minishell: failed to allocate env");
			free(path);
			exit(1);
		}
		execve(path, cmd->args, env);
		perror("minishell");
		free(path);
		free_args(env);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
		else
			minishell->exit_status = 1;
	}
	else
	{
		perror("fork");
	}
}

void	ft_exec_pipe(t_minishell *minishell, t_pipe *pipeline)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	pid_left = fork();
	if (pid_left == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execute(minishell, pipeline->left);
		exit(0);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ft_execute(minishell, pipeline->right);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}

void	ft_exec_redir(t_minishell *minishell, t_redir *redir)
{
	int	fd;
	int	tmp_stdout;
	int	tmp_stdin;

	tmp_stdout = dup(STDOUT_FILENO);
	tmp_stdin = dup(STDIN_FILENO);
	if (redir->type == REDIR_IN)
	{
		fd = open(redir->file_name, O_RDONLY);
		if (fd == -1)
		{
			perror("minishell: input redirection failed");
			minishell->exit_status = 1;
			return ;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: input redirection failed");
			close(fd);
			minishell->exit_status = 1;
			return ;
		}
		close(fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("minishell: output redirection failed");
			minishell->exit_status = 1;
			return ;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: output redirection failed");
			close(fd);
			minishell->exit_status = 1;
			return ;
		}
		close(fd);
	}
	else if (redir->type == REDIR_APP)
	{
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell: append redirection failed");
			minishell->exit_status = 1;
			return ;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: append redirection failed");
			close(fd);
			minishell->exit_status = 1;
			return ;
		}
		close(fd);
	}
	ft_execute(minishell, redir->next);
	dup2(tmp_stdout, STDOUT_FILENO);
	dup2(tmp_stdin, STDIN_FILENO);
	close(tmp_stdout);
	close(tmp_stdin);
}

void	ft_execute(t_minishell *minishell, void *root)
{
	if (!root)
		return ;
	if (((t_pipe *)root)->type == PIPE)
		ft_exec_pipe(minishell, (t_pipe *)root);
	else if (((t_redir *)root)->type == REDIR_IN
		|| ((t_redir *)root)->type == REDIR_OUT
		|| ((t_redir *)root)->type == REDIR_APP)
		ft_exec_redir(minishell, (t_redir *)root);
	else if (((t_exec *)root)->type == COMMAND)
		ft_exec_cmd(minishell, (t_exec *)root);
}
