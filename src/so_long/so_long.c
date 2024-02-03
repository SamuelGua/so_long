/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/03 22:56:10 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int ac, char **av, char **envp)
{
    t_maps *maps;
    
    if (envp[0] == NULL || ac != 2)
        return (1);
    maps = ft_calloc(sizeof(t_maps), 1);
    if  (maps == NULL)
        return (ft_putstr_fd("Error : Malloc\n", 1), 1);
    if (parsing(maps, av) != 1)
        return (free(maps), 1);
}
