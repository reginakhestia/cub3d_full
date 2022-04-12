/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <ztune@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 0:01:01 by ztune              #+#    #+#             */
/*   Updated: 2022/04/08 0:02:02 by ztune             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		slen;

	slen = ft_strlen(s);
	ret = malloc(sizeof(char) * (slen + 1));
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s, slen);
	ret[slen] = '\0';
	return (ret);
}
