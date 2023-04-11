/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:51:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/11 15:21:05 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	ft_strspn(char *s, const char *accepts)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(accepts, s[i]))
		i++;
	return (i);
}
