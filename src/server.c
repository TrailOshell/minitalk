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

void	handler(int sig, siginfo_t *info, void *u)
{
	static char	c = 0b00000000;
	static int	i = 0;
	int			client_pid;

	(void)u;
	client_pid = info->si_pid;
	if (sig == SIGUSR2)
		c |= (0b10000000 >> i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(client_pid, SIGUSR1);
		else
			write(1, &c, 1);
		c = 0b00000000;
		i = 0;
	}
	kill(client_pid, SIGUSR2);
}

void	ft_putnbr(int num)
{
	char	c;

	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		c = num + '0';
		write(1, &c, 1);
		usleep(20000);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	set_color(PURPLE);
	typing("PID: ", PURPLE);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	set_color(RESET_C);
	while (1)
		pause();
	return (0);
}
