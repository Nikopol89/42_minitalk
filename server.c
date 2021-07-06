/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:09:11 by jmartini          #+#    #+#             */
/*   Updated: 2021/07/01 15:09:13 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_savemsg(t_byte *sigbits, t_byte *byte, siginfo_t *info)
{
	static t_byte	*str;
	t_byte			*tmp;
	static int		i;

	if (*sigbits == ACK)
	{
		ft_printf("%s\n", str);
		free(str);
		i = 0;
		*sigbits = 0;
		*byte = BYTE_OPS;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	tmp = str;
	str = ft_calloc(i + 2, sizeof(*str));
	if (!ft_memcpy(str, tmp, i))
		exit (0);
	str[i] = *sigbits;
	if (i)
		free(tmp);
	*sigbits = 0;
	*byte = BYTE_OPS;
	i++;
}

static void	ft_decode(int sig, siginfo_t *info, void *ucontext)
{
	static t_byte	sigbits;
	static t_byte	byte;

	(void)ucontext;
	if (!byte)
		byte = BYTE_OPS;
	if (sig == SIGUSR1)
		sigbits |= 1;
	byte >>= 1;
	if (byte)
		sigbits <<= 1;
	else
		ft_savemsg(&sigbits, &byte, info);
}

int	main(void)
{
	struct sigaction	act_usr1;
	struct sigaction	act_usr2;

	act_usr1.sa_sigaction = &ft_decode;
	act_usr2.sa_sigaction = &ft_decode;
	act_usr1.sa_flags = SA_SIGINFO;
	act_usr2.sa_flags = SA_SIGINFO;
	sigemptyset(&act_usr1.sa_mask);
	sigemptyset(&act_usr2.sa_mask);
	sigaddset(&act_usr1.sa_mask, SIGUSR2);
	sigaddset(&act_usr2.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &act_usr1, NULL);
	sigaction(SIGUSR2, &act_usr2, NULL);
	ft_printf("PID: %d\n", getpid());
	while (1)
	{
	}
	return (0);
}
