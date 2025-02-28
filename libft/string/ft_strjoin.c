/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:34:14 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/25 23:02:22 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int 	j;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	result = ((char *)malloc(sizeof(char) *(size) + 1));
	if (result == NULL)
		return (result);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
