# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#              #
#    Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
LDFLAGS	:= -lreadline
RM		:= rm -f
LIBFT	:= libft/libft.a
UNAME	:= $(shell uname)

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3 -fsanitize=address
endif

ifeq ($(DEBUG), 2)
CFLAGS	+= -g
endif

# **************************************************************************** #

SRCS	+= $(M_SRCS)
M_SRCS	:= \
	srcs/minishell/main.c \
	srcs/minishell/signal.c \

SRCS	+= $(A_SRCS)
A_SRCS	:= \
	srcs/ast/print_ast.c \
	srcs/ast/ast_d.c \
	srcs/ast/print_ast2.c \
	srcs/ast/ast_c.c \
	srcs/ast/ast_p.c \
	srcs/ast/ast_l.c \
	srcs/ast/ast_s.c \
	srcs/ast/ast_a.c \

SRCS	+= $(B_SRCS)
B_SRCS	:= \
	srcs/builtin/builtin_echo.c \
	srcs/builtin/builtin_export.c \
	srcs/builtin/builtin_unset.c \
	srcs/builtin/builtin_pwd.c \
	srcs/builtin/builtin_env.c \
	srcs/builtin/builtin_exit.c \
	srcs/builtin/builtin_cd.c \

SRCS	+= $(EV_SRCS)
EV_SRCS	:= \
	srcs/environ/ft_putenv.c \
	srcs/environ/ft_setenv.c \
	srcs/environ/ft_getenv.c \
	srcs/environ/ft_unsetenv.c \
	srcs/environ/add_environ.c \
	srcs/environ/init_environ.c \
	srcs/environ/print_env.c \
	srcs/environ/free_environ.c \

SRCS	+= $(EX_SRCS)
EX_SRCS	:= \
	srcs/executor/executor.c \
	srcs/executor/exec_c.c \
	srcs/executor/exec_p_piped.c \
	srcs/executor/exec_d.c \
	srcs/executor/exec_calc_retval.c \
	srcs/executor/exec_s.c \
	srcs/executor/exec_stdfd.c \
	srcs/executor/exec_a.c \
	srcs/executor/exec_p.c \
	srcs/executor/exec_l.c \
	srcs/executor/exec_error.c \
	srcs/executor/heredoc.c \

SRCS	+= $(EP_SRCS)
EP_SRCS	:= \
	srcs/expander/expander.c \
	srcs/expander/filename_expander.c \
	srcs/expander/parameter_expander2.c \
	srcs/expander/quote_remover.c \
	srcs/expander/word_splitter.c \
	srcs/expander/is_match_globstar.c \
	srcs/expander/parameter_expander.c \
	srcs/expander/execpath.c \

SRCS	+= $(I_SRCS)
I_SRCS	:= \

SRCS	+= $(L_SRCS)
L_SRCS	:= \
	srcs/lexer/token_list_print.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex_loop.c \
	srcs/lexer/token_list_join.c \
	srcs/lexer/token_list_new.c \
	srcs/lexer/token_list_free.c \

SRCS	+= $(P_SRCS)
P_SRCS	:= \
	srcs/parser/lr_reduce_c.c \
	srcs/parser/lr_reduce_ad.c \
	srcs/parser/lr_parse_error.c \
	srcs/parser/lr_stack.c \
	srcs/parser/lr_table.c \
	srcs/parser/lr_reduce_s.c \
	srcs/parser/lr_parse.c \
	srcs/parser/lr_reduce_p.c \
	srcs/parser/parser.c \
	srcs/parser/lr_reduce_l.c \

SRCS	+= $(U_SRCS)
U_SRCS	:= \
	srcs/utils/ft_x_malloc.c \
	srcs/utils/ft_x_dup2.c \
	srcs/utils/ft_r_dup2.c \
	srcs/utils/ft_x_execve.c \
	srcs/utils/ft_x_dup.c \
	srcs/utils/ft_x_pipe.c \
	srcs/utils/ft_x_fork.c \
	srcs/utils/ft_putendl_len_fd.c \

SRCS	+= $(D_SRCS)
D_SRCS	:= \
	srcs/debug/debug_expander.c \
	srcs/debug/debug_execpath.c \
	srcs/debug/debug_syntax.c \
	srcs/debug/debug_lexer.c \

INCS	:= \
	includes \
	$(dir $(LIBFT))/includes \

LIBS	:= \
	$(LIBFT) \

# **************************************************************************** #

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
CFLAGS	+= $(addprefix -I,$(INCS))
LDFLAGS	+= $(addprefix -L,$(dir $(LIBS)))
vpath %.c $(sort $(dir $(SRCS)))

ifeq ($(UNAME), Darwin)
	# mac
	CFLAGS	+= $(addprefix -I,$(shell brew --prefix readline)/include)
	LDFLAGS	+= $(addprefix -L,$(shell brew --prefix readline)/lib)
endif

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBS) $(OBJDIR) $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ==="
	@printf "\n--- $(notdir $(SRCS))$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $@
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

-include $(DEPS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GR)+$(RC)"

$(LIBFT):
	@printf "\n$(CY)~~~ Preparing $@ ~~~\n$(RC)"
	@make -C $(dir $(LIBFT))

mostlyclean:
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@$(RM) -r $(OBJDIR)

clean: mostlyclean
	@printf "$(RE)--- Removing $(LIBFT)$(RC)\n"
	@make -C $(dir $(LIBFT)) fclean

fclean: clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all mostlyclean clean fclean re bonus

# **************************************************************************** #
