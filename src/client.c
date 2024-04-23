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
		typing("Message sent successfully\n", GREEN);
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

void	sending_message(char **argv, int pid)
{
	int					i;

	i = 0;
	g_ack_signal = 0;
	while (argv[2][i])
		send_char(argv[2][i++], pid);
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
			sa.sa_handler = ack_handler;
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = 0;
			sigaction(SIGUSR1, &sa, NULL);
			sigaction(SIGUSR2, &sa, NULL);
			sending_message(argv, pid);
		}
	}
	return (0);
}

//printf("(int)argv[2][i] = \'%c\' %d\n", (int)argv[2][i], (int)argv[2][i]);