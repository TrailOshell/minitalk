/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:37:05 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/18 13:37:06 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

static size_t	check(size_t n, const char *nptr, int sign)
{
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = *nptr - '0' + (n * 10);
		nptr++;
	}
	return (n * sign);
}

int	ft_atoi(const char *nptr)
{
	size_t	n;
	int		sign;
	int		d;

	d = 0;
	sign = 1;
	n = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		d++;
		nptr++;
	}
	if (d > 1)
		return (n);
	n = check(n, nptr, sign);
	return (n);
}

