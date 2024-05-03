/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:04:45 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 18:04:46 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	check_diff_pid(int pid)
{
	static int	store_pid;

	if (store_pid != pid)
	{
		store_pid = pid;
		typing("\nDifferent client PID found, byte now reset\n", YELLOW);
		return (1);
	}
	return (0);
}

void	reset_byte(char *c, int *i)
{
	*c = 0b00000000;
	*i = 0;
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	c = 0b00000000;
	static int	i = 0;
	int			client_pid;

	(void)ucontext;
	client_pid = info->si_pid;
	if (check_diff_pid(client_pid) == 1)
		reset_byte(&c, &i);
	if (sig == SIGUSR2)
		c |= (0b10000000 >> i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(client_pid, SIGUSR2);
		else
			write(1, &c, 1);
		reset_byte(&c, &i);
		usleep(1000);
	}
	usleep(50);
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
	typing("Server_BONUS PID: ", PURPLE);
	set_color(PURPLE);
	mnt_putnbr(getpid());
	write(1, "\n", 1);
	set_color(RESET_C);
	while (1)
		pause();
	return (0);
}
