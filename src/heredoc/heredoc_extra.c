/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:59:28 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/01 20:01:36 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	child_status(int hd_exit_status)
{
	if (WIFEXITED(hd_exit_status))
		return (WEXITSTATUS(hd_exit_status));
	else if (WIFSIGNALED(hd_exit_status))
	{
		if (WTERMSIG(hd_exit_status) == SIGINT)
		{
			return (EXIT_SIGINT);
		}
		else if (WTERMSIG(hd_exit_status) == SIGQUIT)
		{
			return (EXIT_SIGQUIT);
		}
	}
	return (0);
}
