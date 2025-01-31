/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:23 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/31 12:56:46 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * SERVER FUCNTION
 * 1- Display server PID 
 * 2- Create an endless loop so that the server can 
 * 		receive signals at any time
 * 3- Receive signals
 * 4- Decrypt signals
 */

static void	handler(int signo, siginfo_t *info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client_pid = 0;

	if (info->si_pid)
		client_pid = info->si_pid;
	if (SIGUSR1 == signo)
		c |= (0b10000000 >> bit);
	else if (SIGUSR2 == signo)
		c &= ~(0x80 >> bit);
	++bit;
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			ft_kill(client_pid, SIGUSR2);
			c = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	ft_kill(client_pid, SIGUSR1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		ft_error_exit("Error: Wrong input given\n" RST
			"Expected: ./server\n");
	printf("SERVER_PID: %d\n", getpid());
	ft_signal(SIGUSR1, handler, true);
	ft_signal(SIGUSR2, handler, true);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
