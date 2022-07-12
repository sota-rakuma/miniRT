# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/10 17:18:54 by srakuma           #+#    #+#              #
#    Updated: 2022/07/13 02:42:42 by rnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strjoin_with_free.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_printb.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line.c
BONUS_SRCS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c
REG_OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJS_DIR)/, $(BONUS_SRCS:.c=.o))
OBJS_DIR=obj
DEPS_DIR=deps
DEPS = $(SRCS:.c=.d) $(BONUS_SRCS:.c=.d)

ifdef WITH_BONUS
OBJ_FILES = $(REG_OBJS) $(BONUS_OBJS)
else
OBJ_FILES = $(REG_OBJS)
endif

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS_DIR) $(DEPS_DIR) $(OBJ_FILES)
	ar -cr $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

.PHONY: bonus
bonus:
	$(MAKE) WITH_BONUS=1 all

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(DEPS_DIR):
	mkdir -p $(DEPS_DIR)

$(OBJS_DIR)/%.o: %.c
		${CC} ${CFLAGS} -c -MMD -MP -o $@ $<

-include $(DEPS)

.PHONY: clean
clean:
	rm -fr $(REG_OBJS) $(OBJS_DIR) $(DEPS_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	norminette | grep -v OK! || echo ok

