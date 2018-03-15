/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sdl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftymchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:43:12 by ftymchyn          #+#    #+#             */
/*   Updated: 2018/03/14 17:43:14 by ftymchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PT_H
# define PT_H

# include <stdio.h>
# include "SDL.h"

# define COLOR	0xFFFFFF
# define PUT_PIXEL(pixels, width, x, y, c) (pixels[y * width + x] = c)

#endif