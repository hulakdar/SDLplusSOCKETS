/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:43:23 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/15 14:55:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "simple_sdl.h"

int main(int argc, char **argv)
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*canvas;
	int				width = 1000;
	int				height = 1000;
	int				pixels[1000 * 1000];

	// SOCKETS
    int sockfd, portno;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket");
       exit(0);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)  {
        printf("ERROR connecting");
       exit(0);
}

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

	SDL_Event		event;
	bzero(pixels, sizeof(pixels));
	printf("FD: %d\n", sockfd);
	int	n = 0;
	int	ret = 0;
	while (1)
	{
		n = 0;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
		}
		while (n < (int)sizeof(pixels) && ret > -1)
		{
			ret = read(sockfd, pixels + (n >> 2), sizeof(pixels));
			if (ret == 0)
				break ;
			n += ret;
		}
		if (ret == -1)
			break;
		SDL_UpdateTexture(canvas, NULL, pixels, width << 2);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, canvas, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	close(sockfd);
	SDL_Quit();
	return (0);
}
