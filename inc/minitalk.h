/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:58:29 by tsomchan          #+#    #+#             */
/*   Updated: 2024/04/24 00:51:53 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

// # include <stdio.h>

# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET_C "\033[0m"

// color.c
void	set_color(char *color);
void	write_color(char *s, char *color);
void	typing(char *s, char *color);

// util.c
size_t	mnt_strlen(char *s);
int		mnt_strcmp(char *s1, char *s2);
int		mnt_atoi(char *str);
void	mnt_putnbr(int num);

#endif