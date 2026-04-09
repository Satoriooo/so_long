/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:08:35 by shirose           #+#    #+#             */
/*   Updated: 2026/04/09 17:32:52 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', fd);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar((nb % 10) + '0', fd);
}

void	clean_map(t_game *game)
{
	int	n;

	n = game->map_h;
	if (game->error_i > -1)
		n = game->error_i;
	while (n >= 0)
		free(game->map[n--]);
	free(game->map);
	game->map = NULL;
}

int	terminate_all(t_game *game, int n)
{
	if (game->fd > 0)
		close(game->fd);
	if (game->map)
		clean_map(game);
	if (game->floor_img)
		mlx_destroy_image(game->mlx_ptr, game->floor_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx_ptr, game->exit_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx_ptr, game->player_img);
	if (game->item_img)
		mlx_destroy_image(game->mlx_ptr, game->item_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx_ptr, game->wall_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	exit(n);
}
