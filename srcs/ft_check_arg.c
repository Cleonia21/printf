#include "../printf.h"
#include "../libft/libft.h"

char *ft_check_arg(char *str)
{
    if (!str)
        return ("(null)");
    else
        return (str);
}
