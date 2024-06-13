/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:39:53 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/16 18:16:40 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

static void	put_to_window(t_game *game, void *image_ptr)
{
	game->coord.y = 0;
	while (game->map[game->coord.y] != 0)
	{
		game->coord.x = 0;
		while (game->map[game->coord.y][game->coord.x] != 0)
		{
			image_ptr = NULL;
			if (game->map[game->coord.y][game->coord.x] == '1')
				image_ptr = game->img.wall;
			else if (game->map[game->coord.y][game->coord.x] == '0')
				image_ptr = game->img.floor;
			else if (game->map[game->coord.y][game->coord.x] == 'C')
				image_ptr = game->img.collectible;
			else if (game->map[game->coord.y][game->coord.x] == 'P')
				image_ptr = game->img.player;
			else if (game->map[game->coord.y][game->coord.x] == 'E')
				image_ptr = game->img.exit;
			if (image_ptr != NULL)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, image_ptr,
					game->coord.x * TILE_SIZE, game->coord.y * TILE_SIZE);
			game->coord.x++;
		}
		game->coord.y++;
	}
}

static void	con_xpm_to_img(t_game *game)
{
	int	img_width;
	int	img_height;

	img_width = TILE_SIZE;
	img_height = TILE_SIZE;
	game->img.wall = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/wall.xpm", &img_width, &img_height);
	if (!game->img.wall)
		endgame(game, "mlx_xpm_file_to_image failed", RED, 3);
	game->img.floor = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/floor.xpm", &img_width, &img_height);
	if (!game->img.wall)
		endgame(game, "mlx_xpm_file_to_image failed", RED, 3);
	game->img.collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/star.xpm", &img_width, &img_height);
	if (!game->img.wall)
		endgame(game, "mlx_xpm_file_to_image failed", RED, 3);
	game->img.player = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/ball.xpm", &img_width, &img_height);
	if (!game->img.wall)
		endgame(game, "mlx_xpm_file_to_image failed", RED, 3);
	game->img.exit = mlx_xpm_file_to_image(game->mlx_ptr,
			"img/exit.xpm", &img_width, &img_height);
	if (!game->img.wall)
		endgame(game, "mlx_xpm_file_to_image failed", RED, 3);
}

static void	reset_img(t_game *game)
{
	game->img.collectible = NULL;
	game->img.wall = NULL;
	game->img.player = NULL;
	game->img.exit = NULL;
	game->img.floor = NULL;
}

void	*rendering(t_game *game)
{
	void	*image_ptr;

	game->wmap_width = game->cols * TILE_SIZE;
	game->wmap_height = game->rows * TILE_SIZE;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		endgame(game, "mlx_init failed", RED, 1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->wmap_width,
			game->wmap_height, "so_long");
	if (!game->win_ptr)
		endgame(game, "mlx_new_window failed", RED, 2);
	reset_img(game);
	con_xpm_to_img(game);
	image_ptr = NULL;
	put_to_window(game, image_ptr);
	return (NULL);
}
