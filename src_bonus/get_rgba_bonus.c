/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgba.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:21:49 by jorgfern          #+#    #+#             */
/*   Updated: 2023/10/15 20:24:43 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Function to get a pixel value from the texture at (x, y)
uint32_t get_pixel(mlx_texture_t *side, uint32_t y, uint32_t x)
{
    // Ensure coordinates are within texture bounds
    if (y >= side->height || x >= side->width)
        return 0; // Return transparent or black

    // Calculate the index in the pixel array
    uint32_t xy = (y * side->width + x) * 4;

    // Retrieve the pixel color in ARGB format
    return (side->pixels[xy] << 24) |        // Red
           (side->pixels[xy + 1] << 16) |    // Green
           (side->pixels[xy + 2] << 8) |     // Blue
           (side->pixels[xy + 3]);           // Alpha
}

// Function to get interpolated color from a texture range
uint32_t get_rgb(t_all *all, mlx_texture_t *side, double y, double x, double step_size, double scale_y)
{
    uint32_t start_x = (uint32_t)floor(x);
    uint32_t start_y = (uint32_t)floor(y);
    uint32_t end_x = (uint32_t)floor(x + 1.0);
    uint32_t end_y = (uint32_t)floor(y + step_size);
	uint32_t step = round(((double)side->width * (double)side->height) / (1280 * 720 ) / (all->dist[0] / 1000.0));

	(void)scale_y;
	if (step == 0)
		step = 1;

    if (end_x >= side->width) end_x = side->width - 1;
    if (end_y >= side->height) end_y = side->height - 1;

    double total_red = 0, total_green = 0, total_blue = 0, total_alpha = 0;
    uint32_t count = 0;

    for (uint32_t i = start_y; i <= end_y; i += step) {
        for (uint32_t j = start_x; j <= end_x; j += step) {
            double x_ratio = fmod(x, 1.0);
            double y_ratio = fmod(y, 1.0);

            // Calculate the weights for interpolation
            double w1 = (1 - x_ratio) * (1 - y_ratio);
            double w2 = x_ratio * (1 - y_ratio);
            double w3 = (1 - x_ratio) * y_ratio;
            double w4 = x_ratio * y_ratio;

            // Get the colors of the four surrounding pixels
            uint32_t p1 = get_pixel(side, i, j);
            uint32_t p2 = get_pixel(side, i, j + 1 < side->width ? j + 1 : j);
            uint32_t p3 = get_pixel(side, i + 1 < side->height ? i + 1 : i, j);
            uint32_t p4 = get_pixel(side, i + 1 < side->height ? i + 1 : i, j + 1 < side->width ? j + 1 : j);

            // Interpolate red channel
            total_red += w1 * ((p1 >> 24) & 0xFF) + w2 * ((p2 >> 24) & 0xFF) +
                         w3 * ((p3 >> 24) & 0xFF) + w4 * ((p4 >> 24) & 0xFF);

            // Interpolate green channel
            total_green += w1 * ((p1 >> 16) & 0xFF) + w2 * ((p2 >> 16) & 0xFF) +
                           w3 * ((p3 >> 16) & 0xFF) + w4 * ((p4 >> 16) & 0xFF);

            // Interpolate blue channel
            total_blue += w1 * ((p1 >> 8) & 0xFF) + w2 * ((p2 >> 8) & 0xFF) +
                          w3 * ((p3 >> 8) & 0xFF) + w4 * ((p4 >> 8) & 0xFF);

            // Interpolate alpha channel
            total_alpha += w1 * (p1 & 0xFF) + w2 * (p2 & 0xFF) +
                           w3 * (p3 & 0xFF) + w4 * (p4 & 0xFF);

            ++count;
        }
    }

    // Average the interpolated colors
    unsigned int red = (unsigned int)(total_red / count);
    unsigned int green = (unsigned int)(total_green / count);
    unsigned int blue = (unsigned int)(total_blue / count);
    unsigned int alpha = (unsigned int)(total_alpha / count);

    // Return the interpolated color in ARGB format
    return (red << 24) | (green << 16) | (blue << 8) | alpha;
}

// Function to get the pixel color with a given scale
unsigned int get_pixel_color(t_all *all, double scale_y, double y)
{
    double step_size = fmax(1.0, scale_y);
    return get_rgb(all, all->side, y * scale_y, all->texture_x, step_size, scale_y);
}
