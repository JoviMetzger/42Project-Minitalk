/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 14:52:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/17 13:10:04 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_sig(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
	    ft_printf(BLUE BOLD "Client PID: %d\n" RESET, pid);
	    ft_printf(BLUE "Waiting for a message..\n" RESET);
	    while (argc == 1)
	    {
	    	signal(SIGUSR1, handle_sig);
	    	signal(SIGUSR2, handle_sig);
	    	pause();
	    }
	}
    else
    {
        ft_printf(RED "Error: Wrong format\n" RESET);
		ft_printf(RED "Try: ./client <PID> <MESSAGE>\n" RESET);
		return (1);
    }
	return (0);
}
