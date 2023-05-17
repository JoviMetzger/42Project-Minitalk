/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 12:12:28 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/17 15:07:47 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/* ft_send();
*   This function is responsible for sending a single bit of data to 
*   the specified process ID.
*   - It takes two parameters: 
*       - bit -> the bit value to be sent, either 0 or 1.
*       - pid -> the process ID of the recipient process.
*   - If the bit value is non-zero (1):
*       - Send a SIGUSR2 signal to the process with the given pid using 
*         the kill function.
*       - If the kill function returns -1 (indicating an error), 
*         call the ft_error_msg.
*   - If the bit value is zero:
*       - Send a SIGUSR1 signal to the process with the given pid 
*         using the kill function.
*       - If the kill function returns -1 (indicating an error), 
*         call the ft_error_msg.
*   - Pause the execution of the current process until a signal 
*     is received using the pause function.
*   - Add a small delay of 100 microseconds using the usleep function.
*/
static void	ft_send(int bit, int pid)
{
	if (bit)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf(RED "Error\n" RESET);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf(RED "Error\n" RESET);
			exit(EXIT_FAILURE);
		}
	}
	pause();
	usleep(100);
}

/* send_bits();
*   This function sends a character (c) byte by byte to 
*   the specified process ID. 
*   - It uses the ft_send() function to send each bit of the character.
*   - The c value is bitwise shifted left (c <<= 1) after each bit 
*     is sent to process the next bit.
*/
static void	send_bits(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		ft_send(c & 128, pid);
		c <<= 1;
		bit++;
	}
}

/* sender();
*   This function sends a null-terminated string (str) to 
*   the specified process ID. 
*   - It iterates over each character in the string and calls 
*     the send_bits() function to send each character.
*/
static void	sender(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bits(str[i++], pid);
	}
	send_bits(0, pid);
}

/* confirmed();
*   This function acts as a signal handler that handles 
*   SIGUSR1 and SIGUSR2 signals. 
*   - It checks the received signal and performs different 
*     actions accordingly;
*       - If the signal is SIGUSR1:
*           - it prints a success message and exits 
*             the program with EXIT_SUCCESS. 
*       - If the signal is SIGUSR2:
*           - it increments a static variable sent 
*             to keep track of the number of signals received.
*/
static void	confirmed(int signal)
{
	static int	sent;

	if (signal == SIGUSR1)
	{
		ft_printf(GREEN "Signal sent successfully!\n" RESET);
		exit(EXIT_SUCCESS);
	}
	if (signal == SIGUSR2)
		++sent;
}

/* main();
*   This function sets up signal handlers, converts the process ID, 
*   and calls the sender function to send the message.
*   - First it checks the message is not empty. 
*   - If the arguments are valid (argc == 3);
*       - It sets up signal handlers for SIGUSR1 and SIGUSR2.
*       - It converts the PID to an integer using ft_atoi()
*       - It calls the sender() function to send the message (argv[2]) 
*         to the specified PID.
*   - If the arguments are not valid, it displays an error message.
*/
int	main(int argc, char **argv)
{
	int	pid;

	if (*argv[2] == 0)
	{
		ft_printf(RED "Please, insert a non-empty message.\n" RESET);
		return (EXIT_FAILURE);
	}
	if (argc == 3)
	{
		signal(SIGUSR1, confirmed);
		signal(SIGUSR2, confirmed);
		pid = ft_atoi(argv[1]);
		sender(argv[2], pid);
	}
	else
	{
		ft_printf(RED "Error: Wrong format\n" RESET);
		ft_printf(RED "Try: ./client_bonus <PID> <MESSAGE>\n" RESET);
	}
	return (EXIT_FAILURE);
}
