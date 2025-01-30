/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:10:47 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/30 14:46:33 by jaferna2         ###   ########.fr       */
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
