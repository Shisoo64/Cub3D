/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:50:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/03/30 15:44:06 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strtok(char *str, char *token)
{
	static char	*p;

	if (str)
		p = str;
	if (!p || !token)
		return (NULL);
	p += ft_strspn(p, token);
	str = p;
	if (!*str)
		return (NULL);
	p += ft_strcspn(str, token);
	if (*p)
		*p++ = 0;
	if (*p == 0)
		p = NULL;
	return (str);
}
