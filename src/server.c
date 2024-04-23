/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:57:25 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/18 12:57:27 by tsomchan         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */

#include "../inc/minitalk.h"

void	handler(int sig)
{
	static char	c = 0b00000000;
	static int	i = 0;

	if (sig == SIGUSR2)
		c |= (0b10000000 >> i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		c = 0b00000000;
		i = 0;
	}
}


int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

/*
	if (!i)
		i = 1;
	if (sig == SIGUSR1)
	{
		set_bit(0, &i, &byte);
		i++;
	}
	if (sig == SIGUSR2)
	{
		set_bit(1, &i, &byte);
		i++;
	}
*/

/*
t_byte		byte;

void	set_bit(int bit, int *i, t_byte *byte)
{
	printf("i = %d ", *i);
	printf("sig = %d ", bit);
	if (bit == 0)
		printf("SIGUSR1\n", SIGUSR1);
	if (bit == 1)
		printf("SIGUSR2\n", SIGUSR2);
	if (*i == 1)
		byte->b1 = bit;
	if (*i == 2)
		byte->b2 = bit;
	if (*i == 3)
		byte->b3 = bit;
	if (*i == 4)
		byte->b4 = bit;
	if (*i == 5)
		byte->b5 = bit;
	if (*i == 6)
		byte->b6 = bit;
	if (*i == 7)
		byte->b7 = bit;
	if (*i == 8)
	{
		byte->b8 = bit;
		write(1, &*(unsigned char *)byte, 1);
		write(1, "\n", 1);
		*i = 0;
		printf("byte->= \'%c\' %d %d%d%d%d%d%d%d%d\n",
			*(unsigned char *)byte, *(unsigned char *)byte,
			byte->b1, byte->b2, byte->b3, byte->b4,
			byte->b5, byte->b6, byte->b7, byte->b8);
	}
	printf("byte->= \'%c\' %d %d%d%d%d%d%d%d%d\n",
		*(unsigned char *)byte, *(unsigned char *)byte,
		byte->b1, byte->b2, byte->b3, byte->b4,
		byte->b5, byte->b6, byte->b7, byte->b8);
}
*/