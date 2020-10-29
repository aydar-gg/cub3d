/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_pos_sprit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:32:32 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:09:58 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_sprite	*ft_lstlast_sp(t_sprite *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void		ft_lstadd_back_sp(t_sprite **lst, t_sprite *new)
{
	t_sprite *copy;

	copy = *lst;
	if (!lst || !new)
		return ;
	if (copy == NULL)
		*lst = new;
	else
	{
		copy = ft_lstlast_sp(*lst);
		copy->next = new;
	}
}

void		no_place(t_vars *vars, t_sprite *new, int i, int k)
{
	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		ft_error(1, vars);
	new->y = i;
	new->x = k;
	new->y_3d = i * s_map + s_map / 2;
	new->x_3d = k * s_map + s_map / 2;
	new->next = NULL;
	ft_lstadd_back_sp(&vars->sprit, new);
	vars->count_sp++;
}

void			take_map_sprit(t_vars *vars)
{
	int			i;
	int			k;
	t_sprite	*new;

	new = NULL;
	vars->sprit = NULL;
	i = 0;
	vars->count_sp = 0;
	while (i != vars->max_map_hight)
	{
		k = 0;
		while(vars->t_map[i][k] != '\0')
		{
			if (vars->t_map[i][k] == '2')
				no_place(vars, new, i, k);
			k++;
		}
		i++;
	}
}
