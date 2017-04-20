/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl->c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-cren <ele-cren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 14:10:32 by ele-cren          #+#    #+#             */
/*   Updated: 2017/04/20 17:06:40 by ele-cren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_init_sdl(t_sdl *sdl)
{
	if ((SDL_Init(SDL_INIT_VIDEO) || TTF_Init()) != 0)
		ft_sdl_error();
	if ((sdl->win = SDL_CreateWindow("Win", SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		ft_sdl_error();
	if ((sdl->render = SDL_CreateRenderer(sdl->win, -1, 0)) == NULL)
		ft_sdl_error();
	if ((sdl->saf = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_RGBA8888, \
					SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)) == NULL)
		ft_sdl_error();
	if ((sdl->tmp_menu = SDL_LoadBMP("img/menu.bmp")) == NULL)
		ft_sdl_error();
	if ((sdl->menu[IMG] = SDL_CreateTextureFromSurface(sdl->render, \
					sdl->tmp_menu)) == NULL)
		ft_sdl_error();
	SDL_FreeSurface(sdl->tmp_menu);
	ft_init_color(sdl);
	if ((sdl->font = TTF_OpenFont("fonts/wolf.ttf", 75)) == NULL)
		ft_sdl_error();
	sdl->format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	SDL_SetRenderDrawColor(sdl->render, 255, 255, 255, 255);
	SDL_RenderClear(sdl->render);
}

void	ft_aff(t_sdl *sdl, t_def def)
{
	SDL_SetRenderDrawColor(sdl->render, 0, 0, 0, 255);
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->saf, NULL, NULL);
	ft_loop(def, sdl);
	ft_draw_minimap(sdl, def);
	SDL_RenderCopy(sdl->render, sdl->map, NULL, &sdl->posmap);
	SDL_RenderPresent(sdl->render);
}