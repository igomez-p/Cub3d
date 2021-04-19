#include "../inc/libft.h"

int	ft_isprint(int c)
{
	return ((c >= 32 && c <= 126) ? 1 : 0);
}

int         ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57) ? 1 : 0);
}

int			ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sig;

	num = 0;
	sig = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
	{
		sig = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (num * sig > 2147483647)
		return (-1);
	//else if ((long int)(num * sig) < -2147483648)
	//	return (0);
	return (num * sig);
}