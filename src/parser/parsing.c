/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/21 01:27:20 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	// Outro sobre free:
	// free(token->name) e free(token)

	expandtokens(bash);				// substitui as variaveis expandiveis
//	print_token_list(bash->token);
	jointokens(bash);				// junta as words que estao entre quotes
	set_commands(bash);				// altera o type WORD para COMMAND
	print_token_list(bash->token);
	remove_blank(bash);
	print_token_list(bash->token);
	set_arguments(bash);			// altera o type WORD ou EXP_ARG para ARGUMENT

	// eliminar tokens blank (verificar a necessidade de manter a ordem ou
	//							de eliminar tokens desnecessarios)
	// definir comandos (lembrar de procurar por Pipes)
	// definir argumentos de comandos

	print_token_list(bash->token);
}
