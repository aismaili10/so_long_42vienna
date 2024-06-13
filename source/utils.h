/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:58:57 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/16 18:24:09 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "../libft/printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"

# define UP			119
# define DOWN		115
# define LEFT		97
# define RIGHT		100
# define TILE_SIZE 	32
# define RED		"\033[1m\033[31m"
# define GREEN		"\033[1m\033[32m"
# define RESETC		"\033[0m"

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*player;
	void	*exit;
}	t_img;

typedef struct s_count
{
	int	e;
	int	p;
	int	c;
}	t_count;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*line;
	char	**map;
	int		rows;
	int		cols;
	int		p_x;
	int		p_y;
	t_coord	coord;
	int		movements;
	int		wmap_width;
	int		wmap_height;
	int		mal_flag;
	int		line_flag;
	int		i;
	int		fd;
	t_img	img;
	t_count	count;
}	t_game;

void	so_long(char *map, t_game *game);
void	*rendering(t_game *game);
void	map_validity(t_game *game);
int		no_dup(t_game *game);
int		closed_walls(char **lines, int rows);
int		isolated(t_game *game);
void	fail_message_map(char *str, t_game *game);
int		key_press(int keycode, t_game *game);
void	free_game(t_game *game);
void	endgame(t_game *game, char *str, char *color, int exit_code);

#endif
