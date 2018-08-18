/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyevresh <eyevresh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:29:00 by eyevresh          #+#    #+#             */
/*   Updated: 2018/02/23 13:13:45 by eyevresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <locale.h>
# include <time.h>
# include "libft.h"

typedef struct s_conv_map	t_conv_map;
typedef struct s_conversion	t_conversion;
typedef char	*(t_conv_func)(t_conversion *new_conv, va_list ap);

struct			s_conv_map
{
	char		id;
	t_conv_func	*conv_func;
};

struct			s_conversion
{
	int			conv_arg_number;
	char		flags[7];
	int			field_width;
	int			width_arg_number;
	int			precision;
	int			precision_arg_number;
	char		length_modifier[3];
	char		conversion_name;
	int			zero_res;
	int			n_r;
	t_conv_map	conv_map;
};

extern int			g_positional_arg;
extern t_conv_map	g_conv_map[];

/*
** <ft_printf>
*/
int				ft_vdprintf(int fd, const char *format, va_list ap);
int				ft_vsprintf(char *str, const char *format, va_list ap);
int				ft_vsnprintf(char *str, size_t size,
	const char *format, va_list ap);
int				ft_vasprintf(char **ret, const char *format, va_list ap);

/*
** <heleprs>
*/
void			handle_text(char **input, int *size, int fd);
int				handle_conversion(va_list ap, char **input,
	int *size, int fd);
void			print_conversion_result(char *result, int pure_hate,
	int *size, int fd);
void			get_text(char **result, char **input);
char			*get_base_for_conv(char c);
int				get_color(char **input, char **color);

/*
** <conversion>
*/
int				do_conversion(va_list ap, char **result, char **input,
	int *h);
t_conversion	*get_conv_data(char **input, va_list ap);
t_conversion	*alloc_new_conversion(void);
char			*positional_conversion(t_conversion *c, va_list ap, int *h);
char			*unpositional_conversion(t_conversion *c, va_list ap, int *h);
char			*get_final_conversion_res(t_conversion *new_conv,
		char *result, int *h);
char			*include_precision(t_conversion *new_conv, char *result);
char			*include_field_width(t_conversion *new_conv, char *result);
char			*handle_flags(t_conversion *conv, char *result);
char			*optimize_zero_or_negative_result(t_conversion *conv,
		char *result);
char			*handle_c_conv_zero_result(t_conversion *conv, char *result,
	int *h);
void			handle_pos_width_prec(t_conversion *conv, va_list ap,
	int flag);
void			get_positional_conv(t_conversion *conv, va_list copy);

/*
** <precision handleres>
*/
char			*handle_dioux_prec(t_conversion *new_conv, char *result);
char			*handle_s_prec(t_conversion *new_conv, char *result);
char			*handle_p_prec(t_conversion *new_conv, char *result);

/*
** <strange cases>
*/
int				get_n_conversion(t_conversion *conv, char **result);
void			handle_n_conversion(int size, int flag, va_list ap);
char			*handle_p_width(char *result, char *tmp);
char			*reset_for_p_conv(char *result);

/*
** <conversion functions>
*/
char			*di_conversion(t_conversion *conv, va_list ap);
char			*ouxb_conversion(t_conversion *conv, va_list ap);
char			*c_conversion(t_conversion *conv, va_list ap);
char			*s_conversion(t_conversion *conv, va_list ap);
char			*p_percent_coversion(t_conversion *conv, va_list ap);
char			*f_conversion(t_conversion *conv, va_list ap);
char			*e_conversion(t_conversion *conv, va_list ap);
char			*g_conversion(t_conversion *conv, va_list ap);
char			*a_conversion(t_conversion *conv, va_list ap);
char			*r_conversion(t_conversion *conv, va_list ap);
char			*k_conversion(t_conversion *conv, va_list ap);
char			*y_conversion(t_conversion *conv, va_list ap);
char			*q_conversion(t_conversion *conv, va_list ap);

/*
** <flags_handlers>
*/
char			*handle_sharp_flag(t_conversion *conv, char *result);
char			*handle_plus_flag(t_conversion *conv, char *result);
char			*handle_space_flag(t_conversion *conv, char *result);
char			*handle_zero_flag(t_conversion *c, char *result);
char			*handle_negative_result(t_conversion *conv, char *result);
char			*handle_apostrophe_flag(char *result);

/*
** <conversion parser functions>
*/
void			get_pos_arg_number(t_conversion *new_conv, char **input);
void			get_flags(t_conversion *new_conv, char **input);
void			get_field_width(t_conversion *new_conv, char **input,
	va_list ap);
void			get_precision(t_conversion *new_conv, char **input,
	va_list ap);
void			get_length_modifier(t_conversion *new_conv, char **input);
int				check_if_positional_prec(t_conversion *conv, char *str,
	size_t *i);
int				check_if_positional_width(t_conversion *conv, char *str,
	size_t *i);
void			get_conversion_id(t_conversion *new_conv, char **input);
int				validate_conv_input(t_conversion *conv);

/*
** <input optimization>
*/
void			optimize_flags_modifier_id(t_conversion *new_conv);
void			optimize_sharp_flag(t_conversion *conv);
void			optimize_zero_minus_flag(t_conversion *conv);
void			optimize_space_plus_flag(t_conversion *conv);
void			optimize_apostrophe(t_conversion *conv);
void			optimize_length_modifier(t_conversion *new_conv);
void			optimize_conv_id(t_conversion *new_conv);
void			optimize_width_precision(t_conversion *new_conv);
void			optimize_negative_value(t_conversion *conv);

#endif
