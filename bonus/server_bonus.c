/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:12:49 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/19 09:12:07 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/* action();
*	This function performs an action based on the received character (c). 
*	- Prints the character using ft_printf().
*	- If the character is null '\0'.
*		- If it is null, it indicates that the transmission of a message from 
*		  the client is complete.
*		- The server needs to notify the client by sending a signal (SIGUSR1).
*		- The function updates the received count, clears the character, 
*		  and sends the signal using kill().
*	- If the character is not null
*		- It increments the bit count and resets it if it reaches 8.
*/
static void	action(char *c, int *received, int *given_pid, int *bit)
{
	ft_printf("%c", *c);
	if (*c == '\0')
	{
		*received = 0;
		*c = 0;
		if (kill(*given_pid, SIGUSR1) == -1)
		{
			ft_printf(RED "Error\n" RESET);
			exit(EXIT_FAILURE);
		}
		return ;
	}
	*bit = 0;
}

/* handle_sig();
*	This signal handler function is responsible for interpreting 
*	the signals received from the client. 
*	- Uses static variables to track the current communication state.
*	- Checks if the given PID is empty (indicating a new client connection) 
*	  and updates it with the client's PID from the signal information.
*	- Updates the current PID. 
*	- Interprets the received signal (SIGUSR1 or SIGUSR2) as 
*	  a binary digit (0 or 1) and appends it to the received character (c).
*	- Increments the received count and the bit count. 
*	- When the bit count reaches 8, calls the action() function to process 
*	  the received character.
*	- Left-shifts the character (c) by 1 and sends a signal (SIGUSR2) to 
*	  the client using kill().
*	- Includes a usleep() call to introduce a small delay between signals.
*/
static void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static int	given_pid;
	static int	bit;
	static char	c;
	static int	received;
	static int	current_pid;

	(void)context;
	if (!given_pid)
		given_pid = info->si_pid;
	current_pid = info->si_pid;
	if (given_pid != current_pid)
	{
		given_pid = current_pid;
		bit = 0;
		c = 0;
		received = 0;
	}
	c |= (sig == SIGUSR2);
	received++;
	bit++;
	if (bit == 8)
		action(&c, &received, &given_pid, &bit);
	c <<= 1;
	usleep(100);
	kill(given_pid, SIGUSR2);
}

/* main();
*	The main() function sets up the server and handles incoming signals 
*	from the client.
*		- Retrieves the server's PID using getpid().
*		- Sets up the signal handler by assigning the handle_sig() function 
*		  to the sa_sigaction field of the sigaction structure. 
*		- Registers the signal handlers for SIGUSR1 and SIGUSR2 using sigaction.
*		- Enters a loop where it waits for signals using pause().
*		- When a signal is received, the handle_sig() function is invoked 
*		  to process the signal.
*		- If the program is called incorrectly, it displays an error message.
*/
int	main(int argc, char **argv)
{
	int			pid;
	struct sigaction	sig;

	(void)argv;
	if (argc == 1)
	{
		pid = getpid();
		ft_printf(BLUE BOLD "Server PID: %d\n" RESET, pid);
		ft_printf(BLUE "Waiting for message...\n" RESET);
		sig.sa_sigaction = handle_sig;
		sigemptyset(&sig.sa_mask);
		sig.sa_flags = SA_SIGINFO;
		while (1)
		{
			sigaction(SIGUSR1, &sig, 0);
			sigaction(SIGUSR2, &sig, 0);
			pause();
		}
	}
	else
	{
		ft_printf(RED "Error: Wrong format\n" RESET);
		ft_printf(RED "Try: ./server_bonus\n" RESET);
	}
	return (0);
}
