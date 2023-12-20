/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaixao- <lpaixao-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:22:18 by lpaixao-          #+#    #+#             */
/*   Updated: 2023/12/14 18:46:23 by lpaixao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
        str = ft_strjoin(str, file);
        if (ft_strchr(file, '\n'))
        {
    	    printf("read achou \\n na posição %i:\n", my_strchr(file, '\n'));
            break ;
        }
*/

static char    *read_line(char *str, int fd)
{
//    printf("inicio | read_line com fd: %i e str: %s\n", fd, str);
    char    *file;
    int     ret_r;

    ret_r = 1;
    file = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!file)
		return (NULL);
    while (ret_r > 0)
    {
//        printf("inicio | do loop\n");
        ret_r = read(fd, file, BUFFER_SIZE); // foguete não dá ré
//	    printf("read leu ret_r: %i bytes\n", ret_r);
        if (ret_r <= 0)
			break ;
        file[ret_r] = '\0';
//	    printf("read leu ret_r: %i bytes em file: |%s|\n", ret_r, file);
        if (!ft_strchr(file, '\n'))
        {
//    	    printf("read não achou \\n \n");    
            str = ft_strjoin(str, file);
        }
        else
        {
//    	    printf("read achou \\n na posição %i:\n", my_strchr(file, '\n'));
            str = ft_strjoin(str, file);
            break ;
        }
//        printf("fim    | do loop\n");
    }
	free(file);
//    printf("fim    | read_line com fd: %i e str: %s\n", fd, str);
    return (str);
}

static char    *cut_line(char *str, char **extra)
{
//    printf("inicio | cut_line com str: |%s| e *extra: |%s|\n", str, *extra);
    char    *temp;
	int		len;

    temp = NULL;
	len = 0;

	len = my_strchr(str, '\n');
//    printf("achou \\n na posição %i de str: %s\n", len, str);
    *extra = ft_substr(str, len + 1, (ft_strlen(str) - (len + 1)));
    temp = ft_substr(str, 0, len);
    free(str);
    str = temp;
    temp = NULL;
//    printf("fim    | cut_line com str: |%s| e *extra: |%s|\n", str, *extra);
    return (str);
}

char    *get_next_line(int fd)
{
//    printf("inicio | get_next_line com fd: %i\n", fd);
    static char	*extra;
    char		*str;

    str = NULL;
    if (!extra)
        extra = NULL;
    if (extra)
    {
        str = extra;
        extra = NULL;
    }
    str = read_line(str, fd);
    if (ft_strchr(str, '\n'))
        str = cut_line(str, &extra);
//    printf("fim    | get_next_line com fd: %i\n", fd);
    return (str);
}