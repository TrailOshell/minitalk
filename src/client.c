/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:57:37 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 00:40:37 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	send_char(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (0b10000000 >> i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i++;
		usleep(500);
	}
}

void	sending_message(char **argv, int pid)
{
	while (*argv[2])
	{
		send_char(*(argv[2]), pid);
		argv[2]++;
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		typing("Input like this -> ./client [PID] [STRING]\n", YELLOW);
	else if (argc == 3)
	{
		pid = mnt_atoi(argv[1]);
		if (pid <= 0)
			typing("Invalid PID!\n", YELLOW);
		else
			sending_message(argv, pid);
	}
	return (0);
}
