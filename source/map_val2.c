/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_val2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:49:37 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/15 21:59:12 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	sub_no_dup(t_count *count, char e)
{
	if (e == 'E')
		count->e++;
	else if (e == 'P')
		count->p++;
	else if (e == 'C')
		count->c++;
}

int	no_dup(t_game *game)
{
	int	y;
	int	x;

	game->count.e = 0;
	game->count.p = 0;
	game->count.c = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			sub_no_dup(&game->count, game->map[y][x]);
			x++;
		}
		y++;
	}
	if (game->count.e != 1 || game->count.p != 1 || game->count.c < 1)
		return (0);
	return (1);
}

static int	right_length_line(char *lines, int end)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	if (i != end)
		return (0);
	return (1);
}

static int	check_middle_line(char **lines, int x, int y, int end)
{
	while (lines[y])
	{
		if (!right_length_line(lines[y], end + 1))
			return (0);
		if (lines[y][x] != '1' || lines[y][end] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	closed_walls(char **lines, int rows)
{
	int	y;
	int	x;
	int	end;

	y = 0;
	x = 0;
	while (lines[y][x])
	{
		if (lines[y][x] != '1')
			return (0);
		x++;
	}
	end = x - 1;
	x = 0;
	if (!check_middle_line(lines, x, y, end))
		return (0);
	while (lines[rows - 1][x])
	{
		if (!right_length_line(lines[rows - 1], end + 1))
			return (0);
		if (lines[rows - 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}
