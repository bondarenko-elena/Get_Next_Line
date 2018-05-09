/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olbondar <olbondar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 17:05:45 by olbondar          #+#    #+#             */
/*   Updated: 2017/11/25 17:23:31 by olbondar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmps1;
	const unsigned char	*tmps2;
	size_t				i;

	tmps1 = (const unsigned char*)s1;
	tmps2 = (const unsigned char*)s2;
	i = 0;
	if (tmps1 == tmps2 || n == 0)
		return (0);
	while (i < n)
	{
		if (tmps1[i] != tmps2[i])
			return (tmps1[i] - tmps2[i]);
		i++;
	}
	return (0);
}
