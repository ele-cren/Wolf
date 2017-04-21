/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-cren <ele-cren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:04:57 by ele-cren          #+#    #+#             */
/*   Updated: 2017/04/21 14:34:53 by ele-cren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf.h>

int		main(int ac, char **av)
{
	t_sdl	sdl;

	(void)av;
	if (ac == 1)
	{
		ft_init_sdl(&sdl);
		ft_draw_saf(&sdl);
		ft_select(&sdl);
	}
	else
		ft_putendl("Usage : ./wolf3d");
	return (0);
}

void	ft_game(t_sdl *sdl, char *map, int select)
{
	t_def	def;
	t_parse	parse;

	ft_init_all(&def, sdl, &parse, map);
	if (select == 1 || select == 2)
		(select == 1) ? ft_init_42(&def) : ft_init_1(&def);
	else if (select == 3)
		ft_init_2(&def);
	ft_aff(sdl, def);
	while (sdl->keep_game == 1)
	{
		ft_event(sdl);
		def.m_speed = 0.075;
		ft_is_key(sdl, &def);
		def.o_time = def.time;
		def.time = SDL_GetTicks();
		def.frame_time = (def.time - def.o_time) / 1000;
		ft_aff(sdl, def);
		SDL_Delay(16);
	}
	sdl->key[SDL_SCANCODE_ESCAPE] = 0;
	SDL_RenderClear(sdl->render);
	ft_inttabdel(&def.tab);
	SDL_DestroyTexture(sdl->map);
	SDL_DestroyTexture(sdl->wall);
}
