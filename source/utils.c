/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:10:47 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/31 12:57:52 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Prints an error message and terminates the program.
 * @param error_msg A pointer to the null-terminated string 
 * containing the error message to display.
 */
void	ft_error_exit(const char *error_msg)
{
	printf(RED"%s"RST, error_msg);
	exit(EXIT_FAILURE);
}

void	ft_signal(int signo, void *handler, bool use_siginfo)
{
	struct sigaction	sa = {0};

	if (use_siginfo)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
		ft_error_exit("Error. sigaction failed\n");
}

void	ft_kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
		ft_error_exit("Error: Kill failed\n");
}
