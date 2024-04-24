/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:57:25 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 00:57:41 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	check_diff_pid(int pid)
{
	static int	store_pid;
	int			isdiff;

	isdiff = 0;
	if (store_pid != pid)
	{
		isdiff = 1;
		store_pid = pid;
		typing("\nDifferent client PID found, byte now reset\n", YELLOW);
	}
	return (isdiff);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c = 0b00000000;
	static int	i = 0;
	int			client_pid;

	(void)ucontext;
	client_pid = info->si_pid;
	if (check_diff_pid(client_pid) == 1)
	{
		c = 0b00000000;
		i = 0;
	}
	if (sig == SIGUSR2)
		c |= (0b10000000 >> i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(client_pid, SIGUSR2);
		else
			write(1, &c, 1);
		c = 0b00000000;
		i = 0;
		usleep(200);
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	typing("Server PID: ", PURPLE);
	set_color(PURPLE);
	mnt_putnbr(getpid());
	write(1, "\n", 1);
	set_color(RESET_C);
	while (1)
		pause();
	return (0);
}
