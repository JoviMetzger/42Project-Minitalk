/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 14:52:26 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/18 09:56:27 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* handle_sig():
*	This function is the signal handler for SIGUSR1 and SIGUSR2
*	- If the received signal is SIGUSR1:
*		- It updates the variable (i) by setting the bit-th bit to 1 using 
*		  bitwise OR operation.
*		- If bit reaches 8 (it means that a full byte has been received):
*			- The function prints the character corresponding to the integer.
*			- Resets (bit) to 0 and (i) to 0.
*/
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

/* main():
*	This program sets up signal handlers for SIGUSR1 and SIGUSR2 and waits 
*	for these signals to be received. 
*	- It first checks if argc is equal to 1 (only program name itself).
*	- Retrieves the process ID (PID) of the current process using getpid().
*	- The program enters a loop that waits for signals by repeatedly 
*	  calling pause(), which suspends the process until a signal is received.
*	- When a signal is received, the corresponding signal handler (handle_sig()) 
*	  is invoked to process the signal.
*	- If the argc is not equal to 1, it means that the program was invoked 
*	  with incorrect command-line arguments.
*		- The program prints an error message indicating the wrong format 
*		  and suggests the correct format.
*/
int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf(BLUE BOLD "Server PID: %d\n" RESET, pid);
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
