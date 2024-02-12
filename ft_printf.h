/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:03:25 by dongjle2          #+#    #+#             */
/*   Updated: 2024/02/08 00:55:45 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft/libft.h"

typedef union u_nums
{
	unsigned long long	ull;
	unsigned int		ui;
	int					i;
}	t_nums;

typedef struct s_packet
{
	t_nums	val;
	char	fmt;
	char	plus_flag;
	char	minus_flag;
	char	space_flag;
	char	hash_flag;
	int		width;
	char	pad_flag;
	int		precision;
	unsigned char	chr;		//no need if stored in val
	char	*pstr;		//no need if stored in val
	char	complete;	//too hard
}	t_packet;

int			begin_rd(const char *s, va_list ap, int *ret_val);
char		*cp_s_to_calloc(const char *s, const char *formats);
void		prt_pkt(t_packet *k, int *ret_val);
int			prt_c(t_packet *k, int *ret);
int			prt_s(t_packet *k, int *ret_val);
int			prt_p(t_packet *k, int *ret_val);
int			prt_xX(t_packet *k, int *ret_val);
int			prt_xX_hard(t_packet *k, char **output_mem, size_t strlen, char *itoa);
void		init_packet(t_packet *k);
void		check_flags(t_packet *k, char **mem);
void		check_width(t_packet *k, char **mem);
void		check_format(va_list ap, t_packet *k, char *mem);
void		check_precision(t_packet *k, char **pmem);
int			rd_mem_to_pkt(t_packet *k, char *mem, va_list ap, const char *formats);
char		*ft_numtoa(t_nums val, char *mode);
int			check_sign(t_nums *val, char *sign, char *mode);
int			ft_ulllen(unsigned long long n, int l);
int			ft_uilen(unsigned int n, int l, char *fmt);
int			ft_ilen(int n, int l);
void		ft_str_toupper(char *s);
char		*prt_p_ez(int *ret_val, size_t strlen, char *itoa);
int			prt_d(t_packet *k, int *ret_val);
int			prt_percent(t_packet *k, int *ret_val);
char		*prt_p_hard(t_packet *k, size_t strlen, char *itoa);
int			ft_printf(const char *s, ...);
void	prt_c_null_given(t_packet *k, int *ret_val);
void	prt_c_core(t_packet *k, char *output_mem);
