#include "../printf.h"
#include "../libft/libft.h"

int ft_print_sumbols(char c, int num)
{
	int i;

	i = num;
	while (i-- > 0)
		write(1, &c, 1);
	return (num);
}
