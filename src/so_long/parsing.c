/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:35:37 by scely             #+#    #+#             */
/*   Updated: 2023/12/29 17:03:36 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	nb_line(char **av)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '1' && line[0] != '\0')
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	i++;
	}
	free(line);
	close(fd);
	return (i);
}

int	good_carac(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '\n'
			&& line[i] != 'C' && line[i] != 'E' && line[i] != 'P')
			return (0);
		i++;
	}
	return (i);
}

int	check_error(char **str)
{
	int		i;
	int		k;
	int		e_xite;
	int		p_erso;
	int		j;

	i = 0;
	k = ft_strlen(str[0]);
	e_xite = 0;
	p_erso = 0;
	while (str[i])
	{
		if (k != ft_strlen(str[i]))
			return (ft_putstr_fd("Wrong size of maps", 1), -1);
		if (good_carac(str[i]) == 0)
			return (ft_putstr_fd("Wrong objects", 1), -1);
		if (str[i][0] != '1' || str[i][k - 2] != '1')
			return (ft_putstr_fd("Wrong wall", 1), -1);
		if (ft_strchr(str[i], 'E') != 0)
			e_xite += 1;
		if (ft_strchr(str[i], 'P') != 0)
			p_erso += 1;
		i++;
	}
	j = 0;
	while (j <= k - 2)
	{
		if (str[0][j] != str[i -1][j] && str[i -1][j] != '1'
			&& str[i -1][j] != '1')
			return (ft_putstr_fd("Wrong size of maps", 1), -1);
		j++;
	}
	if (k == i - 1)
		return (ft_putstr_fd("Square map", 1), -1);
	if (e_xite != 1 || p_erso != 1)
		return (ft_putstr_fd("Wrong number of Exit or Personage", 1), -1);
	return (0);
}

int	main(int ac, char **av)
{
	char	**doublon;
	int		fd;
	int		i;
	int		j;

	i = 0;
	j = nb_line(void);
	doublon = malloc(sizeof(char *) * (j + 1));
	if (!doublon)
		return (free(doublon), -1);
	doublon[j] = NULL;
	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Invalid fd"), -1);
	while (i <= j)
		doublon[i++] = get_next_line(fd);
	if (check_error(doublon) != 0 || ways(doublon) == -1 )
	{
		free(doublon);
		close(fd);
		return (0);
	}
	close(fd);
	// for (i = 0; doublon[i] != NULL; i++)
	// 	printf("%s", doublon[i]);
	i = 0;
	while (doublon[i])
		free(doublon[i++]);
	free(doublon);
	close(fd);
}
