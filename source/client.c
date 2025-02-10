/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:21 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/10 15:43:22 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/*	Global flag for synchronization between client and server */
volatile sig_atomic_t	g_server_pid = BUSY;

/**
 * @brief Signal handler to acknowledge message reception.
 *
 * This function sets `g_server_pid` to `READY`, indicating that 
 * the server has acknowledged a received bit.
 */
static void	ft_ack_handler(void)
{
	g_server_pid = READY;
}

/**
 * @brief Signal handler to indicate the end of message transmission.
 *
 * Prints a confirmation message and exits the program successfully.
 */
static void	ft_end_handler(void)
{
	write(STDOUT_FILENO, "\t✅ Message received ✅\n", 27);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Validates the program arguments.
 *
 * This function checks if the correct number of arguments is provided 
 * and ensures that the first argument (PID) consists only of digits.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return 1 if arguments are valid, 0 otherwise.
 */
static int	check_for_valid_argv(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return (0);
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Sends a character bit by bit using signals.
 *
 * This function sends each bit of the given character to the specified process
 * using SIGUSR1 (for bit 1) and SIGUSR2 (for bit 0). 
 * 
 * It waits for an acknowledgment from the server before sending the next bit.
 *
 * @param c The character to send.
 * @param pid The process ID of the receiver.
 */
void	ft_send_char(char c, pid_t pid)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0x80) >> bit)
			ft_kill(pid, SIGUSR1);
		else
			ft_kill(pid, SIGUSR2);
		++bit;
		while (g_server_pid == BUSY)
			usleep(50);
		g_server_pid = BUSY;
	}
}

/**
 * CLIENT
 * Takes two parameters
 * 
 * - The PID of the server
 * - The message to send
 * 
 * Encrypt the message (encryption via bits)
 * Send the message to the server (PID)
 * Create a stop condition
 */
int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message_to_send;
	int		i;

	if (!check_for_valid_argv(argc, argv))
		ft_error_exit("Error: Wrong input given\n" RST
			"Expected: ./client <server_pid> \"message_to_send\"\n");
	pid = ft_atoi(argv[1]);
	message_to_send = argv[2];
	ft_signal(SIGUSR1, ft_ack_handler, false);
	ft_signal(SIGUSR2, ft_end_handler, false);
	i = 0;
	while (message_to_send[i])
		ft_send_char(message_to_send[i++], pid);
	ft_send_char('\0', pid);
	return (EXIT_SUCCESS);
}
