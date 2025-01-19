/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:43 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/01/19 13:20:58 by cmoura-p         ###   ########.fr       */
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
	WORD,				// geral
	FILE_NAME,			// file
	PIPE,				// |
	REDIR_IN,			// <
	REDIR_OUT,			// >
	REDIR_APP,	 		// >>
	HEREDOC,			// <<
	S_QUOTE,			// '
	D_QUOTE,			// "
	EXP_EXIT,			// $?
	EXP_ENVP,			// $
	COMMAND,			// command
	ARGUMENT,			// argumento de comando
	BUILTIN,			// built-in
};

enum	e_status
{
	NO_QUOTE,
	SINGLE_Q,
	DOUBLE_Q,
};

enum	e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

typedef struct s_token
{
	enum e_type		type;
	enum e_status	status;
	int				i;
	char			*name;
	int				expand;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_envp
{
	char			*name;
	char			*content;
	struct s_envp	*prev;
	struct s_envp	*next;
}					t_envp;

typedef struct s_export
{
	char			*name;
	char			*content;
	struct s_envp	*prev;
	struct s_envp	*next;
}					t_export;

typedef struct s_heredoc
{
	int					i;
	int					fd_heredoc;
	char				*heredoc_path;
	char				*eo_heredoc;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_minishell
{
	char			*cmd_line;
	t_envp			*envp;
	t_heredoc		*heredoc;
	t_token			*token;
	t_export		*export;	// fazer em lista encadeada
	void			*root;
	char			*path;
	int				exit_status;
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
	int				fd;
	int				id;
	void			*next;
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
int			init_bash(t_minishell *minishell, char *prompt);
void		load_envp(t_minishell *bash, char **envp);
int			split_envp(const char *envp_line, char **before, char **after);
void		add_envplst(t_minishell *bash, char *name, char *content);
void		add_envplst_back(t_envp **newenvp, t_envp *lst);
char		*check_syntax(char *line);
int			btw_quotes(char *line, int i);
int			skip_blank(char *line, int i);
char		*ft_minitrim(char *line);

//run
void		run(t_minishell *bash);
void		tokenizer(t_minishell *bash);
void		parsing(t_minishell *bash);

//token
int			tokenizer_quotes(char *line, int i, t_minishell *bash);
int			tokenizer_metachar(char *line, int i, t_minishell *bash);
int			tokenizer_word(char *line, int i, t_minishell *bash);
int			token_redir(char *line, int i, t_minishell *bash);
int			token_pipe(char *line, int i, t_minishell *bash);
int			token_dollar(char *line, int i, t_minishell *bash);
int			s_quote(char *line, int i, t_minishell *bash);
int			d_quote(char *line, int i, t_minishell *bash);
int			redir_in(char *line, int i, t_minishell *bash);
int			redir_out(char *line, int i, t_minishell *bash);
int			redir_app(char *line, int i, t_minishell *bash);
int			redir_heredoc(char *line, int i, t_minishell *bash);
int			handle_blank(char *line, int i, t_minishell *bash);
void		add_tokenlst(t_minishell **bash, char *name, \
						enum e_type type, enum e_status status_q);
void		add_tokenlst_back(t_token **newtoken, t_token *lst);
int			ft_isword(char s);
void		print_token_list(t_token *token);

//parsing
void		jointokens(t_minishell *bash);
void		joinnext(t_token **token, char *name);
void		joinprev(t_token **token, char *name);
void		expandtokens(t_minishell *bash);
void		joinexpand(t_token **token, char *name, char *name_exp);
void 		joinexpand_dq(t_token **token, char *after, char *before, char *name_exp);
void		joinlast(t_token **aux);
void		expand_var(t_token **aux, t_envp *aux_envp);
void		expand_in_dq(t_token **aux, t_envp *aux_envp);
int			check_dollar(char *line, char **before, char **after);
int			valid_envp_char(char s, int i);
char		*envp_name(char *name);
char		*ft_getenv(t_envp *aux, char *name);

//free
void		free_to_quit(t_minishell *bash, char *prompt);
void		free_to_restart(t_minishell *bash);
void		free_bash(t_minishell *bash);
void		free_envp(t_minishell *bash);

#endif
