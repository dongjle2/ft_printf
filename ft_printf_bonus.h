/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 21:05:02 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/02 18:20:34 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
#define FT_PRINTF_BONUS_H
#include <stdarg.h>
#include "libft/libft.h"
#define FORMATS "cspdiuxX%"
#define FLAGS "+ -#0"

typedef union u_nums
{
	unsigned long long	ull;
	unsigned int		ui;
	int					i;
}	t_nums;

// typedef struct s_nums
// {
// 	unsigned long long	ull;
// 	unsigned int		ui;
// 	int					i;
// }	t_nums;

typedef struct s_packet
{
	t_nums	val;
	char	fmt;
	char	plus_flag;
	char	minus_flag;
	char	space_flag;
	char	hash_flag;
	char	pad_flag;
	int		width;
	int		precision;
	char	chr;
	char	*pstr;
}	t_packet;

typedef struct s_display
{
	int		digit_len;
	int		strlen;
	int		num_space;
	int		num_zero;
	short	prefix;
	char	space_location;
	char	sign;
	char	*itoa;
}	t_display;

int			begin_rd(const char *s, va_list ap, int *ret_val);
char		*cp_s_to_calloc(const char *s);
int		prt_pkt(t_packet *k, va_list ap, int *ret_val);
int		prt_c(t_packet *k, t_display *d, va_list ap, int *ret_val);
int	prt_s(t_packet *k, t_display *d, va_list ap, int *ret_val);
int			prt_p(t_packet *k, t_display *d, va_list ap, int *ret_val);
int			prt_x(t_packet *k, t_display *d, va_list ap, int *ret_val);
int			prt_u(t_packet *k, t_display *d, va_list ap, int *ret_val);
void	check_format(t_packet *k, char *pmem);
void		init_packet(t_packet *k);
void		check_flags(t_packet *k, char **mem);
void		check_width(t_packet *k, char **mem);
void		check_precision(t_packet *k, char **pmem);
int			rd_mem_to_pkt(t_packet *k, char *mem);
char		*ft_numtoa(t_nums val, char *mode);
int			check_sign(t_nums *val, char *sign, char *mode);
int			ft_ulllen(unsigned long long n, int l);
int			ft_uilen(unsigned int n, int l, char *fmt);
int			ft_ilen(int n, int l);
void		ft_str_toupper(char *s);
int		prt_d(t_packet *k, t_display *d, va_list ap, int *ret_val);
int			ft_printf(const char *s, ...);
void		init_t_display(t_display *d);
static void		set_t_display(t_display *d, t_packet *k);
static int	print_display(t_display *d, t_packet *k, int *ret_val);
static int	print_padding(t_display *d, int *ret_val);
static int	print_space(t_display *d, t_packet *k, int *ret_val);
int				ft_max(long long a, long long b);
int				ft_min(long long a, long long b);
#endif