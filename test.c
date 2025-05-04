#include <stdio.h>
#include <string.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
// 2147483648
// ifd fd
int num_length(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (strncmp(str, "2147483648", 10) >= 0)
		return (1);
	return (0);

}

int is_space(char *str)
{
	return ((*str == 32) || (*str >= 9 && *str <= 13));
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (is_space(str)) // not important
		str++;
	if (str[i] == '+')
		i++;
	if (num_length(&str[i]))
		return (1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int	op;
	long	final;

	op = 1;
	final = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			op *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		final = (final * 10) + (*str - '0');
		str++;
	}
	return (final * op);
}

int check_numeric(int ac, char **av)
{
	int i;

	i = 1;
	while(i < ac)
	{
		if (ft_isnum(av[i])) // ft_atoi(av[i]) <= 0  redundent idiot
			return (1);
		i++;
	}
	return (0);
}
int check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Number of arguments not valid\n"));
	if (check_numeric(ac, av))
		return (printf("Error in the number\n"));
	return (0);
}

int main(int ac, char **av)
{
	if (check_args(ac, av))
		return (1);
}
