/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:16:14 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 00:40:21 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

size_t	mnt_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

int	mnt_atoi(char *str)
{
	long	num;
	int		idx;
	int		sign;

	num = 0;
	idx = 0;
	sign = 1;
	while (str[idx] == ' ')
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		num = num * 10;
		num = num + str[idx] - '0';
		if (num < -2147483648 || num > 2147483647)
			break ;
		idx++;
	}
	return (num * sign);
}

void	mnt_putnbr(int num)
{
	char	c;

	if (num >= 10)
	{
		mnt_putnbr(num / 10);
		mnt_putnbr(num % 10);
	}
	else
	{
		c = num + '0';
		write(1, &c, 1);
		usleep(20000);
	}
}
