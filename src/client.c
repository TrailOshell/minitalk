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

void	send_signal(int bit, int pid)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
		usleep(300);
	}
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			write(1, "Problem sending the signal!\n", 29);
			exit(1);
		}
		usleep(300);
	}
}

void	convert(int c, int pid)
{
	t_byte	byte;

	//*(unsigned char *)&byte = (unsigned char)c;
	*(unsigned char *)&byte = (unsigned char)c;
	//printf("c = \'%c\' %d\n", c, c);
	//printf("byte = \'%c\' %d %d%d%d%d%d%d%d%d\n",
		//*(unsigned char *)&byte, *(unsigned char *)&byte,
		//byte.b1, byte.b2, byte.b3, byte.b4, byte.b5, byte.b6, byte.b7, byte.b8);
	send_signal(byte.b1, pid);
	send_signal(byte.b2, pid);
	send_signal(byte.b3, pid);
	send_signal(byte.b4, pid);
	send_signal(byte.b5, pid);
	send_signal(byte.b6, pid);
	send_signal(byte.b7, pid);
	send_signal(byte.b8, pid);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi((const char *)argv[1]);
		if (pid == 0 || pid < 0)
		{
			write(1, "Invalid PID!\n", 13);
			return (0);
		}
		while (argv[2][i])
		{
			//printf("(int)argv[2][i] = \'%c\' %d\n", (int)argv[2][i], (int)argv[2][i]);
			convert((int)argv[2][i], pid);
			i++;
		}
	}
	else
		write(1, "Usage: ./client [PID] [STRING_TO_PASS]\n", 40);
	return (0);
}
