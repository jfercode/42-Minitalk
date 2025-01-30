/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:21 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/30 14:52:24 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * TO DO: 
 * 1- Write a main in which the client takes two parameters
 * 		- The PID of the server
 * 		- The message to send
 * 2- Encrypt the message (encryption via bits)
 * 3- Send the message to the server (PID)
 * 4- Create a stop condition 
 */

static	int check_for_valid_argv(int argc, char **argv)
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

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message_to_send;

	if (!check_for_valid_argv(argc, argv))
	{
		ft_error_exit("Error: Wrong input given\n" RST
			"Expected: ./client <server_pid> <message_to_send>\n");
	}
	else
	{
		pid = ft_atoi(argv[1]);
		message_to_send = ft_strdup(argv[2]);
	}
	return (0);
}
