/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:24:24 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/27 20:10:57 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	allowed_elements(char **lines)
{
	int	y;
	int	x;

	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			if (!ft_strchr("10PCE", lines[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	nline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '\n' && line[i + 1] == '\n'))
			return (0);
		if ((line[i] == '\n' && line[i + 1] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_read(t_game *game, int i)
{
	char	*tmp;
	int		gnl_errno;

	i = 0;
	while (game->fd)
	{
		tmp = get_next_line(game->fd, 0);
		if (!tmp)
		{
			gnl_errno = errno;
			if (gnl_errno != 0)
				fail_message_map(RED"Error\nMalloc fail in gnl"RESETC, game);
			break ;
		}
		game->line = ft_strjoingnl(game->line, tmp);
		if (!game->line)
		{
			get_next_line(game->fd, 1);
			return (free(tmp), 2);
		}
		game->line_flag = 1;
		free(tmp);
		i++;
	}
	return (i);
}

static void	check_map(t_game *game)
{
	if (!allowed_elements(game->map))
		fail_message_map(RED"Error\nInvalid map elements"RESETC, game);
	if (!closed_walls(game->map, game->rows))
		fail_message_map(RED"Error\nInvalid map walls"RESETC, game);
	if (!no_dup(game))
		fail_message_map(RED"Error\nInvalid map elements (dups)"RESETC, game);
	if (!isolated(game))
		fail_message_map(RED"Error\nInvalid map path"RESETC, game);
}

void	map_validity(t_game *game)
{
	game->line = NULL;
	game->mal_flag = 0;
	game->line_flag = 0;
	game->i = ft_read(game, game->i);
	if (game->i <= 2)
		fail_message_map(RED"Error\nEmpty/Invalid map"RESETC, game);
	if (!nline(game->line))
		fail_message_map(RED"Error\ninvalid nl in map"RESETC, game);
	game->map = ft_split(game->line, '\n');
	if (!game->map)
		fail_message_map(RED"Error\n"RESETC, game);
	game->mal_flag = 1;
	game->rows = game->i;
	game->cols = 0;
	while (game->map[0][game->cols] != '\0')
		game->cols++;
	check_map(game);
}
