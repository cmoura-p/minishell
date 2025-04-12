/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/04/12 12:55:19 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	expandtokens(bash);
	ft_printf("Expands\n");
	print_token_list(bash->token);
	if (bash->flag_exp_exit)
		join_exitcode(bash);
	remove_exp_null(bash);
	jointokens(bash);
//	ft_printf("Remove NULL and Join\n");
//	print_token_list(bash->token);
	set_redir(bash);
	set_commands(bash);
//	ft_printf("Commands\n");
//	print_token_list(bash->token);
	remove_blank(bash);
	set_arguments(bash);
//	ft_printf("Final CALL\n");
//	print_token_list(bash->token);
	if (bash->heredoc)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		heredoc(bash);
		init_signals();
	}
}

/*
export teste="OI OI"

Novas verificacoes:
	- expansao que tenha espaco em branco (SOZINHA) ls $teste ou ls "$teste"
		em nenhum dos casos da vasamento de memoria
		testei com e sem aspas
		echo funciona normal pq nao da erro
		ls e cat funcionam normal, mas como da erro,
		 	a resposta do erro tem que ser
			- sem aspas - uma linha pra cada token (OK)
			- com aspas - uma unica linha pra tudo (ERRADO)

	- expansao que tenha espaco em branco (ACOMPANHADA)
		ls $teste :testando    ou    ls $teste $USER
			entre commands e final call da um monte de erro de Invalid Read
			IMPORTANTE
				na impressao do token blank e do :testando tambem da um monte de
				Invalid Read
			a resposta do erro ta ok mas tem um blank entre o OI e o :testando
			que nao deveria existir (ERRADO)
			aqui nao da vasamento mas deixa o espaco em branco
		no teste com echo aparecem 3 brancos entre o ultimo oi e o :testando

		ls "$teste :testando"
			entre a tokenizacao e o parsing da um monte de erro de Invalid Read
			a resposta do erro tinha que ser tudo numa linha e nao eh (ERRADO)
			NAO TEM LEAK

		ls "$teste $USER"
			LOUCURA TOTAL!!!!!
			entre a tokenizacao e o parsing da um monte de erro de Invalid Read
			no print do token da expansao nao imprime a expansao imprime USER,
			perdeu o token $
			a resposta tambem ta errada pq tem uma linha pra cada token

			aqui tem vasamento de memoria

	- expansao sem espacos (SOZINHO OU ACOMPANHADO)
		ls $PWD
		ls $PWD $USER
		ls "$PWD $USER"
		ls $PWD no meu computador
		ls "$PWD no meu computador"
			completamente normal sem vasamentos ou outros problemas de memoria

*/
// No caminho do erro nao passa por aqui
// a ideia ta certa mas nao eh aqui
// Verificar

/*
O problema esta aqui no get_sobra
Tenho que testar com um unico branco no final
Isso deve mostrar o comportamento errado
*/
void	get_sobra(t_token **aux, char *a_var, char *env_var)
{
	t_token	*newtoken;
	char	*sobra;

	// se sobra nao tiver conteudo ainda assim ele aloca memoria?
	// porque depois faz free
	sobra = ft_substr(a_var, (ft_strlen(env_var)), (ft_strlen(a_var) - 1));
	if (sobra && *sobra != '\0')
	{
		newtoken = (t_token *)ft_calloc(sizeof(t_token), 1);
		if (!newtoken)
			return ;
		newtoken->name = sobra;
		newtoken->type = WORD;
		newtoken->status = DOUBLE_Q;
		newtoken->prev = (*aux);
		newtoken->next = (*aux)->next;
		if ((*aux)->next != NULL)
			(*aux)->next->prev = newtoken;
		(*aux)->next = newtoken;
	}
	else
		free(sobra);
}

void	join_exitcode(t_minishell *bash)
{
	t_token	*aux;
	t_token	*aux_next;
	t_token	*aux_prev;

	aux = bash->token;
	while (aux)
	{
		aux_next = aux->next;
		aux_prev = aux->prev;
		if (aux->type == EXP_EXIT)
		{
			if ((aux_next) && (aux_next->name != NULL)
				&& (aux_next->type != BLANK))
				join_fw(bash, &aux);
			else
				if ((aux_prev) && (aux_prev->name != NULL)
					&& (aux_prev->type != BLANK))
					join_bw(&aux);
		}
		aux = aux_next;
	}
}

void	join_fw(t_minishell *bash, t_token **aux)
{
	char	*temp;

	temp = ft_strjoin((*aux)->name, (*aux)->next->name);
	free((*aux)->next->name);
	(*aux)->next->name = temp;
	(*aux)->next->type = EXP_EXIT;
	if (!(*aux)->prev)
	{
		bash->token = (*aux)->next;
		(*aux)->next->prev = NULL;
	}
	else
	{
		(*aux)->next->prev = (*aux)->prev;
		(*aux)->prev->next = (*aux)->next;
	}
	if ((*aux)->name)
		free((*aux)->name);
	if ((*aux)->env_null)
		free((*aux)->env_null);
	free(*aux);
}

void	join_bw(t_token **aux)
{
	char	*temp;

	temp = ft_strjoin((*aux)->prev->name, (*aux)->name);
	free((*aux)->prev->name);
	(*aux)->prev->name = temp;
	(*aux)->prev->next = (*aux)->next;
	if ((*aux)->next)
		(*aux)->prev->next = (*aux)->prev;
	if ((*aux)->name)
		free((*aux)->name);
	if ((*aux)->env_null)
		free((*aux)->env_null);
	free(*aux);
}
