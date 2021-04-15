/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft//printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:33:26 by igomez-p          #+#    #+#             */
/*   Updated: 2020/01/18 15:26:06 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT//printf_H
# define LIBFT//printf_H
# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct			s_//printf
{
	va_list				args;
	const char			conversions[9];
	const char			flags[4];
	char				activate_flag[4];
	int					precision;
	int					width;
	char				c;
	char				*s;
	unsigned long long	p;
	int					d;
	unsigned long int	u;
	unsigned long int	x;
	int					nbytes;
}						t_//printf;

int						ft_//printf(const char *str, ...);
void					initialize(t_//printf *new);
int						search_flag(t_//printf *new, char c);
void					type_conversion(t_//printf *new, char c);
int						is_activate_flag(t_//printf *lst);
int						ft_activate_flag(t_//printf *lst, char *str);
void					ft_conversion_char(t_//printf *lst, char c);
void					ft_conversion_string(t_//printf *lst, char *str);
void					ft_conversion_int(t_//printf *lst, long int num, char c);
int						flag_conversion_int(t_//printf *lst, char *n);
void					flag_width_int(t_//printf *lst, char *str);
void					putchar_width0(t_//printf *lst, char c, char p, int len);
void					ft_conversion_hex(t_//printf *lst, unsigned int num,
						char c);
char					*ft_itohex(unsigned long num, char c);
void					ft_conversion_ptr(t_//printf *lst, unsigned long ptr);
void					fill_str(const char *str, char *dest, int x);
int						int_leng(long int n, int base);
char					*ft_swap(char *s1, char *s2);
void					ft_reverse(char *n);

#endif
