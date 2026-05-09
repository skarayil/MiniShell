NAME := minishell
NAME_BONUS := minishell_bonus

CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

SRC_DIR := src_mandatory
OBJ_DIR := build_mandatory

INC := -Iinclude_mandatory -I$(LIBFT_DIR)

SRC_FILES := \
	main.c \
	builtins/builtins.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/exit_utils.c \
	builtins/export.c \
	builtins/pwd.c \
	builtins/unset.c \
	env/env_export_print.c \
	env/env_export_sort.c \
	env/env_get.c \
	env/env_init.c \
	env/env_set.c \
	env/env_unset.c \
	env/shlvl.c \
	exec/exec.c \
	exec/exec_cmd.c \
	exec/exec_path.c \
	exec/fd.c \
	exec/find_in_path.c \
	exec/heredoc.c \
	exec/heredoc_run.c \
	exec/pipeline.c \
	exec/redir_apply.c \
	exec/redir_ops.c \
	exec/wait.c \
	expand/apply_expansion.c \
	expand/expand_handle.c \
	expand/expand_parse_utils.c \
	expand/expand_run.c \
	expand/expand_utils.c \
	expand/expander.c \
	lexer/parse_utils.c \
	lexer/tok_buf.c \
	lexer/tok_op.c \
	lexer/tok_str.c \
	lexer/tok_vec.c \
	lexer/tok_word.c \
	lexer/tokenize.c \
	parser/argv_free.c \
	parser/ast.c \
	parser/ast_cmd.c \
	parser/ast_cmd_utils.c \
	parser/ast_helpers.c \
	parser/ast_nodes.c \
	parser/ast_parse_line.c \
	parser/ast_primary.c \
	parser/ast_redir.c \
	parser/ast_utils.c \
	shell/sh_continuation.c \
	shell/sh_destroy.c \
	shell/sh_handle_line.c \
	shell/sh_init.c \
	shell/sh_loop.c \
	shell/sh_read.c \
	signals/sig_handlers.c \
	signals/sig_setup.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRC_BONUS_DIR := src_bonus
OBJ_BONUS_DIR := build_bonus

INC_BONUS := -Iinclude_bonus -I$(LIBFT_DIR)

SRC_BONUS_FILES := \
	main_bonus.c \
	builtins_bonus/builtins_bonus.c \
	builtins_bonus/cd_bonus.c \
	builtins_bonus/echo_bonus.c \
	builtins_bonus/env_bonus.c \
	builtins_bonus/exit_bonus.c \
	builtins_bonus/exit_utils_bonus.c \
	builtins_bonus/export_bonus.c \
	builtins_bonus/pwd_bonus.c \
	builtins_bonus/unset_bonus.c \
	env_bonus/env_export_print_bonus.c \
	env_bonus/env_export_sort_bonus.c \
	env_bonus/env_get_bonus.c \
	env_bonus/env_init_bonus.c \
	env_bonus/env_set_bonus.c \
	env_bonus/env_unset_bonus.c \
	env_bonus/shlvl_bonus.c \
	exec_bonus/exec_bonus.c \
	exec_bonus/exec_cmd_bonus.c \
	exec_bonus/exec_path_bonus.c \
	exec_bonus/fd_bonus.c \
	exec_bonus/find_in_path_bonus.c \
	exec_bonus/heredoc_bonus.c \
	exec_bonus/heredoc_run_bonus.c \
	exec_bonus/pipeline_bonus.c \
	exec_bonus/subshell_bonus.c \
	exec_bonus/redir_apply_bonus.c \
	exec_bonus/redir_ops_bonus.c \
	exec_bonus/wait_bonus.c \
	expand_bonus/apply_expansion_bonus.c \
	expand_bonus/expand_handle_bonus.c \
	expand_bonus/expand_parse_utils_bonus.c \
	expand_bonus/expand_run_bonus.c \
	expand_bonus/expand_utils_bonus.c \
	expand_bonus/expander_bonus.c \
	expand_bonus/wildcard_bonus.c \
	expand_bonus/wildcard_utils_bonus.c \
	lexer_bonus/parse_utils_bonus.c \
	lexer_bonus/tok_buf_bonus.c \
	lexer_bonus/tok_op_bonus.c \
	lexer_bonus/tok_str_bonus.c \
	lexer_bonus/tok_vec_bonus.c \
	lexer_bonus/tok_word_bonus.c \
	lexer_bonus/tokenize_bonus.c \
	parser_bonus/argv_free_bonus.c \
	parser_bonus/ast_bonus.c \
	parser_bonus/ast_cmd_bonus.c \
	parser_bonus/ast_cmd_utils_bonus.c \
	parser_bonus/ast_helpers_bonus.c \
	parser_bonus/ast_nodes_bonus.c \
	parser_bonus/ast_parse_line_bonus.c \
	parser_bonus/ast_primary_bonus.c \
	parser_bonus/ast_redir_bonus.c \
	parser_bonus/ast_utils_bonus.c \
	shell_bonus/sh_continuation_bonus.c \
	shell_bonus/sh_destroy_bonus.c \
	shell_bonus/sh_handle_line_bonus.c \
	shell_bonus/sh_init_bonus.c \
	shell_bonus/sh_input_bonus.c \
	shell_bonus/sh_loop_bonus.c \
	shell_bonus/sh_read_bonus.c \
	signals_bonus/sig_handlers_bonus.c \
	signals_bonus/sig_setup_bonus.c

SRC_BONUS := $(addprefix $(SRC_BONUS_DIR)/, $(SRC_BONUS_FILES))
OBJ_BONUS := $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(READLINE_DIR),)
		INC += -I$(READLINE_DIR)/include
		INC_BONUS += -I$(READLINE_DIR)/include
		LDFLAGS += -L$(READLINE_DIR)/lib
	endif
	LIBS := -lreadline -lhistory -lncurses
else
	LIBS := -lreadline -lhistory -lncurses
endif

RM := rm -f

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) $(LIBS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(LDFLAGS) $(LIBS) -o $(NAME_BONUS)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus