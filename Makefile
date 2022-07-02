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
RM		:= rm -f
LIBFT	:= libft/libft.a

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3 -fsanitize=address
endif

# **************************************************************************** #

SRCS	+= $(M_SRCS)
M_SRCS	:= \
	srcs/minishell/main.c \

SRCS	+= $(E_SRCS)
E_SRCS	:= \

SRCS	+= $(E_SRCS)
E_SRCS	:= \

SRCS	+= $(I_SRCS)
I_SRCS	:= \

SRCS	+= $(L_SRCS)
L_SRCS	:= \
	srcs/lexer/lex_redirection.c \
	srcs/lexer/token_list_print.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex_loop.c \
	srcs/lexer/token_list_join.c \
	srcs/lexer/token_list_new.c \
	srcs/lexer/lex_quote.c \
	srcs/lexer/token_list_free.c \
	srcs/lexer/lex_string.c \

SRCS	+= $(P_SRCS)
P_SRCS	:= \

SRCS	+= $(U_SRCS)
U_SRCS	:= \

SRCS	+= $(D_SRCS)
D_SRCS	:= \
	srcs/debug/debug_lexer.c \

INCS	:= \
	includes \
	libft/includes \

LIBS	:= \
	$(LIBFT) \

# **************************************************************************** #

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
CFLAGS	+= $(addprefix -I,$(INCS))
LDFLAGS	+= $(addprefix -L,$(dir $(LIBS)))
vpath %.c $(sort $(dir $(SRCS)))

ifeq ($(MAKECMDGOALS),bonus)
CFLAGS	+= -D PIPEX_BONUS
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
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(LIBS) $(OBJS)
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
