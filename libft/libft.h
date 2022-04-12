/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <ztune@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 0:01:01 by ztune              #+#    #+#             */
/*   Updated: 2022/04/08 0:02:02 by ztune             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# define GNL_BUFF_SIZE 1024

int		ft_strlen(const char *str);
char	*ft_memcpy(char *dest, const char *src, int n);
char	*ft_strdup(const char *s);
int		ft_gnl(int fd, char **line);

#endif
