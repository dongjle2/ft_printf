#include <stdio.h>
#include <limits.h>
#include "./ft_printf_bonus.h"
int	main(void)
{
	// ft_printf("ft%.i\n", 0);
	// ft_printf("ft%.0i\n", 0);
	ft_printf("ft%.3i\n", 0);
	ft_printf("ft%04d\n", 0);
	ft_printf("ft%04.0d\n", 0);
	ft_printf("ft%04.0d\n", 1);
	// printf("og%.i\n", 0);
	// printf("og%.0i\n", 0);
	// printf("og%.3i\n", 0);
	// printf("og%04d\n", 0);
	// printf("og%04.0d\n", 0);
	// printf("og%04.0d\n", 1);
	// printf("%08.5d\n", -34);
	// printf("%08.d\n", -34);
	// printf("%08.1d\n", -34);
	// printf("%08.2d\n", -34);
	// printf("%08.3d\n", -34);
	// printf("%8.3d\n", -34);
	// ft_printf("%08.5d\n", -34);
	// ft_printf("%08.d\n", -34);
	// ft_printf("%08.1d\n", -34);
	// ft_printf("%08.2d\n", -34);
	// ft_printf("%08.3d\n", -34);
	// ft_printf("%8.3d\n", -34);

	// printf("%7i\n", -12);
	// ft_printf("%7i\n", -12);
	// printf("%  d\n", 1);
	// ft_printf("%  d\n", 1);
	return (0);
}