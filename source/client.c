/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:21 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/31 12:55:49 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * CLIENT FUNCTION
 * 1- Write a main in which the client takes two parameters
 * 		- The PID of the server ✔
 * 		- The message to send ✔
 * 2- Encrypt the message (encryption via bits)
 * 3- Send the message to the server (PID)
 * 4- Create a stop condition
 */

/*	Global flag for synchronization between client and server */
volatile sig_atomic_t	g_server_pid = BUSY;

static void	ft_ack_handler(void)
{
	g_server_pid = READY;
}

static void	ft_end_handler(void)
{
	write(STDOUT_FILENO, "\t✅ Message received ✅\n", 27);
	exit(EXIT_SUCCESS);
}

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

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message_to_send;
	int		i;

	if (!check_for_valid_argv(argc, argv))
	{
		ft_error_exit("Error: Wrong input given\n" RST
			"Expected: ./client <server_pid> \"message_to_send\"\n");
	}
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
