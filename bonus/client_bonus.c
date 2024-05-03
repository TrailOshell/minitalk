/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:04:55 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 18:04:56 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	g_ack_signal;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack_signal = 1;
	else if (sig == SIGUSR2)
		typing("Message sent\n", GREEN);
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

void	sending_message(char **argv, int pid)
{
	while (*argv[2])
		send_char(*(argv[2]++), pid);
	send_char('\0', pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		typing("Input like this -> ./client [PID] [STRING]\n", YELLOW);
	else if (argc == 3)
	{
		pid = mnt_atoi(argv[1]);
		if (pid <= 0)
			typing("Invalid PID!\n", YELLOW);
		else
		{
			sa.sa_flags = 0;
			sa.sa_handler = handler;
			sigemptyset(&sa.sa_mask);
			sigaction(SIGUSR1, &sa, NULL);
			sigaction(SIGUSR2, &sa, NULL);
			sending_message(argv, pid);
		}
	}
	return (0);
}
