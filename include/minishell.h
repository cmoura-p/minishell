/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:43 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/14 14:25:40 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# define SUCCESS_EXIT "exit\n"

/* enum e_oper
{
	WORD,				// command
	PIPE,				// |
	REDIR_IN,			// <
	REDIR_OUT,			// >
	REDIR_APP,	 		// >>
	HEREDOC,			// <<
	S_QUOTE,			//	'
	D_QUOTE,			//	"
	NOTHING,			//NULL
} 	t_oper;
 */
typedef struct s_minishell
{
	int					exit_status;
	void				*bash_return;
	char				*raw_command;
	struct s_minishell	*next;
} 	t_minishell;

//init
t_minishell	*init_data(char **envp, char **prompt);
void		init_signals();
void		signal_handler(int signum);
int			init_bash(char **cmd_line, char *prompt);
char		*check_syntax(char *line);
int			btw_quotes(char *line, int i);

//parsing
void		parsing(t_minishell *bash);

//free_memory
void		ft_clear_all(t_minishell **bash, char	**line);
void		free_necessary(char	**line, t_minishell **bash);

#endif
