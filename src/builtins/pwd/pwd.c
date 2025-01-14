/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brendon <brendon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:12:36 by brendon           #+#    #+#             */
/*   Updated: 2025/01/06 09:19:10 by brendon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_minishell *minishell)
{
	char	*pwd;

	(void) minishell;// ver o que vai fazer com isso
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf("minishell: pwd: ERROR\n");
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}
		//é preciso tratar o erro