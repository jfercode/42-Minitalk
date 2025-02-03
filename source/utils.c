/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:10:47 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/03 10:59:46 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * @brief Prints an error message and terminates the program.
 *
 * This function prints the provided error message in red and 
 * then exits the program with a failure status.
 *
 * @param error_msg A pointer to a null-terminated string containing 
 * the error message to display.
 */
void	ft_error_exit(const char *error_msg)
{
	printf(RED"%s"RST, error_msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Sets up a signal handler for SIGUSR1 or SIGUSR2.
 *
 * This function configures a signal handler for SIGUSR1 or SIGUSR2, allowing 
 * the user to specify a custom handler function. 
 * 
 * It also provides an option to use `SA_SIGINFO` 
 * to receive additional information about the signal.
 *
 * @param signo The signal to handle (SIGUSR1 or SIGUSR2).
 * @param handler A function pointer to handle the received signal.
 * @param use_siginfo A boolean flag indicating whether to use `SA_SIGINFO` 
 * for extended signal information.
 */
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

/**
 * @brief Sends a signal to a process.
 *
 * This function attempts to send the specified signal to 
 * the given process ID (PID).
 * 
 * If the operation fails, the program exits with an error message.
 * 
 * @param pid The process ID to which the signal will be sent.
 * @param signo The signal to be sent.
 */
void	ft_kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
		ft_error_exit("Error: Kill failed\n");
}
