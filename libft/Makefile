# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 23:50:57 by tsudo             #+#    #+#              #
#    Updated: 2022/03/14 16:01:42 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

NAME	:= libft.a
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
AR		:= ar rc
RM		:= rm -f

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3
endif

ifeq ($(DEBUG), 2)
CFLAGS	+= -g3 -fsanitize=address
endif

# **************************************************************************** #

SRCS += $(SRCS_APULONG)
SRCS_APULONG	:= \
	srcs/apulong/ft_apulong_add.c \
	srcs/apulong/ft_apulong_cmp.c \
	srcs/apulong/ft_apulong_cpy.c \
	srcs/apulong/ft_apulong_div10.c \
	srcs/apulong/ft_apulong_mul.c \
	srcs/apulong/ft_apulong_pow.c \
	srcs/apulong/ft_apulong_str.c \
	srcs/apulong/ft_apulong_val.c \

SRCS += $(SRCS_EXIT)
SRCS_EXIT		:= \
	srcs/exit/ft_error_exit.c \
	srcs/exit/ft_exit.c \
	srcs/exit/ft_validate_file_ext.c \
	srcs/exit/ft_wrapped_malloc.c \
	srcs/exit/ft_wrapped_puts.c \

SRCS += $(SRCS_CHAR)
SRCS_CHAR		:= \
	srcs/char/ft_isalnum.c \
	srcs/char/ft_isalpha.c \
	srcs/char/ft_isascii.c \
	srcs/char/ft_isdigit.c \
	srcs/char/ft_islower.c \
	srcs/char/ft_isprint.c \
	srcs/char/ft_isspace.c \
	srcs/char/ft_isupper.c \
	srcs/char/ft_isxdigit.c \
	srcs/char/ft_tolower.c \
	srcs/char/ft_toupper.c \

SRCS += $(SRCS_PRINTF)
SRCS_PRINTF		:= \
	srcs/ft_printf/ft_dprintf.c \
	srcs/ft_printf/ft_printf_bonus.c \
	srcs/ft_printf/ft_printf.c \
	srcs/ft_printf/ftpf_float_get_bonus.c \
	srcs/ft_printf/ftpf_float_utils_bonus.c \
	srcs/ft_printf/ftpf_length_bonus.c \
	srcs/ft_printf/ftpf_option_bonus.c \
	srcs/ft_printf/ftpf_out_char_bonus.c \
	srcs/ft_printf/ftpf_out_float_bonus.c \
	srcs/ft_printf/ftpf_out_hexfloat_bonus.c \
	srcs/ft_printf/ftpf_out_signed_bonus.c \
	srcs/ft_printf/ftpf_out_string_bonus.c \
	srcs/ft_printf/ftpf_out_unsigned_bonus.c \
	srcs/ft_printf/ftpf_type_bonus.c \
	srcs/ft_printf/ftpf_write_bonus.c \

SRCS += $(SRCS_GNL)
SRCS_GNL		:= \
	srcs/get_next_line/get_next_line.c \
	srcs/get_next_line/get_next_line_easy.c \
	srcs/get_next_line/gnl_ignore_ctrl_d.c \

SRCS += $(SRCS_INT)
SRCS_INT		:= \
	srcs/int/ft_atoi.c \
	srcs/int/ft_heapify_int.c \
	srcs/int/ft_heapsort_int.c \
	srcs/int/ft_index.c \
	srcs/int/ft_intlen.c \
	srcs/int/ft_isintstr.c \
	srcs/int/ft_itoa.c \
	srcs/int/ft_itoa_buf.c \
	srcs/int/ft_lis_len.c \
	srcs/int/ft_lowerbound_int.c \
	srcs/int/ft_nbrlen.c \
	srcs/int/ft_numstrcmp.c \
	srcs/int/ft_shrinkarr_int.c \
	srcs/int/ft_strtol.c \
	srcs/int/ft_strtoul.c \
	srcs/int/ft_unbrlen.c \

SRCS += $(SRCS_LIST)
SRCS_LIST		:= \
	srcs/list/ft_lstadd_back.c \
	srcs/list/ft_lstadd_front.c \
	srcs/list/ft_lstclear.c \
	srcs/list/ft_lstdelone.c \
	srcs/list/ft_lstiter.c \
	srcs/list/ft_lstlast.c \
	srcs/list/ft_lstmap.c \
	srcs/list/ft_lstmsort.c \
	srcs/list/ft_lstnew.c \
	srcs/list/ft_lstsize.c \

SRCS += $(SRCS_MEM)
SRCS_MEM		:= \
	srcs/mem/ft_bzero.c \
	srcs/mem/ft_calloc.c \
	srcs/mem/ft_free_set.c \
	srcs/mem/ft_memchr.c \
	srcs/mem/ft_memcmp.c \
	srcs/mem/ft_memcpy.c \
	srcs/mem/ft_memdup.c \
	srcs/mem/ft_memmove.c \
	srcs/mem/ft_memset.c \
	srcs/mem/ft_realloc.c \

SRCS += $(SRCS_PUT)
SRCS_PUT		:= \
	srcs/put/ft_putchar_fd.c \
	srcs/put/ft_putendl_fd.c \
	srcs/put/ft_putnbr_fd.c \
	srcs/put/ft_putstr_fd.c \

SRCS += $(SRCS_STRING)
SRCS_STRING		:= \
	srcs/string/ft_split.c \
	srcs/string/ft_split_sep.c \
	srcs/string/ft_strchr.c \
	srcs/string/ft_strcmp.c \
	srcs/string/ft_strcspn.c \
	srcs/string/ft_strdup.c \
	srcs/string/ft_striteri.c \
	srcs/string/ft_strjoin.c \
	srcs/string/ft_strjoin3.c \
	srcs/string/ft_strlcat.c \
	srcs/string/ft_strlcpy.c \
	srcs/string/ft_strlen.c \
	srcs/string/ft_strmapi.c \
	srcs/string/ft_strncmp.c \
	srcs/string/ft_strndup.c \
	srcs/string/ft_strnlen.c \
	srcs/string/ft_strnstr.c \
	srcs/string/ft_strrchr.c \
	srcs/string/ft_strsep.c \
	srcs/string/ft_strspn.c \
	srcs/string/ft_strtok.c \
	srcs/string/ft_strtrim.c \
	srcs/string/ft_substr.c \
	srcs/string/ft_trimnl.c \

INCS	:= \
	includes \

# **************************************************************************** #

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
CFLAGS	+= $(addprefix -I,$(INCS))
vpath %.c $(sort $(dir $(SRCS)))

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# **************************************************************************** #

$(NAME): $(OBJDIR) $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ==="
	@printf "\n--- $(notdir $(SRCS))$(RC)\n"
	@$(AR) $(NAME) $(OBJS)
	@printf "$(CY)~~~ Archived [$(AR)] ~~~\n--- $(NAME)$(RC)\n"

all: $(NAME)

-include $(DEPS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GR)+$(RC)"

clean:
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@$(RM) -r $(OBJDIR)

fclean: clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
