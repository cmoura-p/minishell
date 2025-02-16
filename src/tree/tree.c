#include "../../include/minishell.h"

void free_token(t_token *token)
{
	if (!token)
		return;
	if (token->name)
		free(token->name);
	free(token);
}

void free_token_list(t_token *head)
{
	t_token *tmp;

	if (!head)
		return;
	while (head)
	{
		tmp = head->next;
		free_token(head);
		head = tmp;
	}
}

void *ft_pipe(t_token *start, t_token *aux)
{
	t_pipe *pipe;
	t_token *left;
	t_token *right;

	if (!aux || !aux->next)
		return (NULL);
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	left = start;
	right = aux->next;
	if (aux->prev)
		aux->prev->next = NULL;
	if (aux->next)
		aux->next->prev = NULL;
	free_token(aux);
	pipe->type = PIPE;
	pipe->left = ft_tree(left);
	pipe->right = ft_tree(right);
//	printf("pipe\n");
	return (pipe);
}

void *ft_redir_in(t_token *start, t_token *aux)
{
    t_redir *redir;

    if (!aux || !aux->next)
        return (NULL);
    
    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    
    redir->type = REDIR_IN;
    redir->file_name = ft_strdup(aux->next->name);
    
    redir->fd = open(redir->file_name, O_RDONLY);
    if (redir->fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(redir->file_name, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
		// Definir erro, mas continuar a execução
        free(redir->file_name);
        free(redir);
        return (ft_tree(start)); // Continua a construção da árvore sem o redirecionamento
    }

    // Removendo tokens corretamente
    if (aux->prev)
        aux->prev->next = aux->next->next;
    if (aux->next->next)
        aux->next->next->prev = aux->prev;

    free_token(aux->next);
    free_token(aux);

    redir->next = ft_tree(start);
   // printf("redir_in\n");
    return (redir);
}


void *ft_redir_out(t_token *start, t_token *aux)
{
	t_redir *redir;

	if (!aux || !aux->next)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_OUT;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(redir->file_name);
		free(redir);
		return (NULL);
	}
	if (aux->prev)
		aux->prev->next = aux->next->next;
	if (aux->next->next)
		aux->next->next->prev = aux->prev;
	free_token(aux->next);
	free_token(aux);
	redir->next = ft_tree(start);
	//printf("redir_out\n");
	return (redir);
}

void *free_args_on_error(char **args, int i)
{
	while (i >= 0)
		free(args[i--]);
	free(args);
	return (NULL);
}

char **tokken_to_args(t_token *start)
{
	t_token *aux;
	char **args;
	int i;

	aux = start;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (start)
	{
		args[i] = ft_strdup(start->name);
		if (!args[i])
			return (free_args_on_error(args, i - 1));
		start = start->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
void *ft_redir_app(t_token *start, t_token *aux)
{
	t_redir *redir;

	if (!aux || !aux->next)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_APP;
	redir->file_name = ft_strdup(aux->next->name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(redir->file_name);
		free(redir);
		return (NULL);
	}
	if (aux->prev)
		aux->prev->next = aux->next->next;
	if (aux->next->next)
		aux->next->next->prev = aux->prev;
	free_token(aux->next);
	free_token(aux);
	redir->next = ft_tree(start);
	//printf("redir_app\n");
	return (redir);
}

void *ft_tree(t_token *start)
{
	t_token	*aux;
	void	*root;

	if (!start)
		return (NULL);
	aux = start;
	while (aux && aux->type != PIPE)
		aux = aux->next;
	if (aux)
		return (ft_pipe(start, aux));
	aux = start;
	while (aux && aux->type != REDIR_IN)
		aux = aux->next;
	if (aux)
		return (ft_redir_in(start, aux));
	aux = start;
	while (aux && aux->type != REDIR_OUT)
		aux = aux->next;
	if (aux)
		return (ft_redir_out(start, aux));
	aux = start;
	while (aux && aux->type != REDIR_APP)
		aux = aux->next;
	if (aux)
		return (ft_redir_app(start, aux));
	root = malloc(sizeof(t_exec));
	if (!root)
		return (NULL);
	((t_exec *)root)->type = COMMAND;
	((t_exec *)root)->args = tokken_to_args(start);
	//printf("root->type: %d\n", ((t_exec *)root)->type);
	//printf("comand\n");
	free_token_list(start);
	return (root);
}
