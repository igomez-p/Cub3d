/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igomez-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:50:00 by igomez-p          #+#    #+#             */
/*   Updated: 2019/12/12 17:54:36 by igomez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*s;
	int		p;
	int		p2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == NULL)
		return (NULL);
	p = 0;
	while (s1[p])
	{
		s[p] = s1[p];
		p++;
	}
	p2 = 0;
	while (s2[p2])
	{
		s[p] = s2[p2];
		p++;
		p2++;
	}
	s[p] = '\0';
	return (s);
}

static char	*ft_temp(char *l)
{
	int		p;
	int		k;
	char	*temp;

	p = 0;
	while (l[p] && l[p] != '\n')
		p++;
	temp = (char *)malloc(sizeof(char) * (p + 1));
	if (!temp)
		return (NULL);
	k = 0;
	while (k != p)
	{
		temp[k] = l[k];
		k++;
	}
	temp[k] = '\0';
	return (temp);
}

static char	*ft_newstatic(char *aux, char *l, char **line)
{
	char	*aux2;

	aux2 = ft_strdup(&aux[1]);
	*line = ft_temp(l);
	free(l);
	l = NULL;
	l = ft_strdup(aux2);
	free(aux2);
	return (l);
}

char	*ft_swap(char *l, char *buf)
{
	char *temp;

	temp = ft_strjoin(l, buf);
	free(l);
	l = ft_strdup(temp);
	free(temp);
	return (l);
}

int		get_next_line(int fd, char **line)
{
	static char	*l;
	char		*b;
	int			nbytes;
	char		*aux;

	l = (!l) ? ft_strdup("") : l;
	if (!(b = malloc(BUFFER_SIZE + 1)) || fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	while ((nbytes = read(fd, b, BUFFER_SIZE)) > 0)
	{
		b[nbytes] = '\0';
		l = ft_swap(l, b);
		if ((aux = ft_strchr(l, '\n')) != NULL)
		{
			free(b);
			return (((l = ft_newstatic(aux, l, line)) != NULL) ? 1 : 1);
		}
	}
	free(b);
	if ((aux = ft_strchr(l, '\n')) != NULL)
		return (((l = ft_newstatic(aux, l, line)) != NULL) ? 1 : 1);
	*line = ft_strdup(l);
	free(l);
	l = NULL;
	return (0);
}
