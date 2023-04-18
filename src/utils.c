/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/18 15:29:13 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	error_message(char *msg, char *line)
{
	ft_putstr_fd("Error.\n", 2);
	ft_putstr_fd(msg, 2);
	if (line)
		ft_putstr_fd(line, 2);
}

int	get_next_color(char *str)
{
	char	*buf;
	int		value;
	int		i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0)
		return (-1);
	buf = ft_substr(str, 0, i);
	value = ft_atoi(buf);
	free(buf);
	return (value);
}

int	is_colorline_flawless(char *str)
{
	int	i;
	int	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			nbr++;
		else if (!ft_isdigit(str[i]) && ft_isprint(str[i]))
			return (-1);
	}
	return (nbr);
}

int	is_input(char *line)
{
	char	*map_input;

	map_input = "10NSWE ";
	while (*line == 32)
		line++;
	while (*line)
	{
		if (!ft_strchr(map_input, *line) && *line > 32)
			return (0);
		line++;
	}
	return (1);
}

int	is_asset(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (2);
	return (0);
}
