/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:57:37 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/18 12:57:40 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	g_ack_signal;

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "\nMessage sent successfully\n", 27);
	else if (sig == SIGUSR2)
		g_ack_signal = 1;
	return ;
}

void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack_signal = 0;
		if (c & (0b10000000 >> i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		while (!g_ack_signal)
			pause();
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

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;
	int					i;

	if (argc != 3)
		write(1, "Usage: ./client [PID] [STRING_TO_PASS]\n", 40);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Invalid PID!\n", 13);
		return (0);
	}
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	g_ack_signal = 0;
	while (argv[2][i])
		send_char((int)argv[2][i++], pid);
	send_char('\0', pid);
	return (0);
}

//printf("(int)argv[2][i] = \'%c\' %d\n", (int)argv[2][i], (int)argv[2][i]);