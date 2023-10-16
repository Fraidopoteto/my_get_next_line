/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschmunk < jschmunk@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:10:25 by jschmunk          #+#    #+#             */
/*   Updated: 2023/10/11 16:10:25 by jschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd)
{
    char        *line;
    char        buffer[BUFFER_SIZE + 1];
    int         size;
    static char *rest;
    int         lineLen;

    *line = NULL;
    *rest = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (rest)
        line = rest;
    else
        line = (char *)malloc(1);
    
    if (!line)
        return (NULL);
    
    line[0] = '\0';
    while ((size = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[size] = '\0';
        line = (char *)realloc(line, strlen(line) + size + 1);
        if (!line)
            return (NULL);
        strcat(line, buffer);
        if (strchr(line, '\n'))
            break;
    }
    if (size == 0 && !line[0])
    {
        free (line);
        return (NULL);
    }
    if (strchr(line, '\n'))
    {
        lineLen = strlen(line);
        rest = strdup(line + lineLen);
        line[lineLen - strlean(rest)] = '\0';
    }
}
