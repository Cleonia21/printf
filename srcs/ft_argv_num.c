#include "../printf.h"
#include "../libft/libft.h"

static void			ft_make_num(unsigned int num, unsigned int radix, int reg, int *bytes_num)
{
	if (num > radix - 1)
	{
		ft_make_num(num / radix, radix, reg, bytes_num);
	}
	bytes_num += ft_putchar(ft_convert_to_six(num % radix, reg));
}

static void			ft_flag_sumbols(t_param *f, t_mod *mod)
{
	if (f->precision > mod->numlen)
		mod->null_num = f->precision - mod->numlen;
	if (f->width > mod->numlen + mod->null_num + mod->sign)
	{
		if (f->flag == 1)
			mod->space_after = f->width - mod->null_num - mod->numlen + mod->sign;
		if (f->flag == 0)
		{
			if (f->precision > 0)
				mod->space_before = f->width - mod->null_num - mod->numlen + mod->sign;
			else
				mod->null_num = f->width - mod->numlen + mod->sign;
		}
		if (f->flag == -1)
			mod->space_before = f->width - mod->null_num - mod->numlen + mod->sign;
	}
}

static t_mod		ft_initialization()
{
	t_mod mod;

	mod.null_num = 0;
	mod.numlen = 0;
	mod.sign = 0;
	mod.space_after = 0;
	mod.space_before = 0;
	return (mod);
}

static unsigned int	ft_convert_num(unsigned int num, t_mod *mod)
{
	if ((int)num < 0)
	{
		num = (int)num * -1;
		mod->sign = -1;
	}
	return (num);
}

int ft_argv_num(t_param *f, int radix, int reg, unsigned int num)
{
	t_mod	mod;
	int		bytes_num;

	mod = ft_initialization();
	if (reg == -1)
		num = ft_convert_num(num, &mod);
	mod.numlen = ft_numlen(num, radix);
	ft_flag_sumbols(f, &mod);
	bytes_num = ft_print_sumbols(' ', mod.space_before);
	if (mod.sign == -1)
		bytes_num += ft_putchar('-');
	bytes_num += ft_print_sumbols('0', mod.null_num);
	if (num != 0 || f->precision != 0)
	{
		ft_make_num(num, radix, reg, &bytes_num);
		bytes_num += mod.numlen;
	}
	else if (f->width > 0)
		bytes_num += ft_putchar(' ');
	bytes_num += ft_print_sumbols(' ', mod.space_after);
	return (bytes_num);
}
