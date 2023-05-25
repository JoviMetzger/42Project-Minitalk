# 🖥️ minitalk

Minitalk is a repository that contains a small data exchange program using UNIX signals. 

## Table of Contents

- [About](#About)
	- [ Server](#Server)
	- [ Client](#Client)
	- [ Bonus](#Bonus)
	- [ Functions Allowed](#Functions-Allowed)
- [Extra Knowlage](#Extra-Knowlage)
	- [ sa_flags](#sa_flags)
	- [ Bitwise Operations](#Bitwise-Operations)
- [Installation](#Installation)
- [Testing](#Testing)
- [Resources](#Resources)

## About 

### Server:
The server is responsible for quickly displaying received strings from multiple clients using only UNIX signals. It accepts the following signals:

- `SIGUSR1`: *Representing a binary 1*
- `SIGUSR2`: *Representing a binary 0*

### Client:
The client sends strings to the server using UNIX signals. It takes two parameters:

- `PID`: *The process ID of the server.*
- `String to send`: *The message that the client wants to send.*

The client can use the following signals:

- `SIGUSR1`: *Representing a binary 1*
- `SIGUSR2`: *Representing a binary 0*

### Bonus:
The bonus part of the program includes acknowledging every message received by sending back a signal to the client. It also supports Unicode characters, allowing the transmission of non-English characters, special characters, and emojis.

### Functions Allowed

- **`write`**: Attempt to write nbyte bytes from the buffer pointed to by 'buf' to the file associated with the open file descriptor. *(`ssize_t write(int fd, const void *buf, size_t count);`)*
- **`ft_printf`**: Your own ft_printf(), is a replicate of the original printf(). *(`int ft_printf(const char *format, ...);`)*
- **`signal`**: Specify the action to be taken when a specific signal is received by a process. *(`sighandler_t signal(int signum, sighandler_t handler);`)*
- **`sigemptyset`**: Initialize an empty signal set. *(`int sigemptyset(sigset_t *set);`)*
- **`sigaddset`**: Adds a specific signal to a signal set. *(`int sigaddset(sigset_t *set, int signum);`)*
- **`sigaction`**: Examine or modify the action associated with a specific signal. *(`int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`)*
- **`kill`**: Send a signal to a process or a group of processes. *(`int kill(pid_t pid, int sig);`)*
- **`getpid`**: Used to get the process ID of the process that is currently called. *(`pid_t getpid(void);`)*
- **`malloc`**: Used to dynamically allocate memory for data structures at runtime. *(`void *malloc(size_t size);`)*
- **`free`**:  Used to deallocate dynamically allocated memory after malloc(). *(`void free(void *ptr);`)*
- **`pause`**: Wait for signal, whose action is either to execute, or to terminate the process. (`int pause(void);`)*
- **`sleep`**: Program to pause its execution for a specified number of seconds. *(`unsigned int sleep(unsigned int seconds);`)*
- **`usleep`**: Delays the program for a microsecond. *(`int usleep(useconds_t usec);`)*
- **`exit`**: Terminates the calling process immediately. *(`void exit(int status);`)*

## Extra Knowlage

### sa_flags:
**`sa.sa_flags = SA_SIGINFO:`** When sa_flags is set to SA_SIGINFO, it indicates that the signal handler function (sa_sigaction) expects additional information about the signal in the form of siginfo_t and context parameters. This allows the handler to access more detailed information about the signal, such as the process ID that sent the signal or other relevant data. This additional information can be useful in scenarios where more context about the signal is required for appropriate handling.

**`sa.sa_flags = 0:`** On the other hand, setting sa_flags to 0 (or any other value without the SA_SIGINFO flag) indicates that the signal handler function (either sa_sigaction or sa_handler) does not expect or require any additional information beyond the signal number itself. In this case, the handler will receive only the signal number as a parameter. This simpler form of signal handling may be sufficient for scenarios where only the fact that a signal was received is relevant and no further information is needed for appropriate handling.

### Bitwise Operations:

Bitwise operations are used to manipulate individual bits of binary numbers. These operations treat numbers as sequences of binary digits (bits) and perform operations on corresponding bits. They are commonly employed in low-level operations such as hardware manipulation, data compression, encryption, and optimization algorithms.

- **Bitwise AND (&):** The AND operation compares two bits and returns 1 if both bits are 1; otherwise, it returns 0. **For example:**  *`5 (in binary: 0101) & 3 (in binary: 0011) = 1 (in binary: 0001)`*
- **Bitwise OR (|):** The OR operation compares two bits and returns 1 if at least one of the bits is 1; otherwise, it returns 0. **For example:** *`5 (0101) | 3 (0011) = 7 (0111)`*
- **Bitwise XOR (^):** The XOR operation compares two bits and returns 1 if the bits are different; otherwise, it returns 0. **For example:** *`5 (0101) ^ 3 (0011) = 6 (0110)`*
- **Bitwise NOT (~):** The NOT operation flips the bits, converting 0 to 1 and 1 to 0. It is a unary operation that operates on a single operand. 
- **Left shift (<<):** The left shift operation shifts the bits of a number to the left by a specified number of positions. **For example:** *`5 (0101) << 2 = 20 (in binary: 10100)`*
- **Right shift (>>):** The right shift operation shifts the bits of a number to the right by a specified number of positions. **For example:** *`10 (in binary: 1010) >> 2 = 2 (in binary: 0010)`*
	

## Installation

### To execute the *Mandatory Part*, follow the steps below:

1. Compile the program by running the following command:
```bash
$ make
```
2. To get yoy PID execute the program using the following command: 
```bash
$ ./server
```
#### ***Open a second terminal in the same minitalk folder.***
3. To send signal execute the program using the following command:
```bash
$ ./client <PID> "Hello World"
```


### To execute the *Bonus Part*, follow the steps below:

1. Compile the bonus by running the following command:
```bash
$ make bonus
```
2. To get yoy PID execute the program using the following command: 
```bash
$ ./server_bonus
```
#### ***Open a second terminal in the same minitalk folder.***
3. To send signal execute the program using the following command:
```bash
$ ./client_bonus <PID> "Hello World"
```

## Testing

### Spesific hedge-cases 
Different PID *(Positive and negative numbers)*:
```bash
$ ./client -1 "Hello World"
```
If the message is empty:
```bash
$ ./client <PID> ""
```

### Stresstester:
[stresstest20k:](https://github.com/XEDGit/minitalk/blob/master/stresstest20k)
```bash
$ ./client <PID> "stresstest20k"
```
[stresstest50k:](https://github.com/XEDGit/minitalk/blob/master/stresstest50k)
```bash
$ ./client <PID> "stresstest50k"
```
[stresstest100k:](https://github.com/XEDGit/minitalk/blob/master/stresstest100k)
```bash
$ ./client <PID> "stresstest100k"
```
[stresstest250k:](https://github.com/XEDGit/minitalk/blob/master/stresstest250k)
```bash
$ ./client <PID> "stresstest250k"
```

## Resources

- [StressTest](https://github.com/XEDGit/minitalk/tree/master)
- [Project subject](https://cdn.intra.42.fr/pdf/pdf/68781/en.subject.pdf)
