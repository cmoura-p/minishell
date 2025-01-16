/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:58:23 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/15 20:40:38 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(t_minishell *bash)
{
	// Outro sobre free:
	// free(token->name) e free(token)

	expandtokens(bash);				// substitui as variaveis expandiveis
	jointokens(bash);				// junta as words que estao entre quotes

	// eliminar tokens blank (verificar a necessidade de manter a ordem ou
	//							de eliminar tokens desnecessarios)
	// definir comandos (lembrar de procurar por Pipes)
	// definir argumentos de comandos

	print_token_list(bash->token);
}
