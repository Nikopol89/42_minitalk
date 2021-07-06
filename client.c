/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:09:01 by jmartini          #+#    #+#             */
/*   Updated: 2021/07/01 15:09:04 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_encode(const char c, int pid)
{
	t_byte	op;
	int		sig;

	op = BYTE_OPS;
	while (op)
	{
		usleep(SHORT);
		if (c & op)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		op >>= 1;
		kill(pid, sig);
	}
}

static void	ft_engine(const char *str, int pid)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_encode(str[i], pid);
		usleep(LONG);
	}
	ft_encode(ACK, pid);
}

static void	ft_ack(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;
	ft_printf("ACK signal from %d received. Bye!\n", info->si_pid);
	exit (0);
}

static int	ft_err_check(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 3)
	{
		ft_printf("ERROR: wrong amount of arguments\n");
		ft_printf("Usage: ./client \"PID\" \"STRING\"\n");
		return (0);
	}
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			ft_printf("ERROR: PID is not a number\n");
			ft_printf("Usage: ./client \"PID\" \"STRING\"\n");
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct sigaction	act_usr;
	int					pid;

	if (!ft_err_check(argc, argv))
		return (0);
	pid = ft_atoi(argv[1]);
	act_usr.sa_sigaction = &ft_ack;
	act_usr.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act_usr, NULL);
	ft_printf("%d sending to %d\nStandby for ACK\n", getpid(), pid);
	ft_engine(argv[2], pid);
	while (1)
	{
	}
	return (0);
}
