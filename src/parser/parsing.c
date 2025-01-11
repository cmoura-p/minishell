/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/11 11:18:29 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Aqui tenho que pegar o que foi tokenizado
	e "montar" para a arvore binaria

	O que temos ate agora:
		QUOTES - WORDS - PIPES - REDIRS - EXPANSAO

	. sobre QUOTES: eliminar os quotes desnecessarios, ou seja,
					quando ha words separados em tokens mas
					sem espaco em branco, ai ha um quote desnecessario

	.sobre 	WORDS:	repetir a sequencia "colando" as WORDS sem espaco em branco

	. sobre PIPES:	manter os pipes, nao se importar com a existencia de
					espacos, antes ou depois dos pipes

	. sobre REDIR:	ha 4, IN, OUT, APP e HEREDOC
					IN
*/
void	parsing(t_minishell *bash)
{
	expandwords(bash);
	jointokens(bash);
	print_token_list(bash->token);
}
