/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:18 by jaferna2          #+#    #+#             */
/*   Updated: 2025/01/31 12:53:00 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../source/libft/include/libft.h"

# include <signal.h>

# define BUSY	0
# define READY	1

void	ft_kill(pid_t pid, int signo);
void	ft_send_char(char c, pid_t pid);
void	ft_error_exit(const char *error_msg);
void	ft_signal(int signo, void *handler, bool use_siginfo);

#endif /*MINITALK_H*/