/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:13:34 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/23 19:13:35 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	set_color(char *color)
{
	int	len;

	len = 7;
	if (mnt_strcmp(color, RESET_C) == 1)
		len = 4;
	write(1, color, len);
}

void	write_color(char *s, char *color)
{
	set_color(color);
	write(1, s, mnt_strlen(s));
	set_color(RESET_C);
}

void	typing(char *s, char *color)
{
	int	i;
	int	j;
	int	len;

	set_color(color);
	while (*s == '\n')
		write(1, &(*(s++)), 1);
	len = mnt_strlen(s);
	j = 0;
	while (j < len)
	{
		i = 0;
		while (i <= j)
		{
			if (s[i] != '\n')
				write(1, &(s[i]), 1);
			i++;
		}
		j++;
		if (j != len)
			write(1, "\r", 1);
		usleep(10000);
	}
	write(1, "\r", 1);
	write(1, s, len);
	set_color(RESET_C);
}
