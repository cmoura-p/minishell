/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:32:27 by cmoura-p          #+#    #+#             */
/*   Updated: 2025/02/21 22:04:26 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	int		len;

	len = ft_strlen(s);
	new_string = (char *) malloc (len * (sizeof(char)) + 1);
	if (new_string == NULL)
		return (new_string);
	ft_strlcpy(new_string, s, len + 1);
	return (new_string);
}
