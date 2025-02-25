/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:34:14 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/21 22:05:01 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	result = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == NULL)
		return (result);
	i = 0;
	j = 0;
	while (s1[j])
	{
		result[i] = ((char *)s1)[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
		result[i++] = ((char *)s2)[j++];
	result[i] = 0;
	return (result);
}
