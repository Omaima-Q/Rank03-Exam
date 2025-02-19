/*Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but 
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Obs: Your function must not have memory leaks. Moulinette will test that.*/


#include <unistd.h>
#include <stdarg.h>

void	put_str(char *str, int *count)
{
	int	i = 0;

	if (!str)
		str = "(null)";
	while (str[i])
		*count += write(1, &str[i++], 1);
	return ;
}

void	put_nbr(long long int num, int base, int *count)
{
	char *hexa = "0123456789abcdef";

	if (num < 0)
	{
		*count += write(1, "-", 1);
		num *= -1;
	}
	if (num >= base)
		put_nbr(num / base, base, count);
	*count += write(1, &hexa[num % base], 1);
	return ;
}

static int	checktype(char spe, va_list ap)
{
	int	count = 0;

	if (spe == 's')
		put_str(va_arg(ap, char *), &count);
	else if (spe == 'd')
		put_nbr((long long int)va_arg(ap, int), 10, &count);
	else if (spe == 'x')
		put_nbr((long long int)va_arg(ap, unsigned int), 16, &count);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int	count = 0;
	int	i = 0;
	va_list	ap;

	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && (format[i + 1] == 's'
				|| format[i + 1] == 'd' || format[i + 1] == 'x'))
		{
			count += checktype(format[++i], ap);
		}
		else
		{
			count += write(1, &format[i], 1);
		}
		i++;
	}
	va_end(ap);
	return (count);
}

// int	main(void)
// {
// 	ft_printf("\n");
// 	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// 	ft_printf("Magic %s is %d\n", "number", -8000000);
// 	ft_printf("%s\n", "toto");
// 	return (0);
// }
