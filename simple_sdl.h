/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sdl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:43:12 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/15 13:01:26 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PT_H
# define PT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netinet/in.h>
#include <netdb.h> 

# include <SDL.h>

# define COLOR	0xFFFFFF
# define PUT_PIXEL(pixels, width, x, y, c) (pixels[y * width + x] = c)

#endif
