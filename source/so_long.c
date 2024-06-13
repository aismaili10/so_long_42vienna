/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:26:11 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/03 18:37:04 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->p_y = y;
				game->p_x = x;
				break ;
			}
			x++;
		}
		y++;
	}
}

static int	close_window(t_game *game)
{
	endgame(game, "Game closed", RED, 4);
	exit (4);
}

void	so_long(char *map, t_game *game)
{
	game->fd = open(map, O_RDONLY);
	if (game->fd == -1)
	{
		ft_putendl_fd(RED"Error opening the file"RESETC, 2);
		exit(1);
	}
	map_validity(game);
	rendering(game);
	position(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, 17, 0, close_window, game);
	game->movements = 0;
	ft_printf("Movements: %d\n", 0);
	mlx_loop(game->mlx_ptr);
}

static int	valid_map_file(char *map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	if (map[i] == 'r' && map[i - 1] == 'e'
		&& map[i - 2] == 'b' && map[i - 3] == '.')
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("wrong input"), 0);
	if (!valid_map_file(argv[1]))
		return (ft_printf("wrong input"), 0);
	else
		so_long(argv[1], &game);
	return (0);
}
