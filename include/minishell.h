/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:43 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/21 23:48:02 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

# define SUCCESS_EXIT "exit\n"

enum e_type
{
	BLANK,				// blank space
	WORD,				// command
	PIPE,				// |
	REDIR_IN,			// <
	REDIR_OUT,			// >
	REDIR_APP,	 		// >>
	HEREDOC,			// <<
	S_QUOTE,			//	'
	D_QUOTE,			//	"
	NADA,				//NULL
};

typedef struct s_token
{
	enum e_type		type;
	char			*name;
	int				seq;	//?
	int				status;	//?
	int				expand;	//?
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	char			*cmd_line;
	char			**envp;
	t_token			*token;
	void			*root;			//?
	char			*path;			//?
	int				exit_status;	//?
	int				fd_in;			//?
	int				fd_out;			//?
	int				pid;			//?
	int				process;		//?
}					t_minishell;

/*--------------------------B-TREE----------------------*/

typedef struct s_pipe
{
	enum e_type		type;
	void			*left;
	void			*right;
}					t_pipe;

typedef struct s_redir
{
	enum e_type		type;
	char 			*file_name;
	void			*next;
	int				id;
}					t_redir;

typedef struct s_exec
{
	enum e_type		type;
	char			**args;
	char			*path;		//?
	int				builtin;	//?
}					t_exec;

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
