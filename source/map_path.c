/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:58:45 by aismaili          #+#    #+#             */
/*   Updated: 2023/11/26 14:53:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	dfs(t_game *game, int y, int x, int **visited)
{
	if (y < 0 || y >= game->rows || x < 0 || x >= game->cols
		|| game->map[y][x] == '1' || visited[y][x])
		return (0);
	if (game->map[y][x] == 'P')
		return (1);
	visited[y][x] = 1;
	if (dfs(game, y - 1, x, visited)
		|| dfs(game, y + 1, x, visited)
		|| dfs(game, y, x - 1, visited)
		|| dfs(game, y, x + 1, visited))
		return (1);
	return (0);
}

static int	is_reachable(t_game *game, int startY, int startX, int **visited)
{
	return (dfs(game, startY, startX, visited));
}

static void	ft_free(int **visited, int i)
{
	while (--i >= 0)
		free(visited[i]);
	free(visited);
}

static int	ft_eachc_e(t_game *game, int isolated, int **visited)
{
	int	y;
	int	x;
	int	j;

	y = 0;
	while (y < game->rows && isolated != 0)
	{
		x = -1;
		while (++x < game->cols)
		{
			if (game->map[y][x] == 'C' || game->map[y][x] == 'E')
			{
				j = 0;
				while (j < game->rows)
					ft_memset(visited[j++], 0, game->cols * sizeof(int));
				if (!is_reachable(game, y, x, visited))
				{
					isolated = 0;
					break ;
				}
			}
		}
		y++;
	}
	return (isolated);
}

int	isolated(t_game *game)
{
	int	**visited;
	int	i;
	int	isolated;

	visited = malloc(game->rows * sizeof(int *));
	if (!visited)
		return (0);
	i = 0;
	while (i < game->rows)
	{
		visited[i] = ft_calloc(game->cols, sizeof(int));
		if (!visited[i++])
			return (ft_free(visited, i), 0);
	}
	isolated = 1;
	isolated = ft_eachc_e(game, isolated, visited);
	return (ft_free(visited, i), isolated);
}
