/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:49 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/18 11:15:56 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_fork(t_execute *exec, int i)
{
	if (i == exec->count_children)
		i--;
	if ((exec->id[i] < 0) && (i < exec->count_children))
	{
		dprintf(2, "fork error at id[%i]: %i\n", i, exec->id[i]);
		perror("fork error");
		return (-1);
	}
	return (i);
}

int	ft_forking(t_execute *exec)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	exec->id[0] = 1;
	while (++i < exec->count_children && !(exec->count_builtins == 1 && exec->count_children == 1))
	{
		// dprintf(2, "hi, ich forke\n");
		exec->id[i] = fork();
		if (exec->id[i] == 0)
			break ;
	}
	i = ft_check_fork(exec, i);
	dprintf(2, "i: %i exec->id[%i]: %i\n", i, i, exec->id[i]);
	if (i < 0)
		return (1);
	// if (exec->id[i] == 0 && i == 0 && exec->limiter && !(exec->count_builtins == 1 && exec->count_children == 1))
	// 	exec->error += ft_child(i, exec);
	// else if (exec->id[i] == 0 && i == 0 && exec->count_children == 1 && !(exec->count_builtins == 1 && exec->count_children == 1))
		// exec->error += ft_child_first_last(exec, i);
	// else if (exec->id[i] == 0 && i == 0 && !(exec->count_builtins == 1 && exec->count_children == 1))
	// 	error = ft_first_child(exec, i);
	// else if (exec->id[i] == 0 && i == exec->count_children - 1 && !(exec->count_builtins == 1 && exec->count_children == 1))
	// 	error = ft_last_child(exec, i);
	// else if (exec->id[i] == 0 && !(exec->count_builtins == 1 && exec->count_children == 1))
	// 	exec->error += ft_child(i, exec);
	if (exec->id[i] == 0)
		exec->error += ft_child(i, exec);
	else if (exec->id[i] > 0)
		exec->error += ft_parent(exec);
	return (error);
}
