/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgnanaso <rgnanaso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:31:57 by rgnanaso          #+#    #+#             */
/*   Updated: 2024/03/20 15:58:13 by rgnanaso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

	pipex = init_pipex(argc, argv);
	parsing(pipex, argc, argv, envp);
	//pipe(pipex->pip);
	execute(pipex, argv, argc);

}
