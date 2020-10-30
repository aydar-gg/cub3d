/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrin_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:40:44 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 22:03:21 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_scrin_part_2(t_vars *vars, int32_t num, char *bmp)
{
	uint32_t	i;
	int			y;

	num = 1;
	ft_memcpy(&bmp[26], &num, 2);
	ft_memcpy(&bmp[28], &vars->bpp, 2);
	i = 54;
	y = 0;
	while (y < vars->hight)
	{
		ft_memcpy(&bmp[i], vars->img_data, vars->width * sizeof(int));
		vars->img_data += vars->line_length;
		i += vars->width * sizeof(int);
		y++;
	}
	num = open("scr.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write(num, bmp, i);
	free(bmp);
	close(num);
	exit(0);
}

void	get_scrin(t_vars *vars)
{
	char			*bmp;
	int32_t			num;
	uint32_t		size;

	size = (vars->hight * vars->width + 54) * sizeof(int);
	if (!(bmp = (char*)malloc(size)))
		ft_error(1, vars);
	ft_bzero(bmp, size);
	ft_memcpy(&bmp[0], "BM", 2);
	ft_memcpy(&bmp[2], &size, 4);
	num = 54;
	ft_memcpy(&bmp[10], &num, 4);
	num = 40;
	ft_memcpy(&bmp[14], &num, 4);
	num = vars->width;
	ft_memcpy(&bmp[18], &num, 4);
	num = -(vars->hight);
	ft_memcpy(&bmp[22], &num, 4);
	get_scrin_part_2(vars, num, bmp);
}
