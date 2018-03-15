/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:43:23 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/14 17:43:25 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "simple_sdl.h"

int main(void)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*canvas;
	int				width = 1000;
	int				height = 1000;
	int				pixels[1000 * 1000];

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		"Simple SDL", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		0);

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED);

	canvas = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height);

	SDL_Event		event;
	int				mouse_pressed = 0;
	bzero(pixels, sizeof(pixels));
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				mouse_pressed = 1;
			else if (event.type == SDL_MOUSEBUTTONUP)
				mouse_pressed = 0;
			else if (mouse_pressed && event.type == SDL_MOUSEMOTION)
			{
				PUT_PIXEL(
					pixels,
					width,
					event.motion.x,
					event.motion.y,
					COLOR);
			}
		}
		SDL_UpdateTexture(canvas, NULL, pixels, width << 2);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_Quit();
	return (0);
}