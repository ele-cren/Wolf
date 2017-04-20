/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-cren <ele-cren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:14:30 by ele-cren          #+#    #+#             */
/*   Updated: 2017/04/20 17:30:26 by ele-cren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

void	ft_free(t_sdl *sdl)
{
	SDL_DestroyWindow(sdl->win);
	SDL_DestroyRenderer(sdl->render);
	SDL_FreeFormat(sdl->format);
	SDL_DestroyTexture(sdl->menu[MENU]);
	SDL_DestroyTexture(sdl->menu[IMG]);
	SDL_DestroyTexture(sdl->saf);
	TTF_CloseFont(sdl->font);
	TTF_Quit();
	SDL_Quit();
}