/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:51:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/03/30 15:44:04 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strspn(char *s, const char *accepts)
{
	int	i;

	i = 0;
	while (s[i] && ft_strchr(accepts, s[i]))
		i++;
	return (i);
}
