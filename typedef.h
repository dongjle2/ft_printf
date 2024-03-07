/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongjle2 <dongjle2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:34:43 by dongjle2          #+#    #+#             */
/*   Updated: 2024/03/04 20:35:16 by dongjle2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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