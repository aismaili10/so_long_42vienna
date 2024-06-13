/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:53:29 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/16 18:15:54 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->line_flag == 1)
	{
		free(game->line);
		game->line_flag = 0;
	}
	while (i < game->rows)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_game(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.wall);
	mlx_destroy_image(game->mlx_ptr, game->img.floor);
	mlx_destroy_image(game->mlx_ptr, game->img.player);
	mlx_destroy_image(game->mlx_ptr, game->img.exit);
	mlx_destroy_image(game->mlx_ptr, game->img.collectible);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	close(game->fd);
	exit (0);
}

void	fail_message_map(char *str, t_game *game)
{
	ft_putendl_fd(str, 2);
	if (game->mal_flag == 1)
	{
		free_map(game);
		game->line_flag = 0;
	}
	if (game->line_flag == 1)
	{
		free(game->line);
		game->line_flag = 0;
	}
	close(game->fd);
	exit (1);
}

static void	xpm_to_img_fail(t_game *game)
{
	if (game->img.wall)
		mlx_destroy_image(game->mlx_ptr, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx_ptr, game->img.floor);
	if (game->img.collectible)
		mlx_destroy_image(game->mlx_ptr, game->img.collectible);
	if (game->img.player)
		mlx_destroy_image(game->mlx_ptr, game->img.player);
	if (game->img.exit)
		mlx_destroy_image(game->mlx_ptr, game->img.exit);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	close(game->fd);
	exit (3);
}

void	endgame(t_game *game, char *str, char *color, int exit_code)
{
	ft_printf("%s%s\n"RESETC, color, str);
	if (game->line_flag == 1)
	{
		free(game->line);
		game->line_flag = 0;
	}
	if (game->mal_flag == 1)
	{
		free_map(game);
		game->mal_flag = 0;
	}
	if (exit_code == 0 || exit_code == 4)
		free_game(game);
	if (exit_code == 2)
		free(game->mlx_ptr);
	if (exit_code == 3)
		xpm_to_img_fail(game);
	close(game->fd);
	exit (exit_code);
}
