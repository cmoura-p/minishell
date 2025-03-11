/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@students.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:43 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/03/11 10:51:33 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>

extern int	g_signal;

# define SUCCESS_EXIT "exit\n"
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127

enum e_type
{
	BLANK,				// blank space
	WORD,				// geral
	PIPE,				// |
	REDIR_IN,			// <
	FILE_IN,
	REDIR_OUT,			// >
	FILE_OUT,
	REDIR_APP,			// >>
	FILE_APP,
	HEREDOC,			// <<
	S_QUOTE,			// '
	D_QUOTE,			// "
	EXP_EXIT,			// $?
	EXP_ENVP,			// $
	COMMAND,			// command
	ARGUMENT,			// argumento de comando
	EXP_NULL,			// expansao nula
	BUILTIN,			// built-in
};

enum	e_status
{
	NO_QUOTE,
	SINGLE_Q,
	DOUBLE_Q,
};

enum	e_exit_code
{
	SUCCESS,
	MALLOC_ERROR,
	SYNTAX_ERROR,
	SIGNAL_ERROR,
	CMD_NOT_FOUND,
	EXIT_SIGINT = 130,
	EXIT_SIGQUIT = 131,
	WHATEVER,
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

typedef struct s_help_recursion
{
	char			*after;
	char			*before;
	int				flag_expand;
	char			*sobra;
	char			*env_var;
	char			*new_line;
	char			*temp_after;
}					t_help_recursion;

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

typedef struct s_heredoc
{
	int					counter;
	int					fd_heredoc;
	char				*eo_heredoc;
	char				*hd_path;
	enum e_status		status;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_minishell
{
	char				*cmd_line;
	t_envp				*envp;
	t_heredoc			*heredoc;
	t_token				*token;
	t_envp				*export;
	enum e_exit_code	exit_status;
	void				*root;
	char				*path;
	int					fd_in;
	int					fd_out;
	int					pid;
	int					process;
	int					flag_exp_exit;
}						t_minishell;

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
	char			*file_name;
	int				fd;
	int				id;
	void			*next;
}					t_redir;

typedef struct s_exec
{
	enum e_type		type;
	char			**args;
	char			*path;
	int				builtin;
}					t_exec;

//init
t_minishell	*init_data(char **envp);
void		init_signals(void);
int			init_bash(t_minishell *minishell);
void		load_envp(t_minishell *bash, char **envp);
int			split_envp(const char *envp_line, char **before, char **after);
void		add_envplst(t_minishell *bash, char *name, char *content);
void		add_envplst_back(t_envp **newenvp, t_envp *lst);
char		*check_syntax(char *line);
int			btw_quotes(char *line, int i);
int			skip_blank(char *line, int i);
char		*ft_minitrim(char *line, int i, int j);
int			split_string(char *line, char **before, char **after, char c);
void		load_expo(t_minishell *minishell, char **args);
char		**ft_arraydup(char **array);

//signals
void		signal_handler(int signum);
void		set_heredoc_signals(void);
void		heredoc_ctrl_c(t_minishell *bash);
void		heredoc_signal_handler(int signum);
void		handle_ctrl_c(t_minishell *bash);
void		handle_ctrl_d(t_minishell *bash);

//run
void		run(t_minishell *bash);
void		tokenizer(t_minishell *bash);
void		parsing(t_minishell *bash);

//token
int			tokenizer_quotes(char *line, int i, t_minishell *bash);
int			tokenizer_metachar(char *line, int i, t_minishell *bash);
int			tokenizer_word(char *line, int i, t_minishell *bash);
int			token_heredoc(char *line, int i, t_minishell *bash);
int			token_redir(char *line, int i, t_minishell *bash);
int			token_pipe(char *line, int i, t_minishell *bash);
int			token_dollar(char *line, int i, t_minishell *bash);
int			s_quote(char *line, int i, t_minishell *bash);
int			d_quote(char *line, int i, t_minishell *bash);
int			redir_in(char *line, int i, t_minishell *bash);
int			redir_out(char *line, int i, t_minishell *bash);
int			redir_app(char *line, int i, t_minishell *bash);
int			handle_blank(char *line, int i, t_minishell *bash);
void		add_tokenlst(t_minishell **bash, char *name, \
				enum e_type type, enum e_status status_q);
void		add_tokenlst_dq(t_minishell *bash, t_token **aux, \
				char *name, enum e_type type);
void		add_tokenlst_back(t_token **newtoken, t_token *lst);
void		del_tokenlst(t_minishell *bash, t_token **token);
int			ft_isword(char s);
int			expand_is_hd_eof(char *line, int i, int j, char **redir);
void		print_token_list(t_token *token);
void		fix_a_var(char **a_var);

//parsing
void		jointokens(t_minishell *bash);
void		joinnext(t_token **token, char *name);
void		joinprev(t_token **token, char *name);
void		expandtokens(t_minishell *bash);
void		joinexpand(t_token **token, char *name, char *name_exp);
void		expand_var(t_token **aux, t_envp *aux_envp);
void		expand_exit(t_minishell *bash, t_token **token);
void		expand_in_dq(t_minishell *bash, t_token **aux, \
				char *b_var, char *a_var);
int			valid_envp_char(char s, int i);
char		*envp_name(char *name);
char		*ft_getenv(t_envp *aux, char *name);
void		set_commands(t_minishell *bash);
void		set_arguments(t_minishell *bash);
void		set_redir(t_minishell *bash);
t_token		*set_redir_file(t_token *token, enum e_type type);
void		remove_blank(t_minishell *bash);
void		remove_exp_null(t_minishell *bash);
void		find_a_pipe(t_token **aux);
int			blank_in_expand(t_token *token, char *exp_var, \
				char *before, char *after);
void		get_sobra(t_token **aux, char *a_var, char *env_var);
int			not_redirection(t_token *token);
void		newtoken_after_parsing(t_token **aux, char *a_var);
void		join_exitcode(t_minishell *bash);
void		join_fw(t_minishell *bash, t_token **aux);
void		join_bw(t_token **aux);

//heredoc
void		heredoc(t_minishell *bash);
int			set_heredoc(t_heredoc *hd, t_minishell *bash);
void		init_heredoc(t_minishell *bash);
void		create_hd_list(t_minishell *bash);
void		change_hd_tokens(t_minishell *bash);
void		go_write(int fd_hd, char *line);
int			read_hd_line(t_heredoc *hd, t_minishell *bash);
void		add_heredoclst(t_heredoc **hd, char *name, enum e_status status_q);
int			child_status(int hd_exit_status);
int			checked_for_hd(t_token *token);
void		check_exp_in_hd(char **line, t_minishell *bash);
void		join_sobra_out(t_help_recursion *aux_hr, char **temp);
void		join_sobra_in(t_help_recursion *aux_hr, char *expand, char **temp);
void		ft_nao_expande(t_help_recursion *aux_hr);
void		ft_expande(t_help_recursion *aux_hr, t_envp *aux_exp);

//builtins
//cd
void		ft_cd(t_minishell *minishell, char **args);
int			ft_check_args(t_minishell *bash, char **args);

//echo
void		ft_echo(t_minishell *minishell, char **args);

//env
void		ft_env(t_minishell *minishell, char **args);
void		ft_envadd(t_envp **envp, t_envp *new);

//exit
void		ft_exit(t_minishell *minishell, char **args);

//export
void		ft_export(t_minishell *minishell, char **args);
void		ft_expoinsert(t_envp **export, t_envp *new);
t_envp		*ft_exponew(char *name, char *content);
void		ft_freeexponode(t_envp *node);
int			ft_validarg(char *arg, t_minishell *minishell);

//pwd
void		ft_pwd(t_minishell *minishell, char **args);

//ft_ftprintf
void		ft_fprintf(int fd, const char *format, ...);

//unset
void		ft_unset(t_minishell *minishell, char **args);
void		ft_search_del(t_envp **env, char *key);

//free
void		free_to_quit(t_minishell *bash);
void		free_to_restart(t_minishell *bash);
void		free_bash(t_minishell *bash);
void		free_envp(t_minishell *bash);
void		clean_heredoc(t_minishell *bash);
void		clean_tokens(t_minishell *bash);
void		ft_free_tree(void *root);
void		free_token(t_token *token);
void		ft_free_split(char **args);
void		*free_null_redir(t_token *aux);
void		free_expo(t_minishell *bash);

//tree

//build_tree
void		*ft_tree(t_token *start, t_minishell *bash);
void		*ft_redir_app(t_token *start, t_token *aux, t_minishell *bash);
void		*ft_redir_out(t_token *start, t_token *aux, t_minishell *bash);
void		*ft_redir_in(t_token *start, t_token *aux, t_minishell *bash);
void		*ft_pipe(t_token *start, t_token *aux, t_minishell *bash);
void		*handle_command(t_token *start);
t_token		*find_token_by_type(t_token *start, enum e_type type);

//tree_util
void		ft_remove_tokens(t_token *aux);
char		**tokken_to_args(t_token *start);
void		free_token_list(t_token *head);
void		*free_args_on_error(char **args, int i);
void		*handle_redir_error(t_redir *redir, \
				t_minishell *bash, t_token *aux);

//duplicate_token_list
t_token		*duplicate_token_list(t_token *head);

//execute
//ft_env_args.c
char		**ft_env_args(t_envp *envp);

//ft_exec_builtins.c
void		ft_exec_builtin(t_minishell *minishell, char **args);
int			ft_is_builtin(char *cmd);

//ft_exec_cmd.c
void		ft_exec_cmd(t_minishell *minishell, t_exec *cmd);

//ft_exec_pipe.c
void		ft_exec_pipe(t_minishell *minishell, t_pipe *pipeline);

//ft_exec_redir.c
void		ft_exec_redir(t_minishell *minishell, t_redir *redir);

//ft_execute.c
void		ft_execute(t_minishell *minishell, void *root);

//ft_find_path.c
char		*ft_find_path(t_minishell *minishell, char *cmd);

//testes
void		ft_execute(t_minishell *minishell, void *root);
void		free_args(char **args);
void		free_exit(t_minishell **minishell, int status);

#endif
