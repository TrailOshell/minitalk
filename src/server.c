/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:57:25 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/18 12:57:27 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

t_byte		char_byte;

void	set_bit(int bit, int	*i, t_byte char_byte)
{
	if (*i == 1)
		char_byte.b1 = bit;
	if (*i == 2)
		char_byte.b2 = bit;
	if (*i == 3)
		char_byte.b3 = bit;
	if (*i == 4)
		char_byte.b4 = bit;
	if (*i == 5)
		char_byte.b5 = bit;
	if (*i == 6)
		char_byte.b6 = bit;
	if (*i == 7)
		char_byte.b7 = bit;
	if (*i == 8)
	{
		char_byte.b8 = bit;
		write(1, &*(unsigned char *)&char_byte, 1);
		*i = 0;
	}
}

void	handler(int sig)
{
	static int	i;

	printf("SIGUSR1 = %d ", SIGUSR1);
	printf("SIGUSR2 = %d\n", SIGUSR2);
	printf("sig = %d ", sig);
	printf("i = %d\n", i);
	if (!i)
		i = 1;
	if (sig == SIGUSR1)
	{
		set_bit(0, &i, char_byte);
		i++;
	}
	if (sig == SIGUSR2)
	{
		set_bit(1, &i, char_byte);
		i++;
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
	{
		//write(1, "pausing\n", 8);
		pause();
		//write(1, "unpaused\n", 9);
	}
	return (0);
}