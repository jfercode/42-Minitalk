/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:55:18 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/03 10:18:46 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../source/libft/include/libft.h"

# include <signal.h>

# ifndef BUSY
#  define BUSY	0
# endif

# ifndef READY
#  define READY	1
# endif

void	ft_kill(pid_t pid, int signo);
void	ft_send_char(char c, pid_t pid);
void	ft_error_exit(const char *error_msg);
void	ft_signal(int signo, void *handler, bool use_siginfo);

#endif /*MINITALK_H*/