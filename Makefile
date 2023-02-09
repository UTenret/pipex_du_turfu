###########################################################
#### NAME

NAME			= pipex 

###########################################################
#### PATH TO SOURCES

PATH_SRCS 		+= srcs/

###########################################################
#### SOURCES

SRCS			+= pipex.c
SRCS			+= free_func.c
SRCS			+= free_func_cont.c
SRCS			+= init_data.c
SRCS			+= init_data_cont.c
SRCS			+= check_path.c

vpath %.c $(PATH_SRCS)

###########################################################
#### OBJS

PATH_OBJS		= objs/
OBJS			= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

###########################################################
#### LIBRARY

LIBFT_PATH 		= libft/
LIBFT 			= $(LIBFT_PATH)/libft.a

###########################################################
#### INCLUDES

INCLUDES 		= -I./includes -I./$(LIBFT_PATH)/includes
HEADER			= includes/pipex.h

###########################################################
#### COMPILATION

CC				= clang
CFLAGS			+= -Wall

ifeq ($(everything),true)
	CFLAGS		+= -Weverything
else
	CFLAGS		+= -Werror
endif

CFLAGS			+= -Wextra

###########################################################
#### RULES

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L $(INCLUDES) -L $(LIBFT_PATH) -lft

$(LIBFT):
	$(MAKE) -sC $(LIBFT_PATH)

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) 

clean:
	$(RM) -R $(PATH_OBJS)
	$(MAKE) -sC $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -sC $(LIBFT_PATH) fclean

re: fclean
	$(MAKE)

del: fclean
	rm a.out

test: 
	@ $(CC) -o tests/a.out tests/main.c $(NAME) && bash tests/runtests.sh

full_test: fclean all test

norm:
	@norminette $(PATH_SRCS) $(INCLUDES)

.PHONY: all clean fclean re del test full_test

# variables spéciales
# $@ fait référence au nom de la cible
# $< nom première dépendance
# $^ liste dépendance
# $? liste dépendance plus récentes que la cible
# $* nom fichier, sans son extension
# CIBLE > DEPENDANCES > REGLES
