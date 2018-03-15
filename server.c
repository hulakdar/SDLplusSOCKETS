/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:43:23 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/15 15:09:29 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "simple_sdl.h"

int main(int argc, char **argv)
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*canvas;
	int					width = 1000;
	int					height = 1000;
	int					pixels[1000 * 1000];

	// SOCKETS
	int 				sockfd, newsockfd, portno;
	unsigned int		clilen;
	struct sockaddr_in	serv_addr, cli_addr;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) {
		printf("bind error");
		exit(0);
	}
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	// SDL
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

	SDL_Event			event;
	int					mouse_pressed = 0;
	int					n = 0;
	int					ret = 0;
	int					coords[2];
	bzero(pixels, sizeof(pixels));
	while (1)
	{
		if (SDL_PollEvent(&event))
		{
			n = 0;
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
				coords[0] = event.motion.x;
				coords[1] = event.motion.y;
				while (n < (int)sizeof(coords) && ret > -1)
				{
					ret = write(newsockfd, coords + (n >> 2), sizeof(coords) - n);
					if (ret == 0)
						sleep(1);
					if (ret == -1)
						break;
					n += ret;
				}
			}
		}
		SDL_UpdateTexture(canvas, NULL, pixels, width << 2);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	close(sockfd);
	SDL_Quit();
	return (0);
}
