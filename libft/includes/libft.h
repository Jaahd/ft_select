/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:49:05 by avacher           #+#    #+#             */
/*   Updated: 2016/01/13 19:32:15 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_duo
{
	char			*name;
	char			*value;
	struct s_duo	*next;
}					t_duo;

typedef struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int i, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *str, int i, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int i);
int					ft_isdigit(int i);
int					ft_isalnum(int i);
int					ft_isascii(int i);
int					ft_isprint(int i);
int					ft_toupper(int i);
int					ft_tolower(int i);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(const char *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putchar_fd(char c, int fd);

t_list				*ft_lstnew(char *content);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void				ft_putnbrendl(int n);
int					ft_strnlen(char *str, char c);
void				ft_lstpushback(t_list **alst, char *new);
char				*ft_itoa_base(int n, int base);
t_list				*ft_split_to_lst(const char *s, char c);
t_duo				*tbl_to_duo(char **tbl, char c);
char				*srch_begining(const char *str, int c);
char				*srch_value(const char *str, int c);
int					duo_pushback(t_duo **lst, char *name, char *value);
int					duo_del(t_duo **lst);
int					free_tab(char ***tab);
char				**lst_to_tbl(t_list *lst);
int					ft_lst_count(t_list *lst);
int					tbl_len(char **tbl);
void				ft_free_tbl_s(char **tbl);
char				*ft_properjoin(char *s1, char *s2);
int					ft_atoi_base(char *str, int base);
int					ft_hidenp(char *hiden, char *str);
void				ft_swap(char **s1, char **s2);
void				int_swap(int *i, int *j);
int					intcmp(int a, int b);

#endif
