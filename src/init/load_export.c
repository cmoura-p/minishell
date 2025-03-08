#include "../../include/minishell.h"

int	count_strings(char **array)
{
	int	count;

	count = 0;
	while (array[count])
		count++;
	return (count);
}

char	**ft_arraydup(char **array)
{
	int		i;
	int		count;
	char	**new_array;

	count = count_strings(array);
	new_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = strdup(array[i]);
		if (!new_array[i])
		{
			while (i > 0)
				free(new_array[--i]);
			free(new_array);
			return (NULL);
		}
		i++;
	}
	new_array[count] = NULL;
	return (new_array);
}

void	load_expo(t_minishell *minishell, char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i] != NULL && args[i])
	{
		if (!ft_validarg(args[i]))
			continue ;
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
		{
			args[i][j] = '\0';
			ft_expoinsert(&minishell->export,
				ft_exponew(args[i], &args[i][j + 1]));
		}
		else
			ft_expoinsert(&minishell->export, ft_exponew(args[i], NULL));
	}
	ft_free_split(args);
}

void	free_expo(t_minishell *bash)
{
	t_envp	*aux;

	while (bash->export)
	{
		aux = bash->export;
		bash->export = bash->export->next;
		if (aux->name)
		{
			free(aux->name);
			aux->name = NULL;
		}
		if (aux->content)
		{
			free(aux->content);
			aux->content = NULL;
		}
		if (aux)
			free(aux);
	}
	bash->export = NULL;
}
