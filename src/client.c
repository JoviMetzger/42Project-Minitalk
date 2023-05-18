/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/15 14:52:08 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/05/18 09:52:22 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* send_bits():
*	This function is responsible for sending individual bits of a character (i) 
*	to a specified PID using signals.
*	- It enters a loop that iterates 8 times, representing each bit 
*	  of the character.
*	- Inside the loop, it checks if the bit-th bit of (i) is set to 1 using 
*	  bitwise AND operation (i & (1 << bit)).
*		- If the (bit) is 1, it sends SIGUSR1 signal to the PID 
*		  using the kill function.
*		- If the (bit) is 0, it sends SIGUSR2 signal to the PID 
*		  using the kill function.
*	- After sending the signal, it pauses execution for a short time 
*	  using usleep() to allow the signal to be processed.
*	- It increments the (bit) variable by 1.
*/
static void	send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (i & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

/* main():
*	This function sends individual bits of characters in the provided message 
*	to the specified process ID (PID) using signals (SIGUSR1 and SIGUSR2). 
*	- It first checks if the argc is equal to 3 (PID and message).
*		- It converts the string representation of the PID (argv[1]) 
*		  to an integer using ft_atoi() function.
*		- It enters a loop that iterates over each character of 
*		  the message (argv[2]) using the (i) variable as the index.
*		- Inside the loop, it calls the send_bits() function to send each 
*		  character to the specified PID.
*		- After sending all characters, it calls send_bits() again to send 
*		  a newline character ('\n') as the end marker.
*	- If the argc is not equal to 3:
*		- It prints an error message indicating the wrong format 
*		  and suggests the correct format.
*/
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send_bits(pid, argv[2][i]);
			i++;
		}
		send_bits(pid, '\n');
	}
	else
	{
		ft_printf(RED "Error: Wrong format\n" RESET);
		ft_printf(RED "Try: ./client <PID> <MESSAGE>\n" RESET);
		return (1);
	}
	return (0);
}
