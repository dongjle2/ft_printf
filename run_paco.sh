gcc -g -c ft_printf_bonus.c ft_numtoa.c ft_printf_helper.c ft_printf_c_bonus.c
make -C libft re
gcc -g ft_printf_bonus.o ft_numtoa.o ft_printf_helper.o ft_printf_c_bonus.o -L./libft -lft
make bonus
/Users/dongjle2/francinette/tester.sh -in -b