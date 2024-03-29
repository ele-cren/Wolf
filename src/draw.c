/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-cren <ele-cren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:33:20 by ele-cren          #+#    #+#             */
/*   Updated: 2017/05/18 15:29:47 by ele-cren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_draw(int x, t_calc calc, t_sdl *sdl, t_def def)
{
	t_draw	draw;

	ft_init_draw(calc, sdl, &draw, def);
	if (def.tab[calc.map_y][calc.map_x] == 2 && x == WIDTH / 2 && \
			sdl->dst[DSHOTGUN].y + 145 >= draw.draw_s && \
			sdl->dst[DSHOTGUN].y + 145 <= draw.draw_e && calc.wall_dist <= 3.5)
	{
		sdl->wallbreak.breakable = 1;
		sdl->wallbreak.pos_x = calc.map_x;
		sdl->wallbreak.pos_y = calc.map_y;
	}
	sdl->dst[DWALL].x = x;
	sdl->dst[DWALL].h = draw.draw_e - draw.draw_s;
	sdl->dst[DWALL].y = draw.draw_s;
	sdl->dst[DWALL].w = 1;
	if (def.tab[calc.map_y][calc.map_x] == 1)
		SDL_RenderCopy(sdl->render, sdl->game[TWALL], &sdl->src[SWALL], \
												&sdl->dst[DWALL]);
	else if (def.tab[calc.map_y][calc.map_x] == 2)
		SDL_RenderCopy(sdl->render, sdl->game[TWALLB], &sdl->src[SWALL], \
												&sdl->dst[DWALL]);
}

void	ft_init_draw(t_calc calc, t_sdl *sdl, t_draw *draw, t_def def)
{
	if (calc.side == 0)
		draw->wall_x = calc.ray_pos_y + calc.wall_dist * calc.ray_dir_y;
	else
		draw->wall_x = calc.ray_pos_x + calc.wall_dist * calc.ray_dir_x;
	draw->wall_x = draw->wall_x - (int)draw->wall_x;
	if (def.tab[calc.map_y][calc.map_x] == 1)
		SDL_QueryTexture(sdl->game[TWALL], NULL, NULL, &sdl->src[SWALL].w, \
												&sdl->src[SWALL].h);
	else if (def.tab[calc.map_y][calc.map_x] == 2)
		SDL_QueryTexture(sdl->game[TWALLB], NULL, NULL, &sdl->src[SWALL].w, \
												&sdl->src[SWALL].h);
	sdl->src[SWALL].x = draw->wall_x * sdl->src[SWALL].w;
	sdl->src[SWALL].w = 1;
	sdl->src[SWALL].y = 0;
	draw->line_height = (int)HEIGHT / calc.wall_dist;
	draw->draw_s = -draw->line_height / 2 + HEIGHT / 2 + sdl->y;
	draw->draw_e = draw->line_height / 2 + HEIGHT / 2 + sdl->y;
}

void	ft_draw_minimap(t_sdl *sdl, t_def def)
{
	int		x;
	int		y;
	Uint32	color[3];

	color[0] = SDL_MapRGBA(sdl->format, 67, 67, 67, 255);
	color[1] = SDL_MapRGBA(sdl->format, 215, 215, 215, 255);
	color[2] = SDL_MapRGBA(sdl->format, 174, 4, 4, 255);
	SDL_LockTexture(sdl->game[TMAP], NULL, &sdl->tmp, &sdl->pitch);
	sdl->pixels = sdl->tmp;
	y = -1;
	while (++y < def.map_h)
	{
		x = -1;
		while (++x < def.map_w)
		{
			if (def.tab[y / 14][x / 14] > 0 || def.tab[y / 14][x / 14] == -1)
				sdl->pixels[x + (y * def.map_w)] = color[0];
			if (y / 14 == (int)def.pos_y && x / 14 == (int)def.pos_x)
				sdl->pixels[x + (y * def.map_w)] = color[2];
			else if (def.tab[y / 14][x / 14] == 0)
				sdl->pixels[x + (y * def.map_w)] = color[1];
		}
	}
	SDL_UnlockTexture(sdl->game[TMAP]);
}

void	ft_draw_saf(t_sdl *sdl)
{
	int		x;
	int		y;
	Uint32	color;

	sdl->game[TSKY] = ft_create_texture("./img/testsky.bmp", sdl, 0);
	SDL_QueryTexture(sdl->game[TSKY], NULL, NULL, &sdl->width_sky, NULL);
	y = -1;
	color = SDL_MapRGBA(sdl->format, 64, 64, 64, 255);
	SDL_LockTexture(sdl->game[TFLOOR], NULL, &sdl->tmp, &sdl->pitch);
	sdl->pixels = sdl->tmp;
	while (++y < HEIGHT * 2)
	{
		x = -1;
		while (++x < WIDTH)
			sdl->pixels[x + (y * WIDTH)] = color;
	}
	SDL_UnlockTexture(sdl->game[TFLOOR]);
}

void	ft_draw_life(t_def def, t_sdl *sdl)
{
	Uint32	color[2];
	int		x;
	int		y;

	y = -1;
	if (def.garg.life > 0 && def.garg.life <= 25)
		color[0] = SDL_MapRGBA(sdl->format, 255, 26, 0, 255);
	if (def.garg.life > 25 && def.garg.life <= 50)
		color[0] = SDL_MapRGBA(sdl->format, 255, 111, 0, 255);
	if (def.garg.life > 50 && def.garg.life <= 100)
		color[0] = SDL_MapRGBA(sdl->format, 108, 232, 84, 255);
	color[1] = SDL_MapRGBA(sdl->format, 0, 0, 0, 255);
	SDL_LockTexture(sdl->game[TLIFE], NULL, &sdl->tmp, &sdl->pitch);
	sdl->pixels = sdl->tmp;
	while (++y < 25)
	{
		x = -1;
		while (++x < def.garg.life * 2)
			sdl->pixels[x + (y * 200)] = color[0];
		x--;
		while (++x < 200)
			sdl->pixels[x + (y * 200)] = color[1];
	}
	SDL_UnlockTexture(sdl->game[TLIFE]);
}
