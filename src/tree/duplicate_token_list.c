#include "../../include/minishell.h"

t_token	*duplicate_token(t_token *token)
{
	t_token	*new_token;

	if (!token)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = token->type;
	new_token->status = token->status;
	new_token->i = token->i;
	new_token->name = ft_strdup(token->name);
	new_token->expand = token->expand;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

t_token	*duplicate_token_list(t_token *head)
{
	t_token	*new_head;
	t_token	*new_token;
	t_token	*current;
	t_token	*prev;

	new_head = NULL;
	new_token = NULL;
	current = head;
	prev = NULL;
	while (current)
	{
		new_token = duplicate_token(current);
		if (!new_token)
		{
			free_token_list(new_head);
			return (NULL);
		}
		if (!new_head)
			new_head = new_token;
		if (prev)
			prev->next = new_token;
		new_token->prev = prev;
		prev = new_token;
		current = current->next;
	}
	return (new_head);
}
