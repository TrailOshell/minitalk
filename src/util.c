/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:16:14 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/23 19:16:17 by tsomchan         ###   ########.fr       */
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

int	mnt_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	return (1);
}

char	*mnt_strdup(char *str)
{
	char	*dupe;
	int		i;

	i = 0;
	while (str[i])
		i++;
	dupe = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		dupe[i] = str[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}

int	mnt_atoi(char *str)
{
	long	num;
	int		len;
	int		sign;

	num = 0;
	len = 0;
	sign = 1;
	while (str[len] == ' ')
		len++;
	if (str[len] == '-' || str[len] == '+')
	{
		if (str[len] == '-')
			sign = -1;
		len++;
	}
	while (str[len] >= '0' && str[len] <= '9')
	{
		num = num * 10;
		num = num + str[len] - '0';
		if (num < -2147483648 || num > 2147483647)
			break ;
		len++;
	}
	return (num * sign);
}
