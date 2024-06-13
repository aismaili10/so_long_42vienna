/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:17:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/03 18:42:24 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_walkable(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->cols
		|| y >= game->rows || game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'C')
	{
		game->count.c--;
		game->map[y][x] = '0';
	}
	if (game->map[y][x] == 'C' || game->map[y][x] == '0'
		|| game->map[y][x] == 'P')
		return (1);
	else if (game->map[y][x] == 'E')
		return (2);
	return (0);
}

static void	walk_on_exit(t_game *game, int walkable, int tmp_y, int tmp_x)
{
	if (walkable == 2)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.floor,
			game->p_x * TILE_SIZE, game->p_y * TILE_SIZE);
		game->p_x = tmp_x;
		game->p_y = tmp_y;
		game->movements += 1;
		write(1, "\033[A\033[K", 6);
		ft_printf("Movements: %d\n", game->movements);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.player,
			game->p_x * TILE_SIZE, game->p_y * TILE_SIZE);
		if (game->count.c == 0)
			endgame(game, "You won! Nice Job", GREEN, 0);
	}
}

static void	movement(t_game *game, int walkable, int tmp_y, int tmp_x)
{
	if (walkable == 1)
	{
		if (is_walkable(game, game->p_x, game->p_y) == 2)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.exit, game->p_x * TILE_SIZE, game->p_y * TILE_SIZE);
		else
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.floor, game->p_x * TILE_SIZE, game->p_y * TILE_SIZE);
		game->p_x = tmp_x;
		game->p_y = tmp_y;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.player,
			game->p_x * TILE_SIZE, game->p_y * TILE_SIZE);
		game->movements += 1;
		write(1, "\033[A\033[K", 6);
		ft_printf("Movements: %d\n", game->movements);
	}
	walk_on_exit(game, walkable, tmp_y, tmp_x);
}

int	key_press(int keycode, t_game *game)
{
	int	tmp_x;
	int	tmp_y;
	int	walkable;

	tmp_x = game->p_x;
	tmp_y = game->p_y;
	if (keycode == UP)
		tmp_y--;
	else if (keycode == LEFT)
		tmp_x--;
	else if (keycode == DOWN)
		tmp_y++;
	else if (keycode == RIGHT)
		tmp_x++;
	else if (keycode == 65307)
		endgame(game, "Left Game!", RED, 0);
	walkable = is_walkable(game, tmp_x, tmp_y);
	if (walkable && (keycode == UP || keycode == LEFT
			|| keycode == DOWN || keycode == RIGHT))
		movement(game, walkable, tmp_y, tmp_x);
	return (0);
}
