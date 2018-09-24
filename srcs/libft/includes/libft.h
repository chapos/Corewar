/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:52:26 by eyevresh          #+#    #+#             */
/*   Updated: 2018/09/24 09:15:37 by oevtushe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <wchar.h>
# include "lists.h"
# include "colors.h"
# define FT_ABS(x) (((x) < 0) ? -(x) : (x))

typedef struct		s_pair
{
	void			*fst;
	void			*scd;
}					t_pair;

/*
** <lists>
*/
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
size_t				ft_lstsize(t_list *lst);

/*
** <printing>
*/
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_puttab(char **table);

/*
** <strings>
*/
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strrev(char *str);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
														size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_front(char *result, char *str);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/*
** <math>
*/
double				ft_power(double nb, int power);
long double			ft_power_long(long double nb, int power);
long				ft_get_rounded_float_value(double value, int precision);
long				ft_get_rounded_float_value_long(long double value,
														int precision);
long				ft_get_float_part_long(long double value, int precision);
long				ft_get_float_part(double value, int precision);
int					ft_factorial(int nb);
int					ft_sqrt(int nb);

/*
** <memory>
*/
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_realloc(void *data, size_t size);
void				ft_memdel(void **ap);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** <conversions>
*/
long long			ft_lltoi(const char *str);
int					ft_atoi(const char *str);
int					ft_atoi_base(const char *str, int str_base);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, char *base);
char				*ft_stoa_base(short value, char *base);
char				*ft_ctoa_base(char value, char *base);
char				*ft_ltoa_base(long value, char *base);
char				*ft_lltoa_base(long long value, char *base);
char				*ft_imaxtoa_base(intmax_t value, char *base);
char				*ft_ssizetoa_base(ssize_t value, char *base);
char				*ft_uitoa_base(unsigned int value, char *base);
char				*ft_ustoa_base(unsigned short value, char *base);
char				*ft_uctoa_base(unsigned char value, char *base);
char				*ft_ultoa_base(unsigned long value, char *base);
char				*ft_ulltoa_base(unsigned long long value, char *base);
char				*ft_uimaxtoa_base(uintmax_t value, char *base);
char				*ft_sizetoa_base(size_t value, char *base);
char				*ft_dtoa(double value, int precision, int flag);
char				*ft_ldtoa(long double value, int precision, int flag);
char				*ft_dtoa_format_e(double value, int precision,
													int c_case, int f);
char				*ft_ldtoa_format_e(long double value, int prec,
													int c_case, int f);
char				*ft_dtoa_format_g(double value, int precision,
													int c_case, int f);
char				*ft_ldtoa_format_g(long double value, int prec,
													int c_case, int f);
char				*ft_dtoa_format_a(double value, int precision,
													int c_case, int f);
char				*ft_ldtoa_format_a(long double value, int prec,
													int c_case, int f);

/*
** <wchar>
*/
unsigned char		*ft_get_wchar(wint_t c);
char				*ft_get_wchar_str(wchar_t *str, int *precision);
size_t				ft_bit_len(unsigned int value);

/*
** <chars>
*/
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_iswhitespace(char c);

/*
** <sorting>
*/
void				ft_bubble_sort(int *array, size_t size);

/*
** <helpers>
*/
size_t				ft_ilen_base(int nb, int base);
size_t				ft_slen_base(short nb, int base);
size_t				ft_llen_base(long nb, int base);
size_t				ft_lllen_base(long long nb, int base);
size_t				ft_imaxlen_base(intmax_t nb, int base);
size_t				ft_ssizelen_base(ssize_t nb, int base);
size_t				ft_clen_base(char nb, int base);
size_t				ft_uilen_base(unsigned int nb, int base);
size_t				ft_uslen_base(unsigned short nb, int base);
size_t				ft_uclen_base(unsigned char nb, int base);
size_t				ft_ullen_base(unsigned long nb, int base);
size_t				ft_ulllen_base(unsigned long long nb, int base);
size_t				ft_uimaxlen_base(uintmax_t nb, int base);
size_t				ft_sizelen_base(size_t nb, int base);
void				ft_swap_int(int *a, int *b);
int					ft_isvldint(char *str);
int					ft_intln(int n);

/*
** <pointers>
*/
char				*ft_get_address(void *address);
void				ft_del_arr_of_pointers(void **table);
int					*ft_range(int min, int max);

/*
** <complex functions>
*/
int					get_next_line(const int fd, char **line);
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_snprintf(char *str, size_t size,
											const char *format, ...);

#endif
