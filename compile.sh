cc -g ft_printf_bonus_copy.c fmt_*.c ft_numtoa.c ft_printf_helper.c
cc -g *.o -L./libft -lft
./a.out | cat -e