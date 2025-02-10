/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:23 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/10 15:45:14 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Signal handler for SIGUSR1 and SIGUSR2, reconstructing characters.
 *
 * This function handles signals sent to reconstruct a character bit by bit.
 * 
 * It interprets SIGUSR1 as a '1' and SIGUSR2 as a '0', building an 8-bit 
 * character. 
 * 
 * Once a full character is received, it is printed to standard output.
 * 
 * If a null character (`'\0'`) is received, it signals back to confirm receipt.
 *
 * @param signo The received signal (SIGUSR1 or SIGUSR2).
 * @param info A pointer to a `siginfo_t` structure containing sender 
 * information.
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

/**
 * SERVER
 * 
 * Display server PID
 * Create an endless loop so that the server can 
 * 		receive signals at any time.
 * Receive signals
 * Decrypt signals
 */
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
