# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:58:51 by ulysse            #+#    #+#              #
#    Updated: 2023/01/29 14:16:42 by utenret          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################################################################
#### NAME

NAME			= libft.a

##########################################################################
#### PATH TO SOURCES

PATH_SRCS		+= srcs/

##########################################################################
#### SOURCES

SRCS			+= ft_atoi.c 
SRCS			+= ft_bzero.c
SRCS			+= ft_calloc.c
SRCS			+= ft_isalnum.c
SRCS			+= ft_isalpha.c
SRCS			+= ft_isascii.c
SRCS			+= ft_isdigit.c
SRCS			+= ft_isprint.c
SRCS			+= ft_itoa.c 
SRCS			+= ft_memchr.c 
SRCS			+= ft_memcmp.c 
SRCS			+= ft_memcpy.c 
SRCS			+= ft_memmove.c 
SRCS			+= ft_memset.c 
SRCS			+= ft_putchar_fd.c 
SRCS			+= ft_putendl_fd.c 
SRCS			+= ft_putnbr_fd.c 
SRCS			+= ft_putstr_fd.c 
SRCS			+= ft_split.c
SRCS			+= ft_strchr.c
SRCS			+= ft_strdup.c 
SRCS			+= ft_striteri.c
SRCS			+= ft_strjoin.c 
SRCS			+= ft_strlcat.c 
SRCS			+= ft_strlcpy.c
SRCS			+= ft_strlen.c
SRCS			+= ft_strmapi.c
SRCS			+= ft_strncmp.c
SRCS			+= ft_strnstr.c
SRCS			+= ft_strrchr.c 
SRCS			+= ft_strtrim.c
SRCS			+= ft_substr.c 
SRCS			+= ft_tolower.c 
SRCS			+= ft_toupper.c
SRCS			+= ft_uitoa.c 
SRCS			+= ft_printf.c
SRCS			+= ft_printf_converter.c
SRCS			+= ft_printf_utils.c 
SRCS			+= ft_dprintf.c 
SRCS			+= ft_lstnew.c
SRCS			+= ft_lstadd_front.c
SRCS			+= ft_lstsize.c
SRCS			+= ft_lstlast.c
SRCS			+= ft_lstadd_back.c
SRCS			+= ft_lstdelone.c
SRCS			+= ft_lstclear.c
SRCS			+= ft_lstiter.c
SRCS			+= ft_lstmap.c
SRCS			+= get_next_line.c
SRCS			+= ft_strnjoin.c
SRCS			+= ft_strjoin_no_free.c
SRCS			+= ft_strjoin_free_s2.c

vpath %.c $(PATH_SRCS)

##########################################################################
#### OBJS 

PATH_OBJS		= objs/
OBJS			= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

##########################################################################
#### INCLUDES

INCLUDES		= includes/
HEADER			= includes/libft.h

#########################################################################
#### COMPILATION

CC				= clang
CFLAGS			+= -Wall
CFLAGS			+= -Werror
CFLAGS			+= -Wextra
AR = ar rcs

###########################################################
#### RULES

#ifeq (bonus, $(findstring bonus, $(MAKECMDGOALS)))
#  SRCS += $(BONUS) 
#endif

all: $(NAME)

#bonus: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^ 

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) 

clean:
	 $(RM) -R $(PATH_OBJS)

fclean: clean
	$(RM) $(NAME)	

re: fclean
	$(MAKE)
