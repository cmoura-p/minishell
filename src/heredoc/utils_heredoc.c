/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:29:38 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/05 21:39:14 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_heredoc(t_heredoc *hd, t_minishell *bash)
{
    int status;

//  set_signal_hd
    while(1)
    {
        hd->fd_heredoc = open(hd->hd_path, O_CREAT \
        | O_RDWR | O_TRUNC, 064 );
//  	le as linhas do hd e pega o status de retorno
		status = read_hd_line(hd, bash);
        if (status == 1)
            printf("warning: heredoc aborted %s \n", hd->eo_heredoc);
        close(hd->fd_heredoc);
// 		0 ou 1 eh sucesso ou ctrl+c
        if (status == 0 || status == 1)
            exit(0);    // exit pq estou dentro de um processo filho
        if (status == 2)
            exit(2);   // aqui tenho que sair com o exit_code
    }
}
