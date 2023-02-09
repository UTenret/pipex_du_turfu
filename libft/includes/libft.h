/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:15:18 by ulysse            #+#    #+#             */
/*   Updated: 2023/01/29 14:16:24 by utenret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <bsd/string.h>
# include <assert.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif 

# define OPEN_MAX FOPEN_MAX
# ifndef HEXAMIN
#  define HEXAMIN "0123456789abcdef"
# endif

# ifndef HEXAMAJ
#  define HEXAMAJ "0123456789ABCDEF"
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_itoa(int n);
char		*ft_uitoa(unsigned int n);
long long	ft_atoi(const char *nptr);

char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strnjoin(char *s1, char *s2, int size);

void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		**ft_split(char const *str, char c);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void		ft_p(int fd, unsigned long long nbr, size_t size);
void		ft_convert_hexa_min(int fd, unsigned int nbr, size_t size);
void		ft_convert_hexa_maj(int fd, unsigned int nbr, size_t size);
size_t		ft_sizel(unsigned int nbr);
size_t		ft_sizell(unsigned long long nbr);
int			ft_nil(int fd);
int			ft_putchar(int fd, char c);
int			ft_putstr_stack(int fd, const char *s);
int			ft_putstr(int fd, char *s);
int			ft_putnstr(int fd, const char *s, size_t n);
ssize_t		ft_check_next_pc(const char *str, size_t j);
int			ft_convert_hexa_p(int fd, char *str);
int			ft_check_conv(int fd, const char *str, void *arg);
int			ft_vdprintf(int fd, const char *str, va_list ap, size_t len);
int			ft_printf(const char *str, ...);
int			ft_dprintf(int fd, const char *str, ...);

////////////////////////////////GNL////////////////////////////////////////

ssize_t		ft_does_str_contains_n(char	*str);
char		*ft_rest(char *res, char *gnl, size_t i);
char		*ft_weout(char **res, char *buf, char *gnl, int c);
int			ft_letsread(char **res, char *buf, char *gnl, int fd);
char		*get_next_line(int fd);
char		*ft_strnjoin(char *s1, char *s2, int size);
char		*ft_strjoin_no_free(char *s1, char *s2);
char		*ft_strjoin_free_s2(char *s1, char *s2);

#endif 
