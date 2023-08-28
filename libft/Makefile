# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 14:23:58 by jchamak           #+#    #+#              #
#    Updated: 2023/03/01 13:47:56 by jchamak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c \
	ft_memchr.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strlen.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strlcpy.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_strnstr.c \
	ft_strlcat.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_split.c \
	ft_printf.c \
	ft_printf_utils.c
	
BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c
	
PBO = ${SRC:.c=.o}
PBOO = ${BONUS:.c=.o}

CC = gcc

all:	$(NAME)

$(NAME): $(PBO)
	ar rcs libft.a $(PBO)

bonus:		
	gcc $(FLAGS) -c $(SRCS) $(BONUS)
	ar crs $(NAME) $(PBOO)

clean :
	rm -f $(PBO) $(PBOO)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all
	

.PHONY :
	all, clean, re, fclean, bonus