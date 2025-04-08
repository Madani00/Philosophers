#include <stdio.h>

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	op;
	int	final;

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

int check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("try this"));
}

int main(int ac, char **av)
{
	if (check_args(ac, av))
		return (1);

}
